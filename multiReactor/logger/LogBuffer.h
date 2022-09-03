#pragma once
#include<cstring>


class LogBuffer
{
public:
    LogBuffer(size_t total = 1024*1024*10):_total(total), _available(total), _cur(0){
        _data=new char[total];
    }
    ~LogBuffer(){
        delete[] _data;
    }

    void append(const char *data, size_t len){      //将data的数据追加到LogBuffer中的_data后面
        memcpy(_data + _cur, data, len);
        _cur += len;
        _available -= len;
    }
    void clear(){ _cur=0; _available=_total; }
    const char *data() const { return _data;}
    size_t length() const { return _cur;}
    size_t available() const{ return _available;}
    
private:
    char *_data;
    const size_t _total;
    size_t _available;
    size_t _cur;
};