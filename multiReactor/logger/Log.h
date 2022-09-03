#pragma once
#include"LogConfig.h"
#include"LogAsyncAppender.h"
#include<string>
#include<memory>
using namespace std;

static LogConfig kLogConfig;

class Logger
{
public:
    Logger():_logAsyncAppender(new LogAsyncFileAppender(kLogConfig.logPath)){}
    ~Logger() = default;
    
    static Logger& getInstance(){
        static Logger logger; 
        return  logger;
    }
    static void setGlobalConfig(const LogConfig &logConfig){
        kLogConfig = logConfig;
    }

    void writeLog(LogLevel logLevel, const char *fileName, 
                const char *functionName, int32_t lineNo, 
                string &logMsg);

private:
    shared_ptr<LogAsyncFileAppender> _logAsyncAppender;
};


#define LOGINFO(fmt, ...)\
do\
{\
    Logger &logger = Logger::getInstance();\
    char buf[1024]={0};\
    int ret = snprintf(buf, 1024, fmt, ##__VA_ARGS__);\
    string logMsg(buf);\
    logger.writeLog(LogLevel::INFO, __FILE__, __FUNCTION__, __LINE__, logMsg); \
}while(0);


#define LOGERROR(fmt, ...)\
do\
{\
    Logger &logger = Logger::getInstance();\
    char buf[1024]={0};\
    int ret = snprintf(buf, 1024, fmt, ##__VA_ARGS__);\
    string logMsg(buf);\
    logger.writeLog(LogLevel::ERROR, __FILE__, __FUNCTION__, __LINE__, logMsg); \
}while(0);


#define LOGDEBUG(fmt, ...)\
do\
{\
    Logger &logger = Logger::getInstance();\
    char buf[1024]={0};\
    int ret = snprintf(buf, 1024, fmt, ##__VA_ARGS__);\
    string logMsg(buf);\
    logger.writeLog(LogLevel::DEBUG, __FILE__, __FUNCTION__, __LINE__, logMsg); \
}while(0);


#define LOGWARN(fmt, ...)\
do\
{\
    Logger &logger = Logger::getInstance();\
    char buf[1024]={0};\
    int ret = snprintf(buf, 1024, fmt, ##__VA_ARGS__);\
    string logMsg(buf);\
    logger.writeLog(LogLevel::WARN, __FILE__, __FUNCTION__, __LINE__, logMsg); \
}while(0);


#define LOGFATAL(fmt, ...)\
do\
{\
    Logger &logger = Logger::getInstance();\
    char buf[1024]={0};\
    int ret = snprintf(buf, 1024, fmt, ##__VA_ARGS__);\
    string logMsg(buf);\
    logger.writeLog(LogLevel::FATAL, __FILE__, __FUNCTION__, __LINE__, logMsg); \
}while(0);



