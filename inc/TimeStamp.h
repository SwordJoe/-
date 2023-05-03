#pragma once
#include<stdio.h>
#include<stdint.h>
#include<string>

class TimeStamp
{
public:
    TimeStamp(int64_t microSeconds = 0):_microSecondsSinceEpoch(microSeconds){}
    ~TimeStamp(){}

    //当前时间
    static TimeStamp now();
    //增加时间   
    void addTime(double seconds);
    //格式化输出"年-月-日-时-分-秒"
    std::string toFormattedTime() const;

    int64_t microSecondsSinceEpoch() const {return _microSecondsSinceEpoch;}

    bool operator< (const TimeStamp& rhs){
        return _microSecondsSinceEpoch < rhs._microSecondsSinceEpoch;
    }
    bool operator== (const TimeStamp& rhs){
        return _microSecondsSinceEpoch == rhs._microSecondsSinceEpoch;
    }

    static const int kMicroSecondsPerSecond = 1000 * 1000;

private:
    int64_t _microSecondsSinceEpoch;
};