#pragma once
#include"EventLoop.h"
#include"Acceptor.h"
#include"TcpConnection.h"
#include"InetAddress.h"
#include"EventLoopThreadPool.h"
#include"Buffer.h"
#include"CallBacks.h"
#include<functional>
#include<string>
#include<memory>
#include<atomic>
#include<unordered_map>
using namespace std;


class TcpServer
{
    enum Option{
        kNoReusePort,
        kReusePort
    };
    using ConnectionMap = unordered_map<int, TcpConnectionPtr>;
public:
    TcpServer(EventLoop *loop, InetAddress &listenAddr, Option option = kNoReusePort);
    ~TcpServer();

    void setConnectionCallback(const ConnectionCallback &cb){ _connectionCallback = cb;}
    void setMessageCallback(const MessageCallback &cb){ _messageCallback = cb;}
    
    void setThreadsNum(int threadsNum){ _threadPool->setThreadNum(threadsNum);}
    void start();

private:
    void newConnection(int sockfd, InetAddress &peerAddr);
    void removeConnection(const TcpConnectionPtr &conn);
    void removeConnectionInLoop(const TcpConnectionPtr &conn);

private:
    EventLoop* _mainLoop;
    string _ipPort;
    unique_ptr<Acceptor> _acceptor;
    shared_ptr<EventLoopThreadPool> _threadPool;

    ConnectionCallback _connectionCallback;
    MessageCallback _messageCallback;
    
    atomic_int _started;
    int _nextConnId;
    ConnectionMap _connections;
};