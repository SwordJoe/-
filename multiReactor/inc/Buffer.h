#pragma once
#include<vector>
#include<string>
#include<algorithm>
using namespace std;


class Buffer
{
public:
    static const size_t kCheapPrepend = 8;
    static const size_t kInitialSize = 1024;

    Buffer(size_t initialSize = kInitialSize)
    :_buffer(kCheapPrepend + initialSize)
    ,_readIndex(kCheapPrepend)
    ,_writeIndex(kCheapPrepend)
    {}

    size_t readableBytes() const{
        return _writeIndex - _readIndex;
    }
    size_t writeableBytes() const{
        return _buffer.size() - _writeIndex;
    }
    size_t prependableBytes() const{
        return _readIndex;
    }
    char* peek() {
        return begin() + _readIndex;
    }

    //Buffer中的数据被读走了，将readIndex往后移动
    void retrieve(size_t len){      //可读区域已经被读走，取回这部分数据
        if(readableBytes() > len){
            _readIndex += len;
        }
        else{
            retrieveAll();
        }
    }
    void retrieveAll(){
        _readIndex = _writeIndex = kCheapPrepend;
    }

    //从Buffer中取出数据，以string格式返回
    string retrieveAllAsString(){
        return retrieveAsString(readableBytes());
    }
    string retrieveAsString(size_t len){
        string str(peek(),len);
        retrieve(len);
        return str;
    }

    //保证Buffer中可写区域的大小
    void ensureWriteableBytes(size_t len){
        if(writeableBytes()<len){
            makeSpace(len);
        }
    }

    void append(const char *data, size_t len){
        ensureWriteableBytes(len);
        copy(data, data + len, beginWrite());
        _writeIndex += len;
    }

    char* beginWrite(){
        return begin() + _writeIndex;
    }

    size_t readFd(int fd, int* saveErrno);
    size_t writeFd(int fd, int* saveErrno);

private:
    char* begin(){
        return &*_buffer.begin();
    }

    void makeSpace(size_t len){
        if(writeableBytes() + prependableBytes() < len + kCheapPrepend){
            _buffer.resize(_writeIndex + len);
        }
        else{
            size_t readable = readableBytes();
            copy(begin() + _readIndex, begin() + _writeIndex, begin() + kCheapPrepend);
            _readIndex = kCheapPrepend;
            _writeIndex = _readIndex + readable;
        }
    }
    


private:
    vector<char> _buffer;
    size_t _readIndex;
    size_t _writeIndex;
};