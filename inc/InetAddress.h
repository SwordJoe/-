#pragma once
#include<arpa/inet.h>
#include<netinet/in.h>
#include<string>

class InetAddress
{
public:
    InetAddress(uint16_t port = 0, std::string ip = "127.0.0.1");
    InetAddress(const struct sockaddr_in &addr):_addr(addr){}

    std::string toIp() const;
    uint16_t toPort() const;
    std::string toIpPort() const;

    const struct sockaddr_in* getSockAddr() const {return &_addr;}
    void setSockAddr(const struct sockaddr_in &addr){ _addr = addr;}

private:
    struct sockaddr_in _addr;
};