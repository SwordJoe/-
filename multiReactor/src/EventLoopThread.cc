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

//startLoop函数所有步骤都是在主线程中执行的
EventLoop* EventLoopThread::startLoop(){
    _thread.start();        //在start()函数里才真正地创建了一个线程，在线程里执行下面的threadFunc()函数
    
    EventLoop* loop = nullptr;
    {
        unique_lock<mutex> lock(_mutex);
        while(_loop == nullptr){
            _cond.wait(lock);       //one loop per thread 的EventLoop对象是在线程中创建的，在这里需要等待线程创建好EventLoop对象，然后条件变量发出通知
        }
        loop = _loop;
    }
    return loop;
}


/**
 * @brief 该函数是在子线程中执行的
 * 线程主要就是循环执行loop()，其实也就是循环epoll_wait()
 */
void EventLoopThread::threadFunc(){   
    EventLoop loop;     //在线程栈中产生一个EventLoop对象
    {
        unique_lock<mutex> lock(_mutex);
        _loop = &loop;      //将产生的EventLoop对象交给主线程
        _cond.notify_one();
    }

    loop.loop();
    unique_lock<mutex> lock(_mutex);
    _loop = nullptr;
}