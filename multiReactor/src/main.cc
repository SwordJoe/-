#include"../inc/TcpServer.h"
#include"../inc/LOGGER.h"
#include"../../Proto/student.pb.h"
#include<string>
#include<functional>
#include<iostream>
using namespace std;
using namespace std::placeholders;

class EchoServer
{
public:
    EchoServer(EventLoop *loop, InetAddress &addr)
    :_server(loop,addr)
    {
        _server.setConnectionCallback(bind(&EchoServer::onConnection,this,_1));
        _server.setMessageCallback(bind(&EchoServer::onMessage, this, _1, _2, _3));
        _server.setThreadsNum(1);
    }

    void start(){
        _server.start();
    }

private:
    void onConnection(const TcpConnectionPtr &conn){
        cout<<conn->peerAddress().toIpPort().c_str();
    }

    void onMessage(const TcpConnectionPtr &conn, Buffer *buff, TimeStamp time){
        string msg = buff->retrieveAllAsString();

        Student stu;
        stu.ParseFromString(msg);
        cout<<stu.DebugString()<<endl;

        stu.set_id(100);
        stu.set_name("swordjoe");
        stu.set_math(99);
        msg = stu.SerializeAsString();

        //对客户端数据进行一些处理......
        //再发送给客户端
        conn->send(msg);
        //conn->shutdown();
    }

private:
    EventLoop *loop;
    TcpServer _server;
};




int main()
{
    EventLoop loop;
    LOG("\t\t\t\tmainLoop地址：%p",&loop);
    InetAddress addr(8888,"172.24.40.165");
    EchoServer server(&loop, addr);
    server.start();
    //loop.loop();

    return 0;
}