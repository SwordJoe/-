cmake_minimum_required(VERSION 3.5)

project(SERVER)

set(SOURCES 
    src/Buffer.cc
    src/Channel.cc
    src/EventLoop.cc 
    src/InetAddress.cc
    src/TcpConnection.cc
    src/TcpServer.cc
    src/EventLoopThreadPool.cc
    src/main.cc
    )


set(CMAKE_CXX_FLAGS -pthread)
set(CMAKE_BUILD_TYPE "Debug")

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/inc)