#include"Channel.h"


Channel::Channel(int fd, EventLoop* loop)
:_fd(fd)
,_loop(loop)
,_events(0)
,_isTied(false)
,_isHandlingEvent(false)
{}

Channel::~Channel()
{}

void Channel::tie(const std::shared_ptr<void> &obj){
    _tie = obj;
    _isTied = true;
}

void Channel::handleEvent(){
    if(_isTied){
        std::shared_ptr<void> guard = _tie.lock();
        if(guard){
            handleEventWithGuard();
        }
    }
    else{
        handleEventWithGuard();
    }
}

void Channel::handleEventWithGuard()
{
    _isHandlingEvent = true;

    if(_events & (EPOLLIN | EPOLLPRI)){
        _readCallback();
    }
    else if(_events & EPOLLOUT){
        _writeCallback();
    }
    else if(_events & EPOLLHUP){
        _closeCallback();
    }
    else{
        _errorCallback();
    }

    _isHandlingEvent = false;
}