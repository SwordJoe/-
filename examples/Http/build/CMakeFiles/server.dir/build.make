# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/ubuntu/TcpNetServer/examples/Http

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ubuntu/TcpNetServer/examples/Http/build

# Include any dependencies generated for this target.
include CMakeFiles/server.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/server.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/server.dir/flags.make

CMakeFiles/server.dir/home/ubuntu/TcpNetServer/src/Buffer.cc.o: CMakeFiles/server.dir/flags.make
CMakeFiles/server.dir/home/ubuntu/TcpNetServer/src/Buffer.cc.o: /home/ubuntu/TcpNetServer/src/Buffer.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ubuntu/TcpNetServer/examples/Http/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/server.dir/home/ubuntu/TcpNetServer/src/Buffer.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/server.dir/home/ubuntu/TcpNetServer/src/Buffer.cc.o -c /home/ubuntu/TcpNetServer/src/Buffer.cc

CMakeFiles/server.dir/home/ubuntu/TcpNetServer/src/Buffer.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/server.dir/home/ubuntu/TcpNetServer/src/Buffer.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ubuntu/TcpNetServer/src/Buffer.cc > CMakeFiles/server.dir/home/ubuntu/TcpNetServer/src/Buffer.cc.i

CMakeFiles/server.dir/home/ubuntu/TcpNetServer/src/Buffer.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/server.dir/home/ubuntu/TcpNetServer/src/Buffer.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ubuntu/TcpNetServer/src/Buffer.cc -o CMakeFiles/server.dir/home/ubuntu/TcpNetServer/src/Buffer.cc.s

CMakeFiles/server.dir/home/ubuntu/TcpNetServer/src/Channel.cc.o: CMakeFiles/server.dir/flags.make
CMakeFiles/server.dir/home/ubuntu/TcpNetServer/src/Channel.cc.o: /home/ubuntu/TcpNetServer/src/Channel.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ubuntu/TcpNetServer/examples/Http/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/server.dir/home/ubuntu/TcpNetServer/src/Channel.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/server.dir/home/ubuntu/TcpNetServer/src/Channel.cc.o -c /home/ubuntu/TcpNetServer/src/Channel.cc

CMakeFiles/server.dir/home/ubuntu/TcpNetServer/src/Channel.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/server.dir/home/ubuntu/TcpNetServer/src/Channel.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ubuntu/TcpNetServer/src/Channel.cc > CMakeFiles/server.dir/home/ubuntu/TcpNetServer/src/Channel.cc.i

CMakeFiles/server.dir/home/ubuntu/TcpNetServer/src/Channel.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/server.dir/home/ubuntu/TcpNetServer/src/Channel.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ubuntu/TcpNetServer/src/Channel.cc -o CMakeFiles/server.dir/home/ubuntu/TcpNetServer/src/Channel.cc.s

CMakeFiles/server.dir/home/ubuntu/TcpNetServer/src/EventLoop.cc.o: CMakeFiles/server.dir/flags.make
CMakeFiles/server.dir/home/ubuntu/TcpNetServer/src/EventLoop.cc.o: /home/ubuntu/TcpNetServer/src/EventLoop.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ubuntu/TcpNetServer/examples/Http/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/server.dir/home/ubuntu/TcpNetServer/src/EventLoop.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/server.dir/home/ubuntu/TcpNetServer/src/EventLoop.cc.o -c /home/ubuntu/TcpNetServer/src/EventLoop.cc

CMakeFiles/server.dir/home/ubuntu/TcpNetServer/src/EventLoop.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/server.dir/home/ubuntu/TcpNetServer/src/EventLoop.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ubuntu/TcpNetServer/src/EventLoop.cc > CMakeFiles/server.dir/home/ubuntu/TcpNetServer/src/EventLoop.cc.i

CMakeFiles/server.dir/home/ubuntu/TcpNetServer/src/EventLoop.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/server.dir/home/ubuntu/TcpNetServer/src/EventLoop.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ubuntu/TcpNetServer/src/EventLoop.cc -o CMakeFiles/server.dir/home/ubuntu/TcpNetServer/src/EventLoop.cc.s

CMakeFiles/server.dir/home/ubuntu/TcpNetServer/src/InetAddress.cc.o: CMakeFiles/server.dir/flags.make
CMakeFiles/server.dir/home/ubuntu/TcpNetServer/src/InetAddress.cc.o: /home/ubuntu/TcpNetServer/src/InetAddress.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ubuntu/TcpNetServer/examples/Http/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/server.dir/home/ubuntu/TcpNetServer/src/InetAddress.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/server.dir/home/ubuntu/TcpNetServer/src/InetAddress.cc.o -c /home/ubuntu/TcpNetServer/src/InetAddress.cc

CMakeFiles/server.dir/home/ubuntu/TcpNetServer/src/InetAddress.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/server.dir/home/ubuntu/TcpNetServer/src/InetAddress.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ubuntu/TcpNetServer/src/InetAddress.cc > CMakeFiles/server.dir/home/ubuntu/TcpNetServer/src/InetAddress.cc.i

CMakeFiles/server.dir/home/ubuntu/TcpNetServer/src/InetAddress.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/server.dir/home/ubuntu/TcpNetServer/src/InetAddress.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ubuntu/TcpNetServer/src/InetAddress.cc -o CMakeFiles/server.dir/home/ubuntu/TcpNetServer/src/InetAddress.cc.s

CMakeFiles/server.dir/home/ubuntu/TcpNetServer/src/TcpConnection.cc.o: CMakeFiles/server.dir/flags.make
CMakeFiles/server.dir/home/ubuntu/TcpNetServer/src/TcpConnection.cc.o: /home/ubuntu/TcpNetServer/src/TcpConnection.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ubuntu/TcpNetServer/examples/Http/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/server.dir/home/ubuntu/TcpNetServer/src/TcpConnection.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/server.dir/home/ubuntu/TcpNetServer/src/TcpConnection.cc.o -c /home/ubuntu/TcpNetServer/src/TcpConnection.cc

CMakeFiles/server.dir/home/ubuntu/TcpNetServer/src/TcpConnection.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/server.dir/home/ubuntu/TcpNetServer/src/TcpConnection.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ubuntu/TcpNetServer/src/TcpConnection.cc > CMakeFiles/server.dir/home/ubuntu/TcpNetServer/src/TcpConnection.cc.i

CMakeFiles/server.dir/home/ubuntu/TcpNetServer/src/TcpConnection.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/server.dir/home/ubuntu/TcpNetServer/src/TcpConnection.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ubuntu/TcpNetServer/src/TcpConnection.cc -o CMakeFiles/server.dir/home/ubuntu/TcpNetServer/src/TcpConnection.cc.s

CMakeFiles/server.dir/home/ubuntu/TcpNetServer/src/TcpServer.cc.o: CMakeFiles/server.dir/flags.make
CMakeFiles/server.dir/home/ubuntu/TcpNetServer/src/TcpServer.cc.o: /home/ubuntu/TcpNetServer/src/TcpServer.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ubuntu/TcpNetServer/examples/Http/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/server.dir/home/ubuntu/TcpNetServer/src/TcpServer.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/server.dir/home/ubuntu/TcpNetServer/src/TcpServer.cc.o -c /home/ubuntu/TcpNetServer/src/TcpServer.cc

CMakeFiles/server.dir/home/ubuntu/TcpNetServer/src/TcpServer.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/server.dir/home/ubuntu/TcpNetServer/src/TcpServer.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ubuntu/TcpNetServer/src/TcpServer.cc > CMakeFiles/server.dir/home/ubuntu/TcpNetServer/src/TcpServer.cc.i

CMakeFiles/server.dir/home/ubuntu/TcpNetServer/src/TcpServer.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/server.dir/home/ubuntu/TcpNetServer/src/TcpServer.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ubuntu/TcpNetServer/src/TcpServer.cc -o CMakeFiles/server.dir/home/ubuntu/TcpNetServer/src/TcpServer.cc.s

CMakeFiles/server.dir/home/ubuntu/TcpNetServer/src/EventLoopThreadPool.cc.o: CMakeFiles/server.dir/flags.make
CMakeFiles/server.dir/home/ubuntu/TcpNetServer/src/EventLoopThreadPool.cc.o: /home/ubuntu/TcpNetServer/src/EventLoopThreadPool.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ubuntu/TcpNetServer/examples/Http/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/server.dir/home/ubuntu/TcpNetServer/src/EventLoopThreadPool.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/server.dir/home/ubuntu/TcpNetServer/src/EventLoopThreadPool.cc.o -c /home/ubuntu/TcpNetServer/src/EventLoopThreadPool.cc

CMakeFiles/server.dir/home/ubuntu/TcpNetServer/src/EventLoopThreadPool.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/server.dir/home/ubuntu/TcpNetServer/src/EventLoopThreadPool.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ubuntu/TcpNetServer/src/EventLoopThreadPool.cc > CMakeFiles/server.dir/home/ubuntu/TcpNetServer/src/EventLoopThreadPool.cc.i

CMakeFiles/server.dir/home/ubuntu/TcpNetServer/src/EventLoopThreadPool.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/server.dir/home/ubuntu/TcpNetServer/src/EventLoopThreadPool.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ubuntu/TcpNetServer/src/EventLoopThreadPool.cc -o CMakeFiles/server.dir/home/ubuntu/TcpNetServer/src/EventLoopThreadPool.cc.s

CMakeFiles/server.dir/home/ubuntu/TcpNetServer/src/TimeStamp.cc.o: CMakeFiles/server.dir/flags.make
CMakeFiles/server.dir/home/ubuntu/TcpNetServer/src/TimeStamp.cc.o: /home/ubuntu/TcpNetServer/src/TimeStamp.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ubuntu/TcpNetServer/examples/Http/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/server.dir/home/ubuntu/TcpNetServer/src/TimeStamp.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/server.dir/home/ubuntu/TcpNetServer/src/TimeStamp.cc.o -c /home/ubuntu/TcpNetServer/src/TimeStamp.cc

CMakeFiles/server.dir/home/ubuntu/TcpNetServer/src/TimeStamp.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/server.dir/home/ubuntu/TcpNetServer/src/TimeStamp.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ubuntu/TcpNetServer/src/TimeStamp.cc > CMakeFiles/server.dir/home/ubuntu/TcpNetServer/src/TimeStamp.cc.i

CMakeFiles/server.dir/home/ubuntu/TcpNetServer/src/TimeStamp.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/server.dir/home/ubuntu/TcpNetServer/src/TimeStamp.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ubuntu/TcpNetServer/src/TimeStamp.cc -o CMakeFiles/server.dir/home/ubuntu/TcpNetServer/src/TimeStamp.cc.s

CMakeFiles/server.dir/home/ubuntu/TcpNetServer/src/TimerQueue.cc.o: CMakeFiles/server.dir/flags.make
CMakeFiles/server.dir/home/ubuntu/TcpNetServer/src/TimerQueue.cc.o: /home/ubuntu/TcpNetServer/src/TimerQueue.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ubuntu/TcpNetServer/examples/Http/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/server.dir/home/ubuntu/TcpNetServer/src/TimerQueue.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/server.dir/home/ubuntu/TcpNetServer/src/TimerQueue.cc.o -c /home/ubuntu/TcpNetServer/src/TimerQueue.cc

CMakeFiles/server.dir/home/ubuntu/TcpNetServer/src/TimerQueue.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/server.dir/home/ubuntu/TcpNetServer/src/TimerQueue.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ubuntu/TcpNetServer/src/TimerQueue.cc > CMakeFiles/server.dir/home/ubuntu/TcpNetServer/src/TimerQueue.cc.i

CMakeFiles/server.dir/home/ubuntu/TcpNetServer/src/TimerQueue.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/server.dir/home/ubuntu/TcpNetServer/src/TimerQueue.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ubuntu/TcpNetServer/src/TimerQueue.cc -o CMakeFiles/server.dir/home/ubuntu/TcpNetServer/src/TimerQueue.cc.s

CMakeFiles/server.dir/home/ubuntu/TcpNetServer/src/Timer.cc.o: CMakeFiles/server.dir/flags.make
CMakeFiles/server.dir/home/ubuntu/TcpNetServer/src/Timer.cc.o: /home/ubuntu/TcpNetServer/src/Timer.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ubuntu/TcpNetServer/examples/Http/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object CMakeFiles/server.dir/home/ubuntu/TcpNetServer/src/Timer.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/server.dir/home/ubuntu/TcpNetServer/src/Timer.cc.o -c /home/ubuntu/TcpNetServer/src/Timer.cc

CMakeFiles/server.dir/home/ubuntu/TcpNetServer/src/Timer.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/server.dir/home/ubuntu/TcpNetServer/src/Timer.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ubuntu/TcpNetServer/src/Timer.cc > CMakeFiles/server.dir/home/ubuntu/TcpNetServer/src/Timer.cc.i

CMakeFiles/server.dir/home/ubuntu/TcpNetServer/src/Timer.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/server.dir/home/ubuntu/TcpNetServer/src/Timer.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ubuntu/TcpNetServer/src/Timer.cc -o CMakeFiles/server.dir/home/ubuntu/TcpNetServer/src/Timer.cc.s

CMakeFiles/server.dir/src/HttpContext.cc.o: CMakeFiles/server.dir/flags.make
CMakeFiles/server.dir/src/HttpContext.cc.o: ../src/HttpContext.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ubuntu/TcpNetServer/examples/Http/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Building CXX object CMakeFiles/server.dir/src/HttpContext.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/server.dir/src/HttpContext.cc.o -c /home/ubuntu/TcpNetServer/examples/Http/src/HttpContext.cc

CMakeFiles/server.dir/src/HttpContext.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/server.dir/src/HttpContext.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ubuntu/TcpNetServer/examples/Http/src/HttpContext.cc > CMakeFiles/server.dir/src/HttpContext.cc.i

CMakeFiles/server.dir/src/HttpContext.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/server.dir/src/HttpContext.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ubuntu/TcpNetServer/examples/Http/src/HttpContext.cc -o CMakeFiles/server.dir/src/HttpContext.cc.s

CMakeFiles/server.dir/src/HttpResponse.cc.o: CMakeFiles/server.dir/flags.make
CMakeFiles/server.dir/src/HttpResponse.cc.o: ../src/HttpResponse.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ubuntu/TcpNetServer/examples/Http/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_12) "Building CXX object CMakeFiles/server.dir/src/HttpResponse.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/server.dir/src/HttpResponse.cc.o -c /home/ubuntu/TcpNetServer/examples/Http/src/HttpResponse.cc

CMakeFiles/server.dir/src/HttpResponse.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/server.dir/src/HttpResponse.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ubuntu/TcpNetServer/examples/Http/src/HttpResponse.cc > CMakeFiles/server.dir/src/HttpResponse.cc.i

CMakeFiles/server.dir/src/HttpResponse.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/server.dir/src/HttpResponse.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ubuntu/TcpNetServer/examples/Http/src/HttpResponse.cc -o CMakeFiles/server.dir/src/HttpResponse.cc.s

CMakeFiles/server.dir/src/HttpServer.cc.o: CMakeFiles/server.dir/flags.make
CMakeFiles/server.dir/src/HttpServer.cc.o: ../src/HttpServer.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ubuntu/TcpNetServer/examples/Http/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_13) "Building CXX object CMakeFiles/server.dir/src/HttpServer.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/server.dir/src/HttpServer.cc.o -c /home/ubuntu/TcpNetServer/examples/Http/src/HttpServer.cc

CMakeFiles/server.dir/src/HttpServer.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/server.dir/src/HttpServer.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ubuntu/TcpNetServer/examples/Http/src/HttpServer.cc > CMakeFiles/server.dir/src/HttpServer.cc.i

CMakeFiles/server.dir/src/HttpServer.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/server.dir/src/HttpServer.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ubuntu/TcpNetServer/examples/Http/src/HttpServer.cc -o CMakeFiles/server.dir/src/HttpServer.cc.s

# Object files for target server
server_OBJECTS = \
"CMakeFiles/server.dir/home/ubuntu/TcpNetServer/src/Buffer.cc.o" \
"CMakeFiles/server.dir/home/ubuntu/TcpNetServer/src/Channel.cc.o" \
"CMakeFiles/server.dir/home/ubuntu/TcpNetServer/src/EventLoop.cc.o" \
"CMakeFiles/server.dir/home/ubuntu/TcpNetServer/src/InetAddress.cc.o" \
"CMakeFiles/server.dir/home/ubuntu/TcpNetServer/src/TcpConnection.cc.o" \
"CMakeFiles/server.dir/home/ubuntu/TcpNetServer/src/TcpServer.cc.o" \
"CMakeFiles/server.dir/home/ubuntu/TcpNetServer/src/EventLoopThreadPool.cc.o" \
"CMakeFiles/server.dir/home/ubuntu/TcpNetServer/src/TimeStamp.cc.o" \
"CMakeFiles/server.dir/home/ubuntu/TcpNetServer/src/TimerQueue.cc.o" \
"CMakeFiles/server.dir/home/ubuntu/TcpNetServer/src/Timer.cc.o" \
"CMakeFiles/server.dir/src/HttpContext.cc.o" \
"CMakeFiles/server.dir/src/HttpResponse.cc.o" \
"CMakeFiles/server.dir/src/HttpServer.cc.o"

# External object files for target server
server_EXTERNAL_OBJECTS =

server: CMakeFiles/server.dir/home/ubuntu/TcpNetServer/src/Buffer.cc.o
server: CMakeFiles/server.dir/home/ubuntu/TcpNetServer/src/Channel.cc.o
server: CMakeFiles/server.dir/home/ubuntu/TcpNetServer/src/EventLoop.cc.o
server: CMakeFiles/server.dir/home/ubuntu/TcpNetServer/src/InetAddress.cc.o
server: CMakeFiles/server.dir/home/ubuntu/TcpNetServer/src/TcpConnection.cc.o
server: CMakeFiles/server.dir/home/ubuntu/TcpNetServer/src/TcpServer.cc.o
server: CMakeFiles/server.dir/home/ubuntu/TcpNetServer/src/EventLoopThreadPool.cc.o
server: CMakeFiles/server.dir/home/ubuntu/TcpNetServer/src/TimeStamp.cc.o
server: CMakeFiles/server.dir/home/ubuntu/TcpNetServer/src/TimerQueue.cc.o
server: CMakeFiles/server.dir/home/ubuntu/TcpNetServer/src/Timer.cc.o
server: CMakeFiles/server.dir/src/HttpContext.cc.o
server: CMakeFiles/server.dir/src/HttpResponse.cc.o
server: CMakeFiles/server.dir/src/HttpServer.cc.o
server: CMakeFiles/server.dir/build.make
server: CMakeFiles/server.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/ubuntu/TcpNetServer/examples/Http/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_14) "Linking CXX executable server"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/server.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/server.dir/build: server

.PHONY : CMakeFiles/server.dir/build

CMakeFiles/server.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/server.dir/cmake_clean.cmake
.PHONY : CMakeFiles/server.dir/clean

CMakeFiles/server.dir/depend:
	cd /home/ubuntu/TcpNetServer/examples/Http/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ubuntu/TcpNetServer/examples/Http /home/ubuntu/TcpNetServer/examples/Http /home/ubuntu/TcpNetServer/examples/Http/build /home/ubuntu/TcpNetServer/examples/Http/build /home/ubuntu/TcpNetServer/examples/Http/build/CMakeFiles/server.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/server.dir/depend

