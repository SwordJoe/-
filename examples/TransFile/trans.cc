#include"TcpServer.h"
#include"Callbacks.h"
#include<string>
#include<iostream>
#include<fstream>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>

void connectionCallback(const TcpConnectionPtr& conn){
    std::ofstream ofs;
    ofs.open("Bible.txt",std::ios::out);
}

void recvFile(const TcpConnectionPtr& conn, Buffer *buff){
    int fd = open("Bible.txt", O_RDWR | O_APPEND);
    std::string line = buff->retrieveAllAsString();
    ::write(fd, line.c_str(), line.size());
}


int main()
{
    EventLoop loop;
    InetAddress servAddr(6666, "10.0.12.8");
    TcpServer server(&loop,servAddr);
    //server.setConnectionCallback(std::bind(&connectionCallback, std::placeholders::_1));
    server.setMessageCallback(std::bind(&recvFile, std::placeholders::_1, std::placeholders::_2));
    server.setThreadsNum(2);
    server.start();
}