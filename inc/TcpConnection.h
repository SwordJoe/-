#pragma once
#include"Callbacks.h"
#include"Channel.h"
#include"Buffer.h"
#include"InetAddress.h"
#include<memory>
#include<functional>
#include<string>

class EventLoop;

class TcpConnection : public std::enable_shared_from_this<TcpConnection>
{
public:
    TcpConnection(int fd, EventLoop* loop, InetAddress& servAddr, InetAddress& peerAddr);
    ~TcpConnection();

    int fd() const {return _fd;}
    bool isConnected(){return _isConnected;}
    void send(const std::string& message);
    EventLoop* getLoop() const{return _ioLoop;}
    void shutdown();
    
    void setConnectionCallback(const ConnectionCallback &cb){_connectionCallback = cb;}
    void setMessageCallback(const MessageCallback &cb){_messageCallback = cb;}
    void setCloseCallback(const CloseCallback &cb){_closeCallback = cb;}

    void connectionEstablished();
    void connectionDestroyed();

    const InetAddress& servAddr(){return _servAddr;}
    const InetAddress& peerAddr(){return _peerAddr;}

private:
    void handleRead();
    void handleWrite();
    void handleClose();
    void handleError();    

    void sendInLoop(const void* buf, size_t len);
    void shutdownInLoop();

private:
    int _fd;
    EventLoop* _ioLoop;
    InetAddress _servAddr;      //服务端IP+port
    InetAddress _peerAddr;      //客户端IP+Port
    std::unique_ptr<Channel> _channel;

    bool _isConnected;          //连接标志
    bool _isHalfClose;          //半关闭标志

    Buffer _inputBuffer;        //接收数据的缓冲区
    Buffer _outputBuffer;       //发送数据的缓冲区

    ConnectionCallback _connectionCallback;
    MessageCallback _messageCallback;
    CloseCallback _closeCallback;
};