#pragma once
#include"TimeStamp.h"
#include"Callbacks.h"
#include"Timer.h"
#include<atomic>


class Timer
{
public:
    Timer(TimeStamp expiration, TimerCallback cb, double interval)
    :_expiration(expiration)
    ,_callback(cb)
    ,_sequence(++_seqNum)
    ,_interval(interval)
    ,_isRepeated(interval > 0)
    {}
    ~Timer() = default;

    void run(){ _callback();}
    bool repeat() const {return _isRepeated;}
    TimeStamp expiration() const{ return _expiration;}
    int64_t sequence() const {return _sequence;}
    
    void restart(){
        if(_isRepeated){
            _expiration.addTime(_interval);
        }
        else{
            _expiration = TimeStamp();
        }
    }

    bool operator< (const Timer& rhs){
        if(!(_expiration == rhs._expiration)){
            return _expiration < rhs._expiration;
        }
        else{
            return _sequence < rhs._sequence;
        }
    }

private:    
    TimeStamp _expiration;          //到期时间
    int64_t _sequence;              //定时器序列号，每个定时器唯一
    TimerCallback _callback;        //定时回调函数
    double _interval;               //重复定时的间隔时间
    bool _isRepeated;               //是否重复定时
    static std::atomic_int64_t _seqNum;
};

//std::atomic_int64_t Timer::_seqNum;