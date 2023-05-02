#include"TcpServer.h"
#include<sys/socket.h>
#include<sys/types.h>
#include<stdio.h>
#include<errno.h>
#include<strings.h>
#include<unistd.h>
#include<iostream>

static void defaultConnectionCallback(const TcpConnectionPtr& conn)
{
    std::cout<<"["<<conn->peerAddr().toIpPort()<<" -> "<<
            conn->servAddr().toIpPort()<<"] is "<< 
            (conn->isConnected() ? "UP" : "DOWN")  <<std::endl;
}

TcpServer::TcpServer(EventLoop* mainLoop, InetAddress& servAddr)
:_lfd(::socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK | SOCK_CLOEXEC, 0))
,_isRunning(false)
,_mainLoop(mainLoop)
,_servAddr(servAddr)
,_acceptChannel(new Channel(_lfd, mainLoop))
,_threadPool(new EventLoopThreadPool(mainLoop))
,_connectionCallback(std::bind(&defaultConnectionCallback,std::placeholders::_1))
{
    _acceptChannel->setReadCallback(std::bind(&TcpServer::onNewConnection, this));
}

TcpServer::~TcpServer()
{
    ::close(_lfd);
}

void TcpServer::start()
{
    _threadPool->start();   //先启动线程池

    //socket、bind、listen、accept的流程
    int option = 1;
    setsockopt(_lfd, SOL_SOCKET, SO_REUSEPORT, &option, sizeof(option));
    setsockopt(_lfd, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(option));
    ::bind(_lfd, (sockaddr*)_servAddr.getSockAddr(), sizeof(sockaddr_in));
    ::listen(_lfd, 128);

    _acceptChannel->setEvents(EPOLLIN);
    _mainLoop->addChannel(_acceptChannel.get());    //注册_lfd到_mainLoop中
    _mainLoop->loop();      //_mainLoop中的epoll开始循环监听_lfd，如果有读事件就调用accept()简历新连接
}

void TcpServer::onNewConnection()
{
    struct sockaddr_in addr;
    socklen_t len = sizeof(addr);
    bzero(&addr, sizeof(addr));

    int connfd = ::accept4(_lfd,(struct sockaddr*)&addr, &len, SOCK_NONBLOCK | SOCK_CLOEXEC);
    std::cout<<"Accept a new connfd: "<<connfd<<std::endl;
    
    InetAddress peerAddr(addr);
    EventLoop* ioLoop = _threadPool->getNextLoop();
    TcpConnectionPtr conn(new TcpConnection(connfd, ioLoop, _servAddr, peerAddr));
    _connsMap[connfd] = conn;
    conn->setConnectionCallback(_connectionCallback);
    conn->setMessageCallback(_messageCallback);
    conn->setCloseCallback(std::bind(&TcpServer::removeConnection, this, std::placeholders::_1));

    ioLoop->runInLoop(std::bind(&TcpConnection::connectionEstablished,conn));
}

void TcpServer::removeConnection(const TcpConnectionPtr& conn)
{
    _mainLoop->runInLoop(std::bind(&TcpServer::removeConnectionInLoop, this, conn));
}

void TcpServer::removeConnectionInLoop(const TcpConnectionPtr& conn)
{
    _connsMap.erase(conn->fd());
    std::cout<<"Remove a TcpConnection, fd = "<<conn->fd()<<std::endl;
    conn->getLoop()->queueInLoop(std::bind(&TcpConnection::connectionDestroyed,conn));
}

