#pragma once
#include"LogBuffer.h"
#include"../inc/Thread.h"
#include<vector>
#include<mutex>
#include<thread>
#include<condition_variable>
using namespace std;



class LogAsyncFileAppender
{
public:
    LogAsyncFileAppender(const string &baseName);
    ~LogAsyncFileAppender();
    void append(const char *msg, size_t len);
    void start();
    void stop();

private:
    void threadFunc();

    bool _started;
    bool _running;
    time_t _flushInterval;
    string _logPath;

    mutex _mutex;
    condition_variable _cond;
    Thread  _dumpToFileThread;
    unique_ptr<LogBuffer> _curBuffer;               //当前buff，日志都是先写入到当前buff中
    vector<unique_ptr<LogBuffer>> _buffers;         //buffer池
};