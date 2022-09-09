#include"../inc/TcpServer.h"
#include"../logger/Log.h"
#include"../inc/TcpConnection.h"
#include"../inc/LOGGER.h"
#include<cstring>
#include<functional>
#include<sys/socket.h>
#include<stdio.h>
using namespace std;
using namespace std::placeholders;

TcpServer::TcpServer(EventLoop *loop, InetAddress &listenAddr, Option option)
:_mainLoop(loop)
,_ipPort(listenAddr.toIpPort())
,_acceptor(new Acceptor(loop, listenAddr, option = kReusePort))
,_threadPool(new EventLoopThreadPool(loop))
,_nextConnId(1)
,_started(0)
{
    LOG("\t\t\tTcpServer 启动");
    //设置lfd读事件发生时的回调函数，lfd有读事件表示有新客户端连接，给其注册新客户端连接上来的处理函数
    _acceptor->setNewConnectionCallback(bind(&TcpServer::newConnection, this, _1, _2));    
}

TcpServer::~TcpServer(){
    for(auto &item : _connections){
        TcpConnectionPtr conn(item.second);
        item.second.reset();

        conn->getLoop()->runInLoop(bind(&TcpConnection::connectDestroyed,conn));
    }
}

void TcpServer::start(){
    if( _started++ == 0){
        _threadPool->start();           //启动线程池，创建n个子线程，立马开始loop循环，同时主线程会保存这n个线程对象和loop对象
        
        //在Acceptor::listen()函数的内部会调用listen()函数
        //但是Accept::listen()内部最主要的工作是将lfd注册到mainLoop的epoll中，调用Channel的enableRead()进行注册
        _mainLoop->runInLoop(bind(&Acceptor::listen, _acceptor.get()));     
        _mainLoop->loop();          //mainLoop开启循环，监听客户端连接
        LOG("\t\t\t主线程loop开始epoll_wait()监听");
    }
}

//该函数专门给lfd的读事件回调
//当有新连接到来时，回调该函数，从线程池中选取一个ioLoop，将新fd注册给该ioLoop中的epoll
void TcpServer::newConnection(int sockfd, InetAddress &peerAddr){
    EventLoop* ioLoop = _threadPool->getNextLoop();     //选取一个ioLoop
    LOG("\tioLoop地址:%p",ioLoop);
    sockaddr_in local;
    ::bzero(&local, sizeof(local));
    socklen_t addrlen = sizeof(local);
    if(getsockname(sockfd, (sockaddr*)&local, &addrlen) < 0){
        //LOGERROR("getsockname error:%d",errno);
    }
    InetAddress localAddr(local);

    //新建一个TcpConnection，初始化TcpConnection对象时会自动根据sockfd创建一个Channel通道
    TcpConnectionPtr conn(new TcpConnection(ioLoop, sockfd, localAddr, peerAddr));      
    _connections[sockfd] = conn;            //加入ConnectionMap, unordered_map<int,TcpConnectionPtr>

    conn->setConnectionCallback(_connectionCallback);
    conn->setMessageCallback(_messageCallback);
    conn->setCloseCallback(bind(&TcpServer::removeConnection, this, _1));

    //这一步很关键，之前忘了设置，新建一个TcpConnection对象之后，需要将该tcp fd注册到对应EventLoop的epoll中(注册的关键操作是在Channel的enableRead()函数中)
    //运行到这里还是在主线程中，而注册到subLoop的epoll中这些操作应该交由subLoop子线程来做，这里涉及到线程间的通信(唤醒)
    ioLoop->runInLoop(bind(&TcpConnection::connectionEstablished,conn));
}

void TcpServer::removeConnection(const TcpConnectionPtr &conn){
    _mainLoop->runInLoop(bind(&TcpServer::removeConnectionInLoop, this, conn));
}

void TcpServer::removeConnectionInLoop(const TcpConnectionPtr &conn){
    _connections.erase(conn->fd());
    EventLoop *ioLoop = conn->getLoop();
    ioLoop->queueInLoop(bind(&TcpConnection::connectDestroyed, conn));
}