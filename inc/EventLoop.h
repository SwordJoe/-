#pragma once 
#include"Callbacks.h"
#include<thread>
#include<memory>
#include<vector>
#include<unordered_map>
#include<mutex>
#include<functional>
#include<sys/epoll.h>

class Channel;

class EventLoop
{
public:
    EventLoop();
    ~EventLoop();

    void loop();
    void quitLoop();

    void runInLoop(Functor cb);
    void queueInLoop(Functor cb);

    void wakeupLoop();

    void addChannel(Channel* channel);
    void deleteChannel(Channel* channel);
    void updateChannel(Channel* channel);

    //判断EventLoop是否在本线程执行
    bool isInLoopThread() const {return _threadId == std::this_thread::get_id();}

private:
    void handleEventfdRead();           
    void executePendingFunctors();  

private:
    int _epfd;              //epollfd
    int _eventfd;           //用于唤醒epoll_wait()的eventfd
    bool _isLooping;        
    std::mutex _mutex;      //互斥锁，添加任务函数时保证互斥                 
    std::thread::id _threadId;                  //EventLoop所在线程的id
    std::unique_ptr<Channel> _wakeupChannel;    //包装_eventfd的Channel    
    std::vector<Channel*> _activeChannels;      //epoll_wait()返回后的活跃Channel,也就是活跃fd
    std::vector<Functor> _pendingFunctors;      //epoll_wait()返回之后，需要执行的函数
    std::vector<epoll_event> _events;           //传递给epoll_wait()的第二个参数
    //std::unordered_map<int,Channel*> _allChannels;        //这个变量应该不需要
};