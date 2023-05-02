#pragma once
#include"Callbacks.h"
#include<memory>
#include<functional>
#include<sys/epoll.h>
class EventLoop;

class Channel
{
public:
    Channel(int fd, EventLoop* loop);
    ~Channel();

    void handleEvent();
    void setReadCallback(EventCallback cb){_readCallback = std::move(cb);}
    void setWriteCallback(EventCallback cb){_writeCallback = std::move(cb);}
    void setCloseCallback(EventCallback cb){_closeCallback = std::move(cb);}
    void setErrorCallback(EventCallback cb){_errorCallback = std::move(cb);}

    int fd() const { return _fd;}
    int events() const {return _events;}
    void setEvents(int events){ _events = events;}

    void tie(const std::shared_ptr<void> &obj);

    bool isReading() const {return _events & EPOLLIN || _events & EPOLLPRI;}
    bool isWriting() const {return _events & EPOLLOUT;}

private:
    void handleEventWithGuard();

private:
    const int _fd;
    EventLoop* _loop;
    int _events;            //Channel关心的EPOLL事件
    //int _actualEvents;      //epoll_wait()返回的_fd上的实际EPOLL事件

    bool _isTied;
    std::weak_ptr<void> _tie;
    bool _isHandlingEvent;

    EventCallback _readCallback;
    EventCallback _writeCallback;
    EventCallback _closeCallback;
    EventCallback _errorCallback;
};