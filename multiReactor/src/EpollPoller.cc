#include"../inc/EpollPoller.h"
#include"../logger/Log.h"
#include"../inc/LOGGER.h"

const int kNew = 0;    //Channel未添加到poller中, 对应Channel中_state = -1;
const int kAdded = 1;   //Channel已添加到poller中
const int kDeleted = -1;  //Channel已从poller中删除

EpollPoller::EpollPoller(EventLoop *loop)
:_ownerLoop(loop)
,_epollfd(epoll_create1(EPOLL_CLOEXEC))
,_events(kInitEventSize)
{
    if(_epollfd < 0 ){
        ////LOGFATAL("epoll_create error:%d",errno);
    }
}

EpollPoller::~EpollPoller(){
    ::close(_epollfd);
}

//开启监听
TimeStamp EpollPoller::poll(int timeOuts, ChannelList *activeChannels){
    int numEvents = epoll_wait(_epollfd, &*_events.begin(), _events.size(), timeOuts);
    int saveErrno = errno;
    TimeStamp now(TimeStamp::now());

    if(numEvents > 0){
        fillActiveChannels(numEvents, activeChannels);
        if(numEvents == _events.size()){    //扩容
            _events.resize(_events.size() * 2);
        }
    }
    else if(numEvents == 0){
    }
    else{
        if(saveErrno != EINTR){
            errno = saveErrno;
        }
    }
    return now;
}

//更新fd事件
void EpollPoller::updateChannel(Channel *channel){
    const int state = channel->state();

    if(state == kNew || state == kDeleted){       //channel未被添加到epoll中或者已经被删除了
        if(state == kNew){
            int fd = channel->fd();
            _channels[fd] = channel;
        }
        channel->setState(kAdded);
        update(EPOLL_CTL_ADD, channel);
        LOG("\t\t注册一个fd,fd=%d", channel->fd());
    }
    else{                   //channel已经在epoll中
        int fd =channel->fd();
        if(channel->isNoneEvent()){
            update(EPOLL_CTL_DEL, channel);
            channel->setState(kDeleted);
        }
        else{
            update(EPOLL_CTL_MOD, channel);
        }
    }
}

//从epoll监听队列移除fd
void EpollPoller::removeChannel(Channel *channel){
    int fd = channel->fd();
    _channels.erase(fd);
    //LOGINFO("erase a channel:%d",fd);
    
    int state = channel->state();
    if(state == kAdded){
        update(EPOLL_CTL_DEL, channel);
    }
    channel->setState(kNew);
}

//填写活跃的连接
void EpollPoller::fillActiveChannels(int eventsNum, ChannelList *activeChannels) const{
    for(int i=0; i<eventsNum; ++i){
        Channel *channel = static_cast<Channel*>(_events[i].data.ptr);
        channel->setEvents(_events[i].events);
        activeChannels->push_back(channel);
    }
}

//更新channel通道，epoll_ctl add mod del
void EpollPoller::update(int operation, Channel *channel){
    epoll_event event;
    bzero(&event, sizeof(event));

    int fd = channel->fd();
    event.events = channel->events();
    event.data.fd = fd;
    event.data.ptr = channel;

    int ret=::epoll_ctl(_epollfd, operation, fd, &event);
    if(ret<0){
        if(operation == EPOLL_CTL_DEL){
            //LOGFATAL("epoll_ctl del error:%d", errno);
        }
        else{
            //LOGFATAL("epoll_ctl add/mod error:%d",errno);
        }    
    }
}