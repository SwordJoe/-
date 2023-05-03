#include"TimeStamp.h"
#include<sys/time.h>


TimeStamp TimeStamp::now(){
    struct timeval tv;
    gettimeofday(&tv, nullptr);
    int64_t seconds = tv.tv_sec;
    return TimeStamp(seconds * kMicroSecondsPerSecond + tv.tv_usec);
}

void TimeStamp::addTime(double seconds){   
    _microSecondsSinceEpoch += static_cast<int64_t>(seconds * kMicroSecondsPerSecond);
}

std::string TimeStamp::toFormattedTime() const{
    char buf[64] = {0};
    time_t seconds = static_cast<int64_t>(_microSecondsSinceEpoch/kMicroSecondsPerSecond);
    struct tm tm_time;
    gmtime_r(&seconds, &tm_time);

    snprintf(buf, sizeof(buf), "%4d-%02d-%02d %02d:%02d:%02d",
            tm_time.tm_year + 1900, tm_time.tm_mon + 1, tm_time.tm_mday,
            tm_time.tm_hour, tm_time.tm_min, tm_time.tm_sec);

    return buf;
}