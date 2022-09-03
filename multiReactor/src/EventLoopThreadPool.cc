#include"../inc/EventLoopThreadPool.h"
#include"../inc/EventLoopThread.h"
#include"../inc/LOGGER.h"


EventLoopThreadPool::EventLoopThreadPool(EventLoop *mainLoop)
:_mainLoop(mainLoop)
,_started(false)
,_threadsNum(0)
,_next(0)
{}

void EventLoopThreadPool::start(){
    _started = true;
    LOG("\t\t线程池启动");
    for(int i=0; i<_threadsNum; ++i){
        EventLoopThread *th = new EventLoopThread();
        _threads.push_back(unique_ptr<EventLoopThread>(th));
        _loops.push_back(th->startLoop());
    }
}

EventLoop* EventLoopThreadPool::getNextLoop(){
    EventLoop* loop = _mainLoop;

    if(!_loops.empty()){
        loop = _loops[_next];
        _next = (_next+1) % _threadsNum;
    }

    return loop;
}