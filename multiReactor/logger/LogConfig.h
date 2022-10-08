#pragma once
#include<stdint.h>
#include<string>
#include<unistd.h>
using namespace std;

enum LogLevel{      //日志级别
    DEBUG = 1,
    INFO = 2,
    WARN = 3,
    ERROR = 4,
    FATAL = 5
};

struct LogConfig{
    LogConfig(uint32_t log_buffer_size = 4096,
            uint32_t log_buffer_nums = 2,
            LogLevel log_level = LogLevel::DEBUG,
            const string &log_path = string(getcwd(nullptr,0))+"/",
            uint32_t log_roll_fileSize = 1024 * 1024 * 10,  //10M
            uint32_t log_flush_interval = 3)
    :logBufferSize(log_buffer_size)
    ,logBufferNums(log_buffer_nums)
    ,logLevel(log_level)
    ,logPath(log_path)
    ,logRollFileSize(log_roll_fileSize)
    ,logFlushInterval(log_flush_interval)
    {}

    uint32_t logBufferSize;                   //日志buffer大小
    uint32_t logBufferNums;                  //日志buffer数量
    LogLevel logLevel;                        //日志级别
    string logPath;                         //日志存放的目录
    uint32_t logRollFileSize;               //滚动日志需要达到的文件大小
    uint32_t logFlushInterval;              //刷盘的时间间隔
};

using LogConfig = struct LogConfig;

