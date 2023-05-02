#pragma once 
#include"Callbacks.h"
#include"Channel.h"
#include"TcpConnection.h"
#include"EventLoop.h"
#include"InetAddress.h"
#include"EventLoopThreadPool.h"
#include<functional>
#include<memory>
#include<unordered_map>

class TcpServer
{
public:
    TcpServer(EventLoop* mainLoop, InetAddress &servAddr);
    ~TcpServer();

    void setConnectionCallback(ConnectionCallback cb){ _connectionCallback = cb;}
    void setMessageCallback(MessageCallback cb){ _messageCallback = cb;}

    void setThreadsNum(int num){_threadPool->setThreadsNum(num);}
    void start();

private:
    void onNewConnection();
    void removeConnection(const TcpConnectionPtr& conn);
    void removeConnectionInLoop(const TcpConnectionPtr& conn);

private:
    int _lfd;
    bool _isRunning;
    EventLoop* _mainLoop;
    InetAddress _servAddr;
    std::unique_ptr<Channel> _acceptChannel;
    std::unordered_map<int,TcpConnectionPtr> _connsMap;
    std::unique_ptr<EventLoopThreadPool> _threadPool;

    ConnectionCallback _connectionCallback;
    MessageCallback _messageCallback;
};