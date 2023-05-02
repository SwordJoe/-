#pragma once
#include<thread>
#include<memory>
#include<vector>

class EventLoop;

class EventLoopThread
{
public:
    EventLoopThread();
    ~EventLoopThread();
    void start();
    EventLoop* getLoop() const {return _loop;}

private:
    void threadFunc();

private:
    EventLoop* _loop;
    std::shared_ptr<std::thread> _thread;
};

class EventLoopThreadPool
{
public:
    EventLoopThreadPool(EventLoop* mainLoop);
    ~EventLoopThreadPool();
    void setThreadsNum(int num){_threadsNum = num;}
    void start();
    EventLoop* getNextLoop();

private:
    int _nextId;
    int _threadsNum;
    EventLoop* _mainLoop;

    //std::vector<EventLoop*> _loops;
    std::vector<std::unique_ptr<EventLoopThread>> _threadPool;
};