#include"Buffer.h"
#include<sys/uio.h>
#include<stdio.h>
#include<errno.h>
#include<unistd.h>

size_t Buffer::readFd(int fd, int* savedErrno)
{
    char extraBuf[65536] = {0};
    struct iovec vec[32];

    size_t writeable = writeableBytes();
    vec[0].iov_base = &*_buffer.begin() + _writeIndex;
    vec[0].iov_len = writeable;

    vec[1].iov_base = extraBuf;
    vec[1].iov_len = sizeof(extraBuf);

    const int iovcnt = (writeable < sizeof(extraBuf) ? 2 : 1);
    size_t n = ::readv(fd, vec, iovcnt);
    if(n < 0){
        *savedErrno = errno;
    }
    else if( n <= writeable){
        _writeIndex += n;
    }
    else{
        _writeIndex = _buffer.size();
        append(extraBuf, n - writeable);
    }
    return n;
}

size_t Buffer::writeFd(int fd, int* savedErrno)
{
    //直接先调用原生::write()写入fd
    size_t n = ::write(fd, &*_buffer.begin()+_readIndex, readableBytes());
    retrieve(n);    //写入n个字节后立马紧缩_buffer的空间
    return n;
}