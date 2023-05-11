cmake_minimum_required(VERSION 3.5)

project(http_server)

set(SOURCES 
    ../../src/Buffer.cc
    ../../src/Channel.cc
    ../../src/EventLoop.cc 
    ../../src/InetAddress.cc
    ../../src/TcpConnection.cc
    ../../src/TcpServer.cc
    ../../src/EventLoopThreadPool.cc
    ../../src/TimeStamp.cc
    ../../src/TimerQueue.cc
    ../../src/Timer.cc
    src/HttpContext.cc
    src/HttpResponse.cc
    src/HttpServer.cc
    )


set(CMAKE_CXX_FLAGS -pthread)   #指定连接pthread库
set(CMAKE_CXX_STANDARD 17)      #指定C++17版本
set(CMAKE_BUILD_TYPE "Debug")

add_executable(server ${SOURCES})

target_include_directories(server PRIVATE ../../inc)
target_include_directories(server PRIVATE ${PROJECT_SOURCE_DIR}/inc)