#include"TcpServer.h"
#include<iostream>
using namespace std;

EventLoop* g_loop;

void print(int a){
    cout<<a<<endl;
}

void cancel(Timer* timer)
{
    g_loop->cancelTimer(timer);
}

int main()
{
    EventLoop loop;
    g_loop = &loop;
    //loop.runAfter(2,std::bind(&print, 100));
    Timer* timer = loop.runEvery(1,std::bind(&print, 666666666));
    loop.runAfter(10,std::bind(&cancel, timer));
    loop.loop();
}