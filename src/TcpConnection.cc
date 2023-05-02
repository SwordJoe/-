#include"TcpConnection.h"
#include"EventLoop.h"
#include<sys/socket.h>
#include<unistd.h>
#include<strings.h>
#include<iostream>

TcpConnection::TcpConnection(int fd, EventLoop* loop, InetAddress& servAddr, InetAddress &peerAddr)
:_fd(fd)
,_ioLoop(loop)
,_channel(new Channel(fd, loop))
,_servAddr(servAddr)
,_peerAddr(peerAddr)
,_isConnected(true)
,_isHalfClose(false)
{
    //设置各个回调函数
    _channel->setReadCallback(std::bind(&TcpConnection::handleRead, this));
    _channel->setWriteCallback(std::bind(&TcpConnection::handleWrite, this));
    _channel->setCloseCallback(std::bind(&TcpConnection::handleClose, this));
    _channel->setErrorCallback(std::bind(&TcpConnection::handleError, this));
}

TcpConnection::~TcpConnection()
{
    close(_fd);
}

void TcpConnection::send(const std::string& message)
{
    if(_isConnected){
        if(_ioLoop->isInLoopThread()){
            sendInLoop(message.c_str(), message.size());
        }else{
            _ioLoop->runInLoop(std::bind(&TcpConnection::sendInLoop, this, message.c_str(), message.size()));
        }
    }
}

void TcpConnection::sendInLoop(const void* buf, size_t len)
{
    size_t nWroteBytes = 0;
    size_t nLeftBytes = len;

    if(_isConnected == false){
        return;
    }

    //只有当fd没有注册写事件，并且发送缓冲区的没有可读字节数时才能先用原生::write()发送
    if(!_channel->isWriting() && _outputBuffer.readableBytes() == 0){
        nWroteBytes = ::write(_channel->fd(), buf, len);
        if(nWroteBytes > 0){
            nLeftBytes = len - nWroteBytes;
        }
        else if( nWroteBytes < 0){
            if(errno == EAGAIN || errno == EWOULDBLOCK){        //系统缓冲区已满，非阻塞返回
                std::cout<<"write errno = EAGAIN"<<std::endl;                
            }
            else if(errno == EINTR){    //写入之前被其他信号打断
                std::cout<<"write errno = EINTR"<<std::endl; 
            }
            else if(errno == EPIPE || errno == ECONNRESET){    //对端close(),并发送了RST
                perror("write");
            }
        }
    }

    //如果调用::write()没有一次性写入成功，就将剩余字节追加到发送缓冲区后面，并给_channel注册写事件
    if(nLeftBytes > 0){
        _outputBuffer.append((char*)buf+nWroteBytes, nLeftBytes);
        if(!_channel->isWriting()){
            int events = _channel->events();
            _channel->setEvents(events | EPOLLOUT);
            _ioLoop->updateChannel(_channel.get()); 
        }
    }
    
}

void TcpConnection::shutdown()
{
    if(_isConnected){
        _isHalfClose = true;
        _ioLoop->runInLoop(std::bind(&TcpConnection::shutdownInLoop, this));
    }
}

void TcpConnection::shutdownInLoop()
{
    if(!_channel->isWriting()){     //如果fd没有写入事件，就半关闭
        ::shutdown(_fd, SHUT_WR);
    }
}

void TcpConnection::connectionEstablished()
{
    _channel->tie(shared_from_this());      //将_channel与TcpConnection绑定
    _channel->setEvents(EPOLLIN);           //设置fd的读事件
    _ioLoop->addChannel(_channel.get());    //将该fd添加到epoll监听队列中监听其读事件
    _connectionCallback(shared_from_this());
}

void TcpConnection::connectionDestroyed()
{
    _isConnected = false;
    _connectionCallback(shared_from_this());    //调用默认的ConnectionCallback,打印TCP下线信息
    _ioLoop->deleteChannel(_channel.get());
}

void TcpConnection::handleRead()
{
    int savedErrno = 0;
    size_t n = _inputBuffer.readFd(_fd, &savedErrno);
    if(n > 0){
        _messageCallback(shared_from_this(), &_inputBuffer);
    }
    else if(n == 0){
        handleClose();
    }
    else{
        errno = savedErrno;
        handleError();
    }
}

void TcpConnection::handleWrite()
{
    if(_channel->isWriting()){
        int savedErrno = 0;
        size_t nWroteBytes = _outputBuffer.writeFd(_channel->fd(), &savedErrno);
        if(nWroteBytes > 0){
            if(_outputBuffer.readableBytes() == 0){ //如果发送缓冲区没有待发送的数据，就停止关注_channel的写事件
                int events = _channel->events();
                events &= ~EPOLLOUT;
                _channel->setEvents(events);
                _ioLoop->updateChannel(_channel.get());
            }
        }
    }
    else{
        std::cout<<"connfd:"<<_channel->fd()<<" is down, no more writing"<<std::endl;
    }
}

void TcpConnection::handleClose()
{
    _isConnected = false;
    _channel->setEvents(0);     
    _ioLoop->updateChannel(_channel.get());     //取消_channel所有关心的事件
    
    TcpConnectionPtr conn(shared_from_this());
    _closeCallback(conn);        //执行上层注册给TcpConnection的closeCallback
}

void TcpConnection::handleError()
{
    // int optval;
    // socklen_t optlen = static_cast<socklen_t>(sizeof(optval));
    // ::getsockopt(_fd, SOL_SOCKET, SO_ERROR, &optval, &optlen);
    // std::cout<<strerror(optval)<<std::endl;
}