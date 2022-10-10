#pragma once
#include"../inc/TimeStamp.h"
#include"../inc/CurrentThread.h"
#include<vector>
#include<mutex>
#include<atomic>
#include<memory>
#include<functional>
using namespace std;

class Channel;
class EpollPoller;

class EventLoop
{
    using Functor = function<void()>;
    using ChannelList = vector<Channel*>;

public:
    EventLoop();
    ~EventLoop();

    void loop();
    void quitLoop();

    void runInLoop(Functor cb);          //在当前loop线程中执行cb
    void queueInLoop(Functor cb);       //将cb放入队列中，唤醒loop所在线程，执行cb

    void wakeup();      //用来唤醒loop所在线程

    void updateChannel(Channel *channel);
    void removeChannel(Channel *channel);
    bool hasChannel(Channel *channel);

    //判断eventLoop对象是否在自己的线程里面
    bool isInLoopThread() const { return _threadId == CurrentThread::tid();}
    TimeStamp pollReturnTime() const { return _pollReturnTime;}

private:
    void handleRead();              //用于唤醒，注册给_wakeupChannel的读事件回调函数
    void doPendingFunctors();      //执行任务队列中的任务函数

private:
    atomic_bool _looping;
    atomic_bool _quit;

    const pid_t _threadId;

    TimeStamp _pollReturnTime;
    std::unique_ptr<EpollPoller> _poller;

    int _wakeupFd;
    unique_ptr<Channel> _wakeupChannel;

    ChannelList _activeChannels;

    atomic_bool _callingPendingFunctors;
    vector<Functor> _pendingFunctors;    
    mutex _mutex;
};