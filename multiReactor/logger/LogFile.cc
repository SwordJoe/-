#include"LogFile.h"

#include<errno.h>
#include<fcntl.h>
#include<cstdio>
#include<cstring>
#include<sys/socket.h>
#include<sys/types.h>
#include<iostream>
using namespace std;

class AppendFileWriter : public FileWriter
{
public:
    AppendFileWriter( const string &fileName)
    :_fp(::fopen(fileName.c_str(), "ae"))
    {
        setbuffer(_fp,_buffer,sizeof(_buffer));     //将写入_buffer的数据流写入_fp
    }
    ~AppendFileWriter(){
        if(_fp){
            fclose(_fp);
        }    
    }
    void append(const char *msg, int32_t len){
        size_t n=fwrite_unlocked(msg,1,len,_fp);    //fwrite的线程不安全版本，但是速度快
        size_t remain=len-n;
        while(remain>0){
            size_t x = fwrite_unlocked(msg+n, 1, remain, _fp);
            if(x == 0){
                int err=ferror(_fp);        //测试文件流_fp是否有错误
                if(err){
                    fprintf(stderr,"AppendFile::append() failed %s\n", strerror(err));
                }
                break;
            }
            n += x;             //总共写入n字节
            remain -= x;   //还剩reamin字节
        }

        _writen += len;
    }
    void flush(){ fflush(_fp); }
    uint32_t writtenBytes() const { return _writen; }
    
private:
    FILE *_fp;
    char _buffer[64*1024];
    uint32_t _writen = 0;       //记录总共写入文件字节数
};


//fileName = baseName + 时间戳 + .log
//e.g. ///LOGGER/20220824-17:27:23.log
string getLogFileName(const string &baseName, time_t *now){
    string fileName;
    
    fileName.reserve(baseName.size() + 64);
    fileName = baseName;

    char timeBuf[32];
    struct tm tm;
    *now=time(nullptr);     
    gmtime_r(now, &tm);
    strftime(timeBuf, sizeof(timeBuf), "%Y%m%d-%H:%M:%S", &tm);
    fileName+=timeBuf;

    fileName += ".log";

    return fileName;
}


LogFile::LogFile(const string &logPath, int32_t rollSize, int32_t flushInterval, int32_t checkInterval)
:_logPath(logPath)
,_rollSize(rollSize)
,_flushInterval(flushInterval)
,_checkCnt(checkInterval)
,_logCnt(0)
,_startOfPeriod(0)
,_lastRoll(0)
,_lastFlush(0)
{
    time_t now = 0;
    string fileName = getLogFileName(_logPath, &now);  //获取日志文件名
    _fileWriter=make_shared<AppendFileWriter>(fileName);
    rollFile();         
}


//将内存中的msg写入文件中
void LogFile::writeToFile(const char *msg, int32_t len){
    _fileWriter->append(msg,len);
    //如果写入日志文件的字节数大于规定的日志文件滚动字节数，滚动日志
    if(_fileWriter->writtenBytes() > _rollSize){  
        rollFile();
        cout<<"当前日志文件容量超过阈值，滚动一次"<<endl;
        cout<<"日志大小："<<_fileWriter->writtenBytes()/1024/1024<<"M"<<endl<<endl<<endl;

    }
    else{
        ++_logCnt;   //写入日志的条数+1
        cout<<"已经写入"<<_logCnt<<"条日志"<<endl;
        if(_logCnt > _checkCnt){
            cout<<"写入日志条数达到检查阈值，检查一下是否需要滚动日志"<<endl<<endl;
            _logCnt=0;
            time_t now = time(nullptr);
            time_t thisPeriod = now / kRollPerSeconds * kRollPerSeconds;
            if(thisPeriod != _startOfPeriod){       //跨24小时了
                rollFile();
                cout<<"跨24小时了"<<endl<<endl;
            }
            else if(now - _lastFlush > _flushInterval){
                _lastFlush = now;
                _fileWriter->flush();
            }
        }
    }
}

void LogFile::rollFile(){
    time_t now = 0;
    string fileName = getLogFileName(_logPath, &now);
    time_t start = now / kRollPerSeconds * kRollPerSeconds;

    if(now > _lastRoll){        //如果当前时间 > 上次滚动时的时间
        _lastRoll = now;        
        _lastFlush = now;
        _startOfPeriod = start; //重设跨天标志

        //新建一个AppendFileWriter,也就是重新打开一个日志文件准备写入
        _fileWriter.reset(new AppendFileWriter(fileName));  
    }
}

void LogFile::flush(){
    _fileWriter->flush();
}