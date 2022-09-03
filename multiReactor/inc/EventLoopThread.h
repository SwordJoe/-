#pragma once
#include"Thread.h"
#include<mutex>
#include<condition_variable>
using namespace std;

class EventLoop;

class EventLoopThread
{
public:
    EventLoopThread();
    ~EventLoopThread();
    EventLoop* startLoop();

private:
    void threadFunc();

private:
    EventLoop* _loop;
    bool _exiting;
    Thread _thread;
    mutex _mutex;
    condition_variable _cond;
};