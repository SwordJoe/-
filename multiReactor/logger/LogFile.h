#pragma once

#include<memory>
#include<string>
#include<sys/time.h>
using namespace std;


class FileWriter
{
public:
    FileWriter() = default;
    virtual ~FileWriter() = default;
    virtual void append(const char *msg, int32_t len) = 0;
    virtual void flush() = 0;
    virtual uint32_t writtenBytes() const = 0;
};


class LogFile
{
public:
    LogFile(const string &baseName, int32_t rollSize, int32_t flushInterval, int32_t checkInterval);
    ~LogFile() = default;

    void writeToFile(const char *logMsg, int32_t len);
    void flush();                   //刷新fp
    void rollFile();                //滚动日志

private:
    string _logPath;
    uint32_t _rollSize;             //单个日志的最大容量
    uint32_t _flushInterval;        //刷盘间隔
    uint32_t _checkCnt;             //写入本日志文件条数的检查阈值，写入超过该条数日志就需要检查是否跨天了
    uint32_t _logCnt;        //已经写入本日志文件的条数                  
    
    time_t _startOfPeriod;           
    time_t _lastRoll;     //上次滚动日志的时间
    time_t _lastFlush;    //上次刷新日志的时间
    shared_ptr<FileWriter> _fileWriter;       //用于向磁盘写入的fileWriter;
    constexpr static int kRollPerSeconds =60*60*24;    //设置日志滚动时间
};