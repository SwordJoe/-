#pragma once
#include"TimeStamp.h"
#include<functional>
#include<memory>
#include<sys/epoll.h>
using namespace std;

class EventLoop;

/**
 * @brief Channel封装了fd及其感兴趣的事件，并且将fd在epoll上的增删改操作也进行了封装
 * 
 */
class Channel
{
    using EventCallback=function<void()>;
    using ReadEventCallback=function<void(TimeStamp)>;

public:
    Channel(EventLoop *loop, int fd);
    ~Channel();

    void handleEvent(TimeStamp recvTime);
    void setReadCallback(ReadEventCallback cb){ _readCallback=std::move(cb);}
    void setWriteCallback(EventCallback cb){ _writeCallback=std::move(cb);}
    void setCloseCallback(EventCallback cb){ _closeCallback=std::move(cb);}
    void setErrorCallback(EventCallback cb){ _errorCallback=std::move(cb);}

    void tie(const shared_ptr<void> &obj);

    int fd() const{ return _fd;}
    int events() const{ return _events;}
    int setEvents(int event){ _revents=event;}  //设置fd的事件

    void enableRead(){              //向loop中的epoll注册读事件
        _events |= kReadEvent;      //更改fd感兴趣的事件类型
        update();                   //注册读事件，update() -> EventLoop::updateChannel(Channel*) -> EpollPoller::updateChannel(Channel*) -> epoll_ctl()
    }
    void disableRead(){             
        _events &= ~kReadEvent;     
        update();                   
    }
    void enableWrite(){
        _events | kWriteEvent;
        update();
    }
    void disableWrite(){
        _events & ~kWriteEvent;
        update();
    }
    void disableAll(){
        _events = kNoneEvent;
        update();
    }

    bool isNoneEvent() const{ return _events & kNoneEvent;}
    bool isWriting() const { return _events & kWriteEvent; }
    bool isReading() const { return _events & kReadEvent; }

    int state(){ return _state;}
    void setState(int state){ _state=state;}

    EventLoop* ownerLoop(){ return _loop;}
    void removeFromEventLoop();

private:
    void update();          //对fd进行更新
    void handleEventWithGuard(TimeStamp recvTime);

private:
    EventLoop *_loop;       //事件循环，每个fd都需要绑定在一个loop上
    const int _fd;
    int _events;            //注册fd感兴趣的事件
    int _revents;           //epoll 返回的具体的事件
    int _state;             //对应EpollPoller.cc中的kNew:未添加到epoll， kAdded：已添加到epoll， kDeleted:已从epoll删除

    weak_ptr<void> _tie;
    bool _tied;

    static const int kNoneEvent;
    static const int kReadEvent;
    static const int kWriteEvent;

    ReadEventCallback _readCallback;
    EventCallback _writeCallback;
    EventCallback _closeCallback;
    EventCallback _errorCallback;
};

