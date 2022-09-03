#include"../inc/TcpConnection.h"
#include"../inc/Socket.h"
#include"../inc/Channel.h"
#include"../inc/EventLoop.h"
#include"../logger/Log.h"
#include"../inc/LOGGER.h"
#include <functional>
#include <string>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <strings.h>
#include <netinet/tcp.h>

using namespace std;
using namespace std::placeholders;

TcpConnection::TcpConnection(EventLoop *loop, int sockfd, InetAddress &localAddr, InetAddress &peerAddr)
:_ioLoop(loop)
,_socket(new Socket(sockfd))
,_channel(new Channel(loop, sockfd))
,_localAddr(localAddr)
,_peerAddr(peerAddr)
,_state(kConnecting)
,_reading(true)
{
    _channel->setReadCallback(bind(&TcpConnection::handleRead, this, _1));
    _channel->setWriteCallback(bind(&TcpConnection::handleWrite, this));
    _channel->setCloseCallback(bind(&TcpConnection::handleClose,this));
    _channel->setErrorCallback(bind(&TcpConnection::handleError, this));
    //LOGINFO("TcpConnection create, fd=%d", sockfd);
}

TcpConnection::~TcpConnection(){
    //LOGINFO("TcpConnection destroy, fd=%d",_socket->fd());
}

void TcpConnection::send(const string &buf){
    if(_state == kConnected){
        if(_ioLoop->isInLoopThread()){      //判断一下是否在当前线程
            sendInLoop(buf.c_str(), buf.size());
        }
        else{
            _ioLoop->runInLoop(bind(&TcpConnection::sendInLoop, this, buf.c_str(), buf.size()));
        }
    }
}

void TcpConnection::sendInLoop(const void *data, size_t len){
    size_t nwrote = 0;
    size_t remaining = len;
    bool faultError = false;

    if(_state == kDisConnected){
        //LOGERROR("TcpConnection has been disConnected, give up writing");
        return;
    }   

    //只有当fd注册了写事件，并且发送缓冲区可读字节数为0时，才直接调用原生的::write()发送
    //因为发送缓冲区的可读字节数!=0，代表上次的数据还没完全发送完毕，所以本次数据应该追加到发送缓冲区的末尾
    if(!_channel->isWriting() && _outputBuffer.readableBytes() == 0){
        nwrote = ::write(_channel->fd(), data, len);            //先调用原生的write函数直接写入TCP内核发送缓冲区
        if(nwrote >= 0){
            remaining = len - nwrote;
        }
        else{
            nwrote = 0;
            if(errno != EWOULDBLOCK){
                //LOGERROR("write error:%d", errno);
                if(errno == EPIPE || errno == ECONNRESET){
                    faultError = true;
                }
            }
        }
    }

    //如果要发送的数据过多，比如发送一份大文件给客户端，剩余字节没有写入立即写入TCP内核发送缓冲区
    //就将剩余数据加入outpufBuffer，设置fd的写事件，等待epoll返回
    if(faultError == false && remaining > 0){           
        _outputBuffer.append((char*)data+nwrote, remaining);
        if(!_channel->isWriting()){
            _channel->enableWrite();
        }
    }
}

void TcpConnection::shutdown(){
    if(_state == kConnected){
        setState(kDisConnecting);
        _ioLoop->runInLoop(bind(&TcpConnection::shutdownInLoop, this));
    }
}

void TcpConnection::shutdownInLoop(){
    if(!_channel->isWriting()){
        _socket->shutdownWrite();
    }
}

//连接建立时的操作
void TcpConnection::connectionEstablished(){
    setState(kConnected);
    _channel->tie(shared_from_this());  
    _channel->enableRead();             //注册该fd的读事件,关键操作

    _connectionCallback(shared_from_this());
}

//连接销毁
void TcpConnection::connectDestroyed(){
    if(_state == kConnected){
        setState(kDisConnected);
        _channel->disableAll();
    }
    _channel->removeFromEventLoop();
}

//处理fd上的读事件，这个函数其实是注册给Channel的
void TcpConnection::handleRead(TimeStamp receiveTime){
    int savedErrno = 0;
    size_t n = _inputBuffer.readFd(_channel->fd(), &savedErrno);
    if(n > 0){
        //using MessageCallback = function<void(const TcpConnectionPtr&, Buffer*, TimeStamp)>;
        _messageCallback(shared_from_this(), &_inputBuffer, receiveTime);
    }
    else if(n == 0){
        handleClose();
    }
    else{
        errno = savedErrno;
        //LOGERROR("TcpConnection read from fd %d error:%d", _socket->fd(),errno);
        handleError();
    }
}

//处理fd上写事件
void TcpConnection::handleWrite(){
    if(_channel->isWriting()){
        int saveErrno = 0;
        size_t n = _outputBuffer.writeFd(_channel->fd(), &saveErrno);
        if(n > 0){
            _outputBuffer.retrieve(n);      //将readable区域的数据读走并发送出去之后，取回这部分空间，也就是将_readIndex 往后移
            if(_outputBuffer.readableBytes() == 0){     
                _channel->disableWrite();   //如果发送缓冲区中的数据都被发送出去了，就让该fd不再关注可读事件
                if(_state == kDisConnecting){
                    shutdownInLoop();
                }
            }
        }
        else{
            //LOGERROR("write error");
        }
    }
    else{
        //LOGERROR("TcpConnection %d is not allowed to write",_channel->fd());
    }
}


void TcpConnection::handleClose(){
    //LOGINFO("close TcpConneciton %d ", _channel->fd());
    LOG("TCP连接关闭，fd=%d",_channel->fd());
    setState(kDisConnected);
    _channel->disableAll();

    TcpConnectionPtr connPtr(shared_from_this());
    _closeCallback(connPtr);
}

void TcpConnection::handleError()
{
    int optval;
    socklen_t optlen = sizeof optval;
    int err = 0;
    if (::getsockopt(_channel->fd(), SOL_SOCKET, SO_ERROR, &optval, &optlen) < 0)
    {
        err = errno;
    }
    else
    {
        err = optval;
    }
    ////LOG_ERROR("TcpConnection::handleError name:%s - SO_ERROR:%d \n", name_.c_str(), err);
}