#include"../inc/EventLoop.h"
#include"../inc/EpollPoller.h"
#include"../inc/Channel.h"
#include"../logger/Log.h"
#include"../inc/LOGGER.h"
#include<sys/eventfd.h>
#include<unistd.h>
#include<fcntl.h>
#include<errno.h>
#include<memory>
using namespace std;

__thread EventLoop* t_loopInThisThread = nullptr;

const int kPollTimeMs = 10000;   //默认的超时时间

int createEventFd(){
    int eventfd = ::eventfd(0, EFD_NONBLOCK | EFD_CLOEXEC);
    if(eventfd < 0){
        //LOGFATAL("eventfd error:%d", errno);
    }
    LOG("\t\t创建eventfd:fd=%d",eventfd);
    return eventfd;
}

EventLoop::EventLoop()
:_looping(false)
,_quit(false)
,_callingPendingFunctors(false)
,_threadId(CurrentThread::tid())
,_poller(new EpollPoller(this))
,_wakeupFd(createEventFd())
,_wakeupChannel(new Channel(this, _wakeupFd))
{
    //LOGDEBUG("create EventLoop %p in thread %d", this, _threadId);
    if(t_loopInThisThread){
        //LOGFATAL("Another EventLoop %p exists in this thread %d", t_loopInThisThread, _threadId);
    }
    else{
        t_loopInThisThread = this;
    }

    //设置wakeupfd的感兴趣事件类型及发生事件后的回调操作
    _wakeupChannel->setReadCallback(bind(&EventLoop::handleRead, this));
    //将负责监听的eventfd添加到epoll监听队列中
    _wakeupChannel->enableRead();
}

EventLoop::~EventLoop(){
    _wakeupChannel->disableAll();
    _wakeupChannel->removeFromEventLoop();
    ::close(_wakeupFd);
    t_loopInThisThread = nullptr;
}

void EventLoop::loop(){
    _looping = true;
    _quit = false;
    //LOGINFO("EventLoop %p start looping", this);
    //LOG("\t\t\t开始loop,loop地址:%p",this);
    while(!_quit){
        _activeChannels.clear();

        _pollReturnTime = _poller->poll(-1, &_activeChannels);           //循环进行epoll_wait()监听，超时时间设置为-1，一直阻塞
        //LOG("\tepoll:%p超时/有事件产生",this);
        for(Channel *channel : _activeChannels){        //处理各个文件描述符中的读写事件
            channel->handleEvent(_pollReturnTime);
        }
        doPendingFunctors();            //如果任务队列中有函数的话，就执行任务函数
    }

    //LOGINFO("EventLoop %p stop looping", this);
    _looping=false;
}

void EventLoop::quitLoop(){
    _quit = true;
    if(!isInLoopThread()){
        wakeup();
    }
}


void EventLoop::runInLoop(Functor cb){
    if(isInLoopThread()){
        cb();
    }
    else{
        queueInLoop(cb);
    }
}

void EventLoop::queueInLoop(Functor cb){
    {
        unique_lock<mutex> lock(_mutex);
        _pendingFunctors.emplace_back(cb);
    }

    if(!isInLoopThread() || _callingPendingFunctors){
        wakeup();
    }
}

void EventLoop::handleRead(){
    uint64_t one = 1;
    ssize_t n = read(_wakeupFd,&one, sizeof(one));
    if(n != sizeof(one)){
        //LOGERROR("read error:%d",errno);
    }
}

void EventLoop::wakeup(){
    uint64_t one = 1;
    ssize_t n = write(_wakeupFd, &one, sizeof(one));
    if(n != sizeof(one)){
        //LOGERROR("write error:%d",errno);
    }
}

void EventLoop::updateChannel(Channel *channel){
    _poller->updateChannel(channel);
}

void EventLoop::removeChannel(Channel *channel){
    _poller->removeChannel(channel);
}

void EventLoop::doPendingFunctors(){
    vector<Functor> functors;
    _callingPendingFunctors = true;

    {//加锁的目的：子线程执行自己的任务队列，此时其他线程可能还会往自己的任务队列中放入任务函数
    //比如主线程可能还会添加任务函数，所以此时需要互斥访问，采用交换指针的操作，减少加锁的颗粒度
        unique_lock<mutex> lock(_mutex);
        functors.swap(_pendingFunctors);
    }

    for(const Functor &functor : functors){
        functor();
    }

    _callingPendingFunctors = false;
}