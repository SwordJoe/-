#include"../inc/EventLoopThread.h"
#include"../inc/EventLoop.h"
#include<functional>

EventLoopThread::EventLoopThread()
:_loop(nullptr)
,_exiting(false)
,_mutex()
,_cond()
,_thread(bind(&EventLoopThread::threadFunc,this))
{

}

EventLoopThread::~EventLoopThread(){
    _exiting = true;
    if(_loop != nullptr){
        _loop->quitLoop();
        _thread.join();
    }
}

EventLoop* EventLoopThread::startLoop(){
    _thread.start();
    
    EventLoop* loop = nullptr;
    {
        unique_lock<mutex> lock(_mutex);
        while(_loop == nullptr){
            _cond.wait(lock);
        }
        loop = _loop;
    }
    return loop;
}

void EventLoopThread::threadFunc(){
    EventLoop loop;
    {
        unique_lock<mutex> lock(_mutex);
        _loop = &loop;
        _cond.notify_one();
    }

    loop.loop();
    unique_lock<mutex> lock(_mutex);
    _loop = nullptr;
}