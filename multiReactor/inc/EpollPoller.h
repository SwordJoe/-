#pragma once
#include"TimeStamp.h"
#include"Channel.h"
#include<vector>
#include<unordered_map>
#include<sys/epoll.h>
using namespace std;

class EventLoop;

class EpollPoller
{
    using ChannelList = vector<Channel*>;
    using ChannelMap = unordered_map<int, Channel*>;
    using EventList = vector<epoll_event>;

public:
    EpollPoller(EventLoop *loop);
    ~EpollPoller();

    TimeStamp poll(int timeOuts, ChannelList *activeChannels);
    void updateChannel(Channel *channel);       //更新被监听fd的事件
    void removeChannel(Channel *channel);       //从建听队列中移除fd
    
    bool hasChannel(Channel *channel) const{
        auto it = _channels.find(channel->fd());
        return it != _channels.end() && it->second == channel;
    }

private:
    void fillActiveChannels(int eventsNum, ChannelList *activeChannels) const;      //填写活跃的连接
    void update(int operation, Channel *channel);        //更新Channel通道，其实就是更新fd感兴趣的事件

private:
    static const int kInitEventSize = 16;  
    int _epollfd;
    EventList _events;
    EventLoop *_ownerLoop;
    ChannelMap _channels;
};