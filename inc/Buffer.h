#pragma once
#include<vector>
#include<string>
#include<algorithm>

class Buffer
{
public:
    Buffer():_buffer(1024),_readIndex(0),_writeIndex(0){}
    ~Buffer() = default;

    size_t readableBytes() const { return _writeIndex - _readIndex;}
    size_t writeableBytes() const { return _buffer.size() - _writeIndex;}
    
    size_t readFd(int fd, int* savedErrno);
    size_t writeFd(int fd, int* savedErrno);
    
    std::string retrieveAllAsString(){
        return retrieveAsString(readableBytes());
    }

    std::string retrieveAsString(size_t len){
        std::string str(&*_buffer.begin(), len);
        retrieve(len);
        return str;
    }

    void retrieve(size_t len){
        if(readableBytes() > len){
            _readIndex += len;
        }else{
            retrieveAll();
        }
    }

    void retrieveAll(){
        _readIndex = _writeIndex = 0;
    }

    void append(const char *data, size_t len){
        if(writeableBytes() < len){
            expandSpace(len);
        }
        std::copy(data, data+len, &*_buffer.begin()+_writeIndex);
        _writeIndex += len;
    }

    void expandSpace(size_t len){
        if(writeableBytes() + _readIndex < len){
            _buffer.resize(_writeIndex + len);
        }
        else{
            size_t readable = readableBytes();
            std::copy(&*_buffer.begin()+_readIndex, &*_buffer.begin()+_writeIndex, &*_buffer.begin());
            _readIndex = 0;
            _writeIndex = readable;
        }
    }

private:
    std::vector<char> _buffer;
    size_t _readIndex;
    size_t _writeIndex;
};