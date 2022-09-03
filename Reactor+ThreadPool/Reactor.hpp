#include"TcpServer.hpp"
#include"ThreadPool.hpp"
#include<unistd.h>
#include<signal.h>
#include<iostream>
#include<functional>
using namespace std;
using namespace placeholders;

//任务类
class MyTask
{
public:
    MyTask(const string &msg,const TcpConnectionPtr &conn)
    :_msg(msg)
    ,_conn(conn)
    {}
    //具体的任务处理函数，是在线程池中的一个子线程执行
    void process(){  
        //业务逻辑的处理
        //decode
        //compute
        //encode
        string response=_msg; //假装做了一些处理
        //利用TcpConnection连接发送数据
        //直接调用_conn->send(response)这种发送方式不符合设计要求，发给客户端的数据应该是由IO线程(Reactor所在线程)进行
        //这意味这计算线程需要通知IO线程发送数据，意味着需要线程间通信，利用eventfd
        //做到职责分离，计算线程只用来处理业务逻辑，IO线程用来进行数据的接收和发送
        //将conn中的send方法作为一个回调函数，注册给EventLoop对象
        //因此需要找到EventLoop对象，此时只有TcpConnetcion对象能够知道EventLoop对象的存在
        
        //sendInLoop就是让EventLoop线程进行发送操作，但其是通过调用EventLoop内部的registerInLoop函数来达到这一目的的
        //EventLoop内的registerInLoop函数主要做两件事：1.向EventLoop自己注册发送回调函数 2.通知EventLoop线程进行发送操作
        _conn->sendInLoop(response);
    }

private:
    string _msg;
    TcpConnectionPtr _conn;
};



class ReactorServer
{
public:
    ReactorServer(unsigned short port,const string &ip, size_t threadNum,size_t taskSize)
    :_threadPool(threadNum,taskSize)
    ,_server(port,ip)
    {}
    
    void start(){
        _threadPool.start();
        //因为onConnection的参数TcpConnection只有等到创建时才会传入，所以用到占位符_1
        _server.setAllCallBacks(bind(&ReactorServer::onConnection,this,_1),    
                                bind(&ReactorServer::onMessage,this,_1),
                                bind(&ReactorServer::onClose,this,_1));
        _server.start();
    }

    void onConnection(const TcpConnectionPtr &conn){
        if(conn->fd()==889){
            cout<<conn->toString()<<" has connected!"<<endl;
        }
        cout<<conn->toString()<<" has connected"<<endl;
    }

    //onMessage运行在IO线程(Reactor所在线程)，即消息的接收和发送由Reactor线程来完成，消息的处理交给线程池中的线程来做
    void onMessage(const TcpConnectionPtr &conn){
        //receive
        string msg=conn->receive();
        //cout<<"server receive msg: "<<msg<<endl;
        

        //如果一个连接的消息处理时间过长，就会影响其他连接的响应速度          
        //因此当消息处理时间过长时，需要将其交给ThreadPool中的其他线程处理
        //需要将接收到的消息封装成一个任务，放入线程池
        MyTask task(msg,conn);
        //绑定参数时，要使用task对象，而不能使用&task(即指针)
        //onMessage是由TcpConnection对象调用的，函数调用完后task就会被销毁
        //而线程池中的线程还需要执行process函数，而该函数是成员函数，第一个参数需要用到this指针
        //所以需要将task对象传进去，而不是将此处task对象的地址传进去
        _threadPool.addTask(bind(&MyTask::process,task));
    }

    void onClose(const TcpConnectionPtr &conn){
        // if(conn->fd()==889){
        //     cout<<conn->toString()<<" has closed!"<<endl;
        // }
        cout<<conn->toString()<<" has closed!"<<endl;
    }

private:
    ThreadPool _threadPool;
    TcpServer _server;
};