#pragma once
#include"InetAddress.h"
#include"Buffer.h"
#include"TimeStamp.h"
#include"CallBacks.h"
#include"Channel.h"
#include<memory>
#include<string>
#include<atomic>
using namespace std;


class EventLoop;
class Socket;

class TcpConnection : public enable_shared_from_this<TcpConnection>
{
public:
    TcpConnection(EventLoop *loop, int sockfd, 
                InetAddress &localAddr,
                InetAddress &peerAddr);
    ~TcpConnection();

    EventLoop* getLoop() const { return _ioLoop;}
    const InetAddress& localAddress() const { return _localAddr;}
    const InetAddress& peerAddress() const { return _peerAddr;}
    
    bool connected() const {return _state == kConnected;}

    void send(const string &buf);
    void shutdown();
    void setConnectionCallback(const ConnectionCallback &cb){ _connectionCallback = cb;}
    void setMessageCallback(const MessageCallback &cb){ _messageCallback = cb;}
    void setCloseCallback(const CloseCallback &cb){ _closeCallback = cb;}

    void connectionEstablished();
    void connectDestroyed();

    int fd(){ return _channel->fd();}

private:
    enum kState{ kDisConnected, kConnecting, kConnected, kDisConnecting};
    void setState(kState state){ _state = state;}

    void handleRead(TimeStamp receiveTime);
    void handleWrite();
    void handleClose();
    void handleError();

    void sendInLoop(const void *message, size_t len);
    void shutdownInLoop();

private:
    EventLoop* _ioLoop;
    atomic_int _state;
    bool _reading;

    unique_ptr<Socket> _socket;
    unique_ptr<Channel> _channel;

    InetAddress _localAddr;
    InetAddress _peerAddr;

    ConnectionCallback _connectionCallback;     //新连接建立回调
    MessageCallback _messageCallback;           //消息到达回调
    CloseCallback _closeCallback;               //连接关闭回调

    Buffer _inputBuffer;        //接受数据的缓冲区
    Buffer _outputBuffer;       //发送数据的缓冲区
};