#include"TimerQueue.h"
#include"EventLoop.h"
#include"Timer.h"
#include<sys/timerfd.h>
#include<unistd.h>
#include<string.h>
#include<iostream>

//T自定义Timer的比较器


TimerQueue::TimerQueue(EventLoop* loop)
:_loop(loop)
,_timerfd(::timerfd_create(CLOCK_MONOTONIC, TFD_NONBLOCK | TFD_CLOEXEC))
,_timerChannel(_timerfd, loop)
{
    _timerChannel.setReadCallback(std::bind(&TimerQueue::handleRead, this));
    _timerChannel.setEvents(EPOLLIN);
    _loop->addChannel(&_timerChannel);
}

TimerQueue::~TimerQueue()
{
    _loop->deleteChannel(&_timerChannel);
}

//添加一个定时器
Timer* TimerQueue::addTimer(TimeStamp timeStamp, TimerCallback cb, double interval)
{
    Timer* timer(new Timer(timeStamp, cb, interval));
    _loop->runInLoop(std::bind(&TimerQueue::addTimerInLoop, this, timer));
    return timer;
}

void TimerQueue::addTimerInLoop(Timer* timer)
{
    //如果新加入的定时器的到期时间比_timers中所有定时器的到期时间都小，就重置_timerfd的到期时间
    if(_timers.empty() || timer->expiration() < (*_timers.begin())->expiration()){
        resetTimerfd(timer->expiration());
    }
    _timers.insert(timer);
    std::cout<<"添加一个定时器,_seqNum="<<timer->sequence()<<",到期时间是："<<timer->expiration().toFormattedTime()<<std::endl;
    std::cout<<"当前时间是："<<TimeStamp::now().toFormattedTime()<<std::endl;
}

void TimerQueue::cancelTimer(Timer* timer)
{
    _loop->runInLoop(std::bind(&TimerQueue::cancelTimerInLoop, this, timer));
}

void TimerQueue::cancelTimerInLoop(Timer* timer)
{
    _timers.erase(timer);
    std::cout<<"删除一个定时器"<<std::endl;
}

//重置_timerfd的到期时间
void TimerQueue::resetTimerfd(TimeStamp expiration)
{
    int64_t microSeconds = expiration.microSecondsSinceEpoch() - TimeStamp::now().microSecondsSinceEpoch();
    if(microSeconds < 100){
        microSeconds = 100;
    }
    struct timespec ts;
    ts.tv_sec = static_cast<time_t>(microSeconds/TimeStamp::kMicroSecondsPerSecond);
    ts.tv_nsec = static_cast<long>(microSeconds % TimeStamp::kMicroSecondsPerSecond * 1000);

    struct itimerspec newValue;
    struct itimerspec oldValue;
    memset(&newValue, 0, sizeof(newValue));
    memset(&oldValue, 0, sizeof(oldValue));

    newValue.it_value = ts;
    int ret = timerfd_settime(_timerfd, 0, &newValue, &oldValue);
    if(ret){
        perror("timer_settime");
    }
    std::cout<<"重置一次_timerfd的到期时间"<<std::endl;
}

//处理_timerfd的读事件
void TimerQueue::handleRead()
{
    uint64_t one;
    ssize_t n = ::read(_timerfd, &one, sizeof(one));
    Timer sentry(TimeStamp::now(),[](){}, 0);
    std::cout<<"读_timerfd,当前时间是:"<<sentry.expiration().toFormattedTime()<<"  "<<sentry.expiration().microSecondsSinceEpoch()<<std::endl;
    // Timer* sentry(new Timer(TimeStamp::now(), [](){}, 0));
    auto it = _timers.begin();
    int i = 1;
    while(it != _timers.end()){
        std::cout<<"第"<<i++<<"个定时器，到期时间是："<<(*it)->expiration().toFormattedTime()<<"  "<<(*it)->expiration().microSecondsSinceEpoch()<<std::endl;
        it++;
    }
    std::set<Timer*>::iterator endIter = _timers.lower_bound(&sentry);
    if(endIter == _timers.end()){
        std::cout<<"末尾"<<std::endl;
    }else{
        std::cout<<"endIter到期时间是："<<(*endIter)->expiration().toFormattedTime()<<std::endl;
    }
    std::vector<Timer*> expirationTimers;
    std::copy(_timers.begin(), endIter, back_inserter(expirationTimers));
    _timers.erase(_timers.begin(), endIter);

    for(auto& timer : expirationTimers){
        timer->run();
    }
    //检查这些到期定时器是否有重复定时的，若有就重置这些定时器的到期时间，再重新插入_timers
    reset(expirationTimers);
}

void TimerQueue::reset(std::vector<Timer*>& expirationTimers)
{
    for(auto& timer : expirationTimers){ 
        if(timer->repeat() && _cancelingTimers.find(timer) == _cancelingTimers.end()){
            timer->restart();
            _timers.insert(timer);
        }
        else{
            delete timer;
        }
    }

    TimeStamp nextExpiration;
    if(!_timers.empty()){       //取出所有定时器中最近的到期时间
        nextExpiration = (*_timers.begin())->expiration();
        if(nextExpiration.microSecondsSinceEpoch() > 0){
            resetTimerfd(nextExpiration);
        }
    }
}