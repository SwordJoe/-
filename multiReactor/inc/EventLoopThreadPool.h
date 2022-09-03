#pragma once
#include"EventLoopThread.h"
#include<vector>
#include<memory>
#include<functional>
using namespace std;

class EventLoop;
class EventLoopThread;

class EventLoopThreadPool
{
public:
    EventLoopThreadPool(EventLoop *mainLoop);
    ~EventLoopThreadPool() = default;

    void setThreadNum(int num){ _threadsNum = num;}
    EventLoop* getNextLoop();
    void start();
    bool started() const {  return _started;}

private:
    EventLoop* _mainLoop;
    bool _started;
    int _threadsNum;
    int _next;
    vector<unique_ptr<EventLoopThread>> _threads;
    vector<EventLoop*> _loops;
};