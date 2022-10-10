#include"../inc/Channel.h"
#include"../inc/EventLoop.h"
#include<sys/epoll.h>

const int Channel::kNoneEvent = 0;
const int Channel::kReadEvent = EPOLLIN|EPOLLPRI;
const int Channel::kWriteEvent = EPOLLOUT;

Channel::Channel(EventLoop *loop, int fd)
:_loop(loop)
,_fd(fd)
,_events(0)
,_revents(0)
,_state(0)      //未被添加到监听队列
,_tied(false)
{}

Channel::~Channel(){}

void Channel::tie(const shared_ptr<void> &obj){
    _tie=obj;
    _tied=true;
}

//更新fd感兴趣的事件
void Channel::update(){
    _loop->updateChannel(this);
}

//将fd从EventLoop中删除
void Channel::removeFromEventLoop(){
    _loop->removeChannel(this);
}

//fd上有事件发生后，调用该函数处理事件
void Channel::handleEvent(TimeStamp recvTime){
    if(_tied){
        shared_ptr<void> guard=_tie.lock();
        if(guard){
            handleEventWithGuard(recvTime);
        }
    }
    else{
        handleEventWithGuard(recvTime);
    }
}


void Channel::handleEventWithGuard(TimeStamp receiveTime)
{
    ////LOG_INFO("channel handleEvent revents:%d\n", revents_);

    if ((_revents & EPOLLHUP) && !(_revents & EPOLLIN)){    //事件
        if (_closeCallback){        
            _closeCallback();
        }
    }

    if (_revents & EPOLLERR){       //错误事件
        if (_errorCallback){
            _errorCallback();
        }
    }

    if (_revents & (EPOLLIN | EPOLLPRI)){   //读事件
        if (_readCallback){
            _readCallback(receiveTime);
        }
    }

    if (_revents & EPOLLOUT){       //写事件
        if (_writeCallback){
            _writeCallback();
        }
    }
}




