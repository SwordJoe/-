#include"LogAsyncAppender.h"
#include"Log.h"
#include"LogFile.h"
#include<cstring>
#include<unistd.h>
#include<sys/stat.h>
#include<assert.h>
#include<iostream>
#include<chrono>
using namespace std;

LogAsyncFileAppender::LogAsyncFileAppender(const string &logPath)
:_started(false)
,_running(false)
,_flushInterval(kLogConfig.logFlushInterval)
,_logPath(logPath)
,_curBuffer(new LogBuffer(kLogConfig.logBufferSize))
,_dumpToFileThread(bind(&LogAsyncFileAppender::threadFunc, this))
{
    mkdir(_logPath.c_str(),0755);
    start();
}

LogAsyncFileAppender::~LogAsyncFileAppender(){
    if(_started){
        stop();
    }
}

void LogAsyncFileAppender::start(){
    _started = true;
    _running = true;
    _dumpToFileThread.start();
}

void LogAsyncFileAppender::stop(){
    _started = false;
    //_running = false;         //延迟将_running置为false
    _cond.notify_one();
    _dumpToFileThread.join();
}

//将日志消息追加到当前的内存buffer中，需要加锁，因为可能会有多个线程同时写入这一块buffer
void LogAsyncFileAppender::append(const char *logMsg, size_t len){
    //lock_guard<mutex> lock(_mutex);
    unique_lock<mutex> Lock(_mutex);
    //Lock.lock();
    
    if(_curBuffer->available() >= len){     
        _curBuffer->append(logMsg,len);    //将日志消息追加到自定义内存buffer中
    }
    else{   //如果当前内存buffer剩余空间不足够存放logMsg
        _buffers.push_back(std::move(_curBuffer));    //先将当前buffer指针移动到_buffers中等待刷盘

        _curBuffer.reset(new LogBuffer(kLogConfig.logBufferSize));   //重新申请一块buffer 
        _curBuffer->append(logMsg, len);
        _cond.notify_one();        
    }

    //Lock.unlock();
}

void LogAsyncFileAppender::threadFunc(){
    unique_ptr<LogBuffer> newBuffer(new LogBuffer(kLogConfig.logBufferSize));
    vector<unique_ptr<LogBuffer>> buffersToDump;            //准备dump到磁盘的buffer，其中存放的是LogBuffer指针
    buffersToDump.reserve(kLogConfig.logBufferNums);

    //参数:基础日志文件名，日志滚动需满足的日志文件大小， 日志刷盘间隔， 日志写入条数的检查阈值
    LogFile logFile(_logPath, kLogConfig.logRollFileSize, kLogConfig.logFlushInterval, 1024);    

    while(_running){
        {
            unique_lock<mutex> Lock(_mutex);
            //Lock.lock();

            if(_buffers.empty()){
                chrono::duration<int> interval(3);
                _cond.wait_for(Lock, interval);
                cout<<"3秒检查一次"<<endl;
            }
            if(_buffers.empty() && _curBuffer->length() == 0){
                //Lock.unlock(); 
                continue;
            }

            _buffers.push_back(std::move(_curBuffer));      //将_curBuffer转移到_buffers中
            buffersToDump.swap(_buffers);                   //交换前后端的buffer池
            _curBuffer = std::move(newBuffer);              //将后端的buffer转移给前端的_curBuffer,以供写日志
            _curBuffer->clear();

            //Lock.unlock();   
        }
                                       
        for(const auto &buffer : buffersToDump){
            logFile.writeToFile(buffer->data(), buffer->length());
        }

        //重置后端的buffer和buffer池
        newBuffer = std::move(buffersToDump[0]);
        newBuffer->clear();
        buffersToDump.clear();

        logFile.flush();

        if(!_started){      //延迟置_running为false，防止当前_curbuffer中还有数据没有dumpToFile
            lock_guard<mutex> guard(_mutex);
            if(_curBuffer->length() == 0){
                _running = false;
            }
        }
    }
    logFile.flush();
}

