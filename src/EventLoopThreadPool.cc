#include"EventLoopThreadPool.h"
#include"EventLoop.h"

EventLoopThread::EventLoopThread()
{}

EventLoopThread::~EventLoopThread()
{
    _loop->quitLoop();
    _thread->join();
}

void EventLoopThread::start()
{
    _thread = std::make_shared<std::thread>(&EventLoopThread::threadFunc,this);
}

void EventLoopThread::threadFunc()
{
    EventLoop loop;
    _loop = &loop;      //this->_loop = &loop，线程中生成一个EventLoop的栈变量，将该栈变量交给EventLoopThread的_loop成员变量
    loop.loop();
}





EventLoopThreadPool::EventLoopThreadPool(EventLoop* mainLoop)
:_mainLoop(mainLoop)
,_nextId(0)
,_threadsNum(0)
{}

EventLoopThreadPool::~EventLoopThreadPool()
{}

void EventLoopThreadPool::start()
{
    for(int i=0; i<_threadsNum; ++i){
        _threadPool.push_back(std::unique_ptr<EventLoopThread>(new EventLoopThread));
        _threadPool[i]->start();
    }
}

EventLoop* EventLoopThreadPool::getNextLoop()
{
    if(_threadsNum == 0){
        return _mainLoop;
    }
    return _threadPool[(_nextId+1)%_threadsNum]->getLoop();
}