#include"../inc/Acceptor.h"
#include"../inc/InetAddress.h"
#include"../logger/Log.h"
#include"../inc/LOGGER.h"
#include<sys/types.h>
#include<sys/socket.h>
#include<errno.h>
#include<unistd.h>

static int createNonBlockFd(){
    int fd=::socket(AF_INET,SOCK_STREAM | SOCK_NONBLOCK | SOCK_CLOEXEC,0);
    LOG("\t\t创建lfd,lfd=%d",fd);
    return fd;
}

Acceptor::Acceptor(EventLoop *loop,const InetAddress &listenAddr, bool reuseport)
:_loop(loop)                                
,_acceptSocket(createNonBlockFd())
,_acceptChannel(loop,_acceptSocket.fd())
,_isListening(false)
{
    _acceptSocket.setReuseAddr(true);
    _acceptSocket.setReusePort(true);
    _acceptSocket.bindAddress(listenAddr);

    _acceptChannel.setReadCallback(bind(&Acceptor::handleRead,this));
}

Acceptor::~Acceptor(){
    _acceptChannel.disableAll();    //将监听fd关心的事件都置为空
    _acceptChannel.removeFromEventLoop();        //将lfd从Epoll中删除
}

void Acceptor::listen(){
    _isListening=true;
    _acceptSocket.listen();          //开启监听
    _acceptChannel.enableRead();   //向epoll中注册读事件
    LOG("\t\t\t向mainLoop中注册lfd成功,lfd=%d",_acceptSocket.fd());
}

//lfd只需要处理关心读事件，当lfd上有事件可读时，就调用该函数，用以分发fd给subLoop
void Acceptor::handleRead(){
    InetAddress peerAddr;
    int connfd=_acceptSocket.accept(&peerAddr);     //接受客户端连接，新建一个fd
    LOG("\t\t接受一个客户端连接:fd=%d",connfd);
    if(connfd>0){
         _newConnectionCallback(connfd,peerAddr);    //轮询找到一个subLoop，唤醒该subLoop，分发当前新客户端fd给subLoop
    }
    else{
         ////LOG_ERROR("%s:%s:%d accept err:%d \n", __FILE__, __FUNCTION__, __LINE__, errno);
        if(errno==EMFILE){          //EMFILE表示当前进程打开的文件描述符已达到上限
            ////LOG_ERROR("%s:%s:%d sockfd reached limit! \n", __FILE__, __FUNCTION__, __LINE__);
        }
    }
}