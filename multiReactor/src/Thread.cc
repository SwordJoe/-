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

    _thread = shared_ptr<thread>(new thread([&](){
        _tid = CurrentThread::tid();
        sem_post(&sem);

        _func();
    }));

    sem_wait(&sem);
}

void Thread::join(){
    _joined = true;
    _thread->join();
}