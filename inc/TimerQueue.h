#pragma once
#include"Channel.h"
#include"Timer.h"
#include"TimeStamp.h"
#include<set>
#include<memory>
#include<vector>

class EventLoop;
class Timer;

struct Cmp
{
    bool operator() (const Timer* lhs, const Timer* rhs) const{
        if(!(lhs->expiration() == rhs->expiration())){
            return lhs->expiration() < rhs->expiration();
        }
        else{
            return lhs->sequence() < rhs->sequence();
        }
    }
};

class TimerQueue
{
public:
    TimerQueue(EventLoop* loop);
    ~TimerQueue();
    
    //添加一个定时器
    Timer* addTimer(TimeStamp timeStamp, TimerCallback cb, double interval);
    void cancelTimer(Timer*);

private:
    void handleRead();
    void addTimerInLoop(Timer* timer);
    void cancelTimerInLoop(Timer* timer);

    //重置_timerfd的到期时间
    void resetTimerfd(TimeStamp expiration);
    //重置部分到期定时器
    void reset(std::vector<Timer*>& expirationTimers);
    
    

private:
    EventLoop* _loop;
    int _timerfd;
    Channel _timerChannel;
    std::set<Timer*,Cmp> _timers;
    std::set<Timer*> _cancelingTimers;
};