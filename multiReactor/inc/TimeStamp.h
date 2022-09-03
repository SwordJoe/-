#pragma once

#include <iostream>
#include <string>
using namespace std;

// 时间类
class TimeStamp
{
public:
    TimeStamp();
    explicit TimeStamp(int64_t microSecondsSinceEpoch);
    static TimeStamp now();
    string toString() const;
private:
    int64_t microSecondsSinceEpoch_;
};