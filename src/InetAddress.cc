#include"InetAddress.h"
#include<string.h>

InetAddress::InetAddress(uint16_t port, std::string ip)
{
    bzero(&_addr, sizeof(_addr));
    _addr.sin_family = AF_INET;
    _addr.sin_port = htons(port);
    _addr.sin_addr.s_addr = inet_addr(ip.c_str());
}


std::string InetAddress::toIp() const
{
    char buf[64] = {0};
    inet_ntop(AF_INET, &_addr.sin_addr, buf, sizeof(buf));
    return buf;
}

uint16_t InetAddress::toPort() const
{
    return ntohs(_addr.sin_port);
}

std::string InetAddress::toIpPort() const
{
    std::string str = toIp();
    uint16_t port = toPort();
    str = str + " : " + std::to_string(port);
    return str;
}