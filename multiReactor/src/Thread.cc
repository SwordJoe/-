#include"../inc/Thread.h"
#include"../inc/CurrentThread.h"
#include<semaphore.h>


atomic_int Thread::_threadCnt(0);

Thread::Thread(ThreadFunc func)
:_started(false)
,_joined(false)
,_tid(0)
,_func(std::move(func))
{}

Thread::~Thread(){
    if(_started && !_joined){
        _thread->detach();
    }
}

void Thread::start(){
    _started = true;
    sem_t sem;
    sem_init(&sem, false, 0);

    _thread = shared_ptr<thread>(new thread([&](){  //27~30行属于子线程执行，此时已经不在主线程中
        _tid = CurrentThread::tid();
        sem_post(&sem);     //设置好线程号_tid，通知主线程，同步操作

        _func();
    }));

    sem_wait(&sem);     //等待子线程将线程号_tid设置好，同步操作
}

void Thread::join(){
    _joined = true;
    _thread->join();
}