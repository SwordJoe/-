#pragma once
#include<netinet/in.h>
class InetAddress; 

class Socket
{
public:
    explicit Socket(int fd):_fd(fd){}
    ~Socket();

    int fd() const {return _fd;}
    void bindAddress(const InetAddress &localaddr);
    void listen();
    int accept(InetAddress *peerAddr);

    void shutdownWrite();

    //void setTcpNoDelay(bool on);
    void setReuseAddr(bool on);
    void setReusePort(bool on);
    void setKeepAlive(bool on);

private:
    const int _fd;
};