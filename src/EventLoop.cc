#include"EventLoop.h"
#include"Channel.h"
#include<iostream>
#include<unistd.h>
#include<assert.h>
#include<sys/eventfd.h>
#include<stdio.h>
#include<errno.h>
#include<iostream>
//__thread EventLoop* _loopInThisThread = nullptr;

EventLoop::EventLoop()
:_isLooping(false)
,_threadId(std::this_thread::get_id())
,_eventfd(::eventfd(0, EFD_NONBLOCK | EFD_CLOEXEC))
,_wakeupChannel(new Channel(_eventfd, this))
,_epfd(epoll_create1(EPOLL_CLOEXEC))
,_events(16)
,_timerQueue(new TimerQueue(this))
{
    _wakeupChannel->setReadCallback(std::bind(&EventLoop::handleEventfdRead,this));
    
    _wakeupChannel->setEvents(EPOLLIN);
    addChannel(_wakeupChannel.get());
}

EventLoop::~EventLoop()
{
    //_loopInThisThread = nullptr;
}

void EventLoop::loop()
{
    _isLooping = true;
    while(_isLooping){
        _activeChannels.clear();

        int eventsNum = ::epoll_wait(_epfd, &*_events.begin(), _events.size(),-1);
        if(eventsNum < 0){
            perror("epoll_wait");
        }
        for(int i=0; i<eventsNum; ++i){
            Channel* channel = static_cast<Channel*>(_events[i].data.ptr);
            channel->setEvents(_events[i].events);
            _activeChannels.push_back(channel);
        }
        if(eventsNum == _events.size()){
            _events.resize( 2 * _events.size());
        }
        for(auto channel : _activeChannels){
            channel->handleEvent();
        }
        executePendingFunctors();
    }
}

void EventLoop::quitLoop()
{
    _isLooping = false;
    //if(_threadId != std::this_thread::get_id()){
        wakeupLoop();
    //}
}

void EventLoop::runInLoop(Functor cb)
{
    if(_threadId == std::this_thread::get_id()){
        cb();
    }
    else{
        queueInLoop(cb);
    }
}

void EventLoop::queueInLoop(Functor cb)
{
    {
        std::unique_lock<std::mutex> lock(_mutex);
        _pendingFunctors.emplace_back(cb);
    }
    wakeupLoop();
}   

void EventLoop::wakeupLoop()
{
    uint64_t one = 1;
    size_t n = write(_eventfd, &one, sizeof(one));
}

void EventLoop::addChannel(Channel* channel)
{
    epoll_event ev;
    ev.data.fd = channel->fd();
    ev.data.ptr = channel;
    ev.events = channel->events();
    int ret = epoll_ctl(_epfd, EPOLL_CTL_ADD, channel->fd(), &ev);
    if(ret == -1){
        perror("epoll_ctl");
    }
}

void EventLoop::updateChannel(Channel* channel)
{
    epoll_event ev;
    ev.data.fd = channel->fd();
    ev.data.ptr = channel;
    ev.events = channel->events();
    
    int ret = epoll_ctl(_epfd, EPOLL_CTL_MOD, channel->fd(), &ev);
    if(ret == -1){
        perror("epoll_ctl");
    }
}

void EventLoop::deleteChannel(Channel* channel)
{
    epoll_event ev;
    ev.data.fd = channel->fd();
    ev.data.ptr = channel;
    ev.events = channel->events();

    int ret = epoll_ctl(_epfd, EPOLL_CTL_DEL, channel->fd(), &ev);
    if(ret == -1){
        perror("epoll_ctl");
    }
}

void EventLoop::handleEventfdRead()
{
    uint64_t one = 1;
    size_t n = read(_eventfd, &one, sizeof(one));
}

void EventLoop::executePendingFunctors()
{
    std::vector<Functor> functors;
    {
        std::unique_lock<std::mutex> lock(_mutex);
        functors.swap(_pendingFunctors);
    }
    for(auto func : functors){
        func();
    }
    _pendingFunctors.clear();
}


// Timer* EventLoop::runAt(TimeStamp timestamp, TimerCallback cb)
// {
//     //Timer* TimerQueue::addTimer(TimeStamp timeStamp, TimerCallback cb, double interval)
//     return _timerQueue->addTimer(timestamp, cb, 0);
// }

Timer* EventLoop::runAfter(double delay, TimerCallback cb)
{
    TimeStamp timestamp(TimeStamp::now());
    timestamp.addTime(delay);
    return _timerQueue->addTimer(timestamp, cb, 0);
}


Timer* EventLoop::runEvery(double interval, TimerCallback cb)
{
    TimeStamp timestamp(TimeStamp::now());
    timestamp.addTime(interval);
    return _timerQueue->addTimer(timestamp, cb, interval);
}

void EventLoop::cancelTimer(Timer* timer)
{
    _timerQueue->cancelTimer(timer);
}

