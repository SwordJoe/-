#pragma once
#include"TcpServer.h"


class EventLoop;

class HttpServer
{
public:
    HttpServer(EventLoop* loop, InetAddress& servAddr);
    ~HttpServer() = default;

    void start(){ _server.start();}

    void setThreadsNum(int num){ _server.setThreadsNum(num);}

private:
    void onConnection(const TcpConnectionPtr& conn);
    void onMessage(const TcpConnectionPtr& conn, Buffer* buff);

private:
    TcpServer _server;
};