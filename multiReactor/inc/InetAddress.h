#pragma once

#include<arpa/inet.h>
#include<netinet/in.h>
#include<string>
using namespace std;

class InetAddress
{
public:
    explicit InetAddress(uint16_t port=0, string ip="127.0.0.1");
    explicit InetAddress(const sockaddr_in &addr):_addr(addr){}

    string toIp() const;
    string toIpPort() const;
    uint16_t toPort() const;

    const sockaddr_in* getSockAddr() const {return &_addr;}
    void setSockAddr(const sockaddr_in &addr) {_addr=addr;}

private:
    sockaddr_in _addr;
};