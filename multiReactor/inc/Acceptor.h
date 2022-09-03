#pragma once
#include"Socket.h"
#include"Channel.h"
#include<functional>
using namespace std;

class EventLoop;
class InetAddress;

class Acceptor
{
public:
    using NewConnectionCallback=function<void(int fd, InetAddress &addr)>;
    Acceptor(EventLoop *loop ,const InetAddress &listenAddr, bool reusePort);
    ~Acceptor();

    void setNewConnectionCallback(const NewConnectionCallback &cb){
        _newConnectionCallback=cb;
    }
    void listen();

private:
    void handleRead();                              //lfd上有读事件发生时，调用该函数

    EventLoop *_loop;                               //mainLoop,Acceptor对象(lfd)只会在mainLoop(主线程)中调用
    Socket _acceptSocket;                           //用来监听的文件描述符
    Channel _acceptChannel;                         //保存lfd的Channel
    NewConnectionCallback _newConnectionCallback;   //新连接建立时的回调函数
    bool _isListening;                              //是否正在监听
};