#pragma once
#include<thread>
#include<functional>
#include<memory>
#include<string>
#include<atomic>
#include<unistd.h>
using namespace std;


class Thread
{
    using ThreadFunc = function<void()>;
public:
    Thread(ThreadFunc);
    ~Thread();

    void start();
    void join();

    bool started() const { return _started;}
    pid_t tid() const {return _tid;}

    static int threadNum(){ return _threadCnt;}

private:
    bool _started;
    bool _joined;
    shared_ptr<thread> _thread;
    pid_t _tid;
    ThreadFunc _func;
    static atomic_int _threadCnt;
};

