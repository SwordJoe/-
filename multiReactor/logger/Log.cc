#include"Log.h"
#include"../inc/TimeStamp.h"

#include<stdarg.h>
#include<cstring>

#include<algorithm>
#include<string>
#include<vector>
using namespace std;

//获取日志级别的字符串
string getLogLevelStr(LogLevel logLevel){
    switch(logLevel){
        case LogLevel::DEBUG:   return "DEBUG";     break;
        case LogLevel::INFO:    return "INFO";      break;
        case LogLevel::WARN:    return "WARN";      break;
        case LogLevel::ERROR:   return "INFO";      break;
        case LogLevel::FATAL:   return "FATAL";     break;
        default:    return "UNKNOWN";
    }
}

//写日志，line50只是写入到内存buffer中，具体写入磁盘文件的时机还需要在AsyncAppender类中进一步操作
void Logger::writeLog(LogLevel logLevel, const char *fileName,
                    const char *functionName, int32_t lineNo,
                    string &logMsg)
{
    if(logLevel < kLogConfig.logLevel){
        return;
    }

    if(logMsg.empty()){
        return;
    }
    //lambda表达式，获取日志文件名，去除前面所有的目录层级
    const auto &getSourceFileName = [](const char *fileName){       
        return strrchr(fileName, '/') ? strrchr(fileName, '/') + 1 : fileName;
    };

    char prefix[128]={0};
    sprintf(prefix,"[%s-%s-%s-%s-%d]\t",
                TimeStamp::now().toString().c_str(),
                getLogLevelStr(logLevel).c_str(),
                getSourceFileName(fileName),
                functionName,
                lineNo);

    logMsg = string(prefix) + logMsg + "\n";        //一条完整的日志信息
    _logAsyncAppender->append(logMsg.data(), logMsg.size());        
}