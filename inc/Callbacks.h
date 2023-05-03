#pragma once
#include<memory>
#include<functional>

class Buffer;
class TcpConnection;

using TcpConnectionPtr = std::shared_ptr<TcpConnection>;
using ConnectionCallback = std::function<void(const TcpConnectionPtr&)>;
using CloseCallback = std::function<void(const TcpConnectionPtr&)>;
using MessageCallback = std::function<void(const TcpConnectionPtr&, Buffer*)>;
using TimerCallback = std::function<void()>;

using EventCallback = std::function<void()>;
using Functor = std::function<void()>;