#include"../inc/Buffer.h"
#include<errno.h>
#include<sys/uio.h>
#include<unistd.h>

size_t Buffer::readFd(int fd, int* saveErrno){
    char extraBuf[65536] = {0};     //64K
    struct iovec vec[32];

    size_t writable = writeableBytes();
    vec[0].iov_base = begin() + _writeIndex;
    vec[0].iov_len = writable;

    vec[1].iov_base = extraBuf;
    vec[1].iov_len = sizeof(extraBuf);

    const int iovcnt = (writable < sizeof(extraBuf) ? 2 : 1);
    size_t n = ::readv(fd, vec, iovcnt);
    if(n < 0){
        *saveErrno = errno;
    }
    else if( n < writable){     //如果从客户端读取到的字节数比可写入数据区域字节数少，就直接将可写标志位往后移动
        _writeIndex += n;
    }
    else{       //如果从客户端读取到的字节数比可写入数据区域字节数要大，将extraBuf追加到buffer缓冲区后面，需要对缓冲区扩容
        _writeIndex = _buffer.size();      
        append(extraBuf, n - writable);
    }
    return n;
}



size_t Buffer::writeFd(int fd, int* saveErrno){
    size_t n = ::write(fd, peek(), readableBytes() );
    if(n < 0){
        *saveErrno = errno;
    }
    return n;
}