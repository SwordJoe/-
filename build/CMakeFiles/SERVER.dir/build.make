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
CMAKE_SOURCE_DIR = /home/ubuntu/TcpNetServer

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ubuntu/TcpNetServer/build

# Include any dependencies generated for this target.
include CMakeFiles/SERVER.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/SERVER.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/SERVER.dir/flags.make

CMakeFiles/SERVER.dir/src/Buffer.cc.o: CMakeFiles/SERVER.dir/flags.make
CMakeFiles/SERVER.dir/src/Buffer.cc.o: ../src/Buffer.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ubuntu/TcpNetServer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/SERVER.dir/src/Buffer.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/SERVER.dir/src/Buffer.cc.o -c /home/ubuntu/TcpNetServer/src/Buffer.cc

CMakeFiles/SERVER.dir/src/Buffer.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/SERVER.dir/src/Buffer.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ubuntu/TcpNetServer/src/Buffer.cc > CMakeFiles/SERVER.dir/src/Buffer.cc.i

CMakeFiles/SERVER.dir/src/Buffer.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/SERVER.dir/src/Buffer.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ubuntu/TcpNetServer/src/Buffer.cc -o CMakeFiles/SERVER.dir/src/Buffer.cc.s

CMakeFiles/SERVER.dir/src/Channel.cc.o: CMakeFiles/SERVER.dir/flags.make
CMakeFiles/SERVER.dir/src/Channel.cc.o: ../src/Channel.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ubuntu/TcpNetServer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/SERVER.dir/src/Channel.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/SERVER.dir/src/Channel.cc.o -c /home/ubuntu/TcpNetServer/src/Channel.cc

CMakeFiles/SERVER.dir/src/Channel.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/SERVER.dir/src/Channel.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ubuntu/TcpNetServer/src/Channel.cc > CMakeFiles/SERVER.dir/src/Channel.cc.i

CMakeFiles/SERVER.dir/src/Channel.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/SERVER.dir/src/Channel.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ubuntu/TcpNetServer/src/Channel.cc -o CMakeFiles/SERVER.dir/src/Channel.cc.s

CMakeFiles/SERVER.dir/src/EventLoop.cc.o: CMakeFiles/SERVER.dir/flags.make
CMakeFiles/SERVER.dir/src/EventLoop.cc.o: ../src/EventLoop.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ubuntu/TcpNetServer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/SERVER.dir/src/EventLoop.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/SERVER.dir/src/EventLoop.cc.o -c /home/ubuntu/TcpNetServer/src/EventLoop.cc

CMakeFiles/SERVER.dir/src/EventLoop.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/SERVER.dir/src/EventLoop.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ubuntu/TcpNetServer/src/EventLoop.cc > CMakeFiles/SERVER.dir/src/EventLoop.cc.i

CMakeFiles/SERVER.dir/src/EventLoop.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/SERVER.dir/src/EventLoop.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ubuntu/TcpNetServer/src/EventLoop.cc -o CMakeFiles/SERVER.dir/src/EventLoop.cc.s

CMakeFiles/SERVER.dir/src/InetAddress.cc.o: CMakeFiles/SERVER.dir/flags.make
CMakeFiles/SERVER.dir/src/InetAddress.cc.o: ../src/InetAddress.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ubuntu/TcpNetServer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/SERVER.dir/src/InetAddress.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/SERVER.dir/src/InetAddress.cc.o -c /home/ubuntu/TcpNetServer/src/InetAddress.cc

CMakeFiles/SERVER.dir/src/InetAddress.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/SERVER.dir/src/InetAddress.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ubuntu/TcpNetServer/src/InetAddress.cc > CMakeFiles/SERVER.dir/src/InetAddress.cc.i

CMakeFiles/SERVER.dir/src/InetAddress.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/SERVER.dir/src/InetAddress.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ubuntu/TcpNetServer/src/InetAddress.cc -o CMakeFiles/SERVER.dir/src/InetAddress.cc.s

CMakeFiles/SERVER.dir/src/TcpConnection.cc.o: CMakeFiles/SERVER.dir/flags.make
CMakeFiles/SERVER.dir/src/TcpConnection.cc.o: ../src/TcpConnection.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ubuntu/TcpNetServer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/SERVER.dir/src/TcpConnection.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/SERVER.dir/src/TcpConnection.cc.o -c /home/ubuntu/TcpNetServer/src/TcpConnection.cc

CMakeFiles/SERVER.dir/src/TcpConnection.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/SERVER.dir/src/TcpConnection.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ubuntu/TcpNetServer/src/TcpConnection.cc > CMakeFiles/SERVER.dir/src/TcpConnection.cc.i

CMakeFiles/SERVER.dir/src/TcpConnection.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/SERVER.dir/src/TcpConnection.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ubuntu/TcpNetServer/src/TcpConnection.cc -o CMakeFiles/SERVER.dir/src/TcpConnection.cc.s

CMakeFiles/SERVER.dir/src/TcpServer.cc.o: CMakeFiles/SERVER.dir/flags.make
CMakeFiles/SERVER.dir/src/TcpServer.cc.o: ../src/TcpServer.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ubuntu/TcpNetServer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/SERVER.dir/src/TcpServer.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/SERVER.dir/src/TcpServer.cc.o -c /home/ubuntu/TcpNetServer/src/TcpServer.cc

CMakeFiles/SERVER.dir/src/TcpServer.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/SERVER.dir/src/TcpServer.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ubuntu/TcpNetServer/src/TcpServer.cc > CMakeFiles/SERVER.dir/src/TcpServer.cc.i

CMakeFiles/SERVER.dir/src/TcpServer.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/SERVER.dir/src/TcpServer.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ubuntu/TcpNetServer/src/TcpServer.cc -o CMakeFiles/SERVER.dir/src/TcpServer.cc.s

CMakeFiles/SERVER.dir/src/EventLoopThreadPool.cc.o: CMakeFiles/SERVER.dir/flags.make
CMakeFiles/SERVER.dir/src/EventLoopThreadPool.cc.o: ../src/EventLoopThreadPool.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ubuntu/TcpNetServer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/SERVER.dir/src/EventLoopThreadPool.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/SERVER.dir/src/EventLoopThreadPool.cc.o -c /home/ubuntu/TcpNetServer/src/EventLoopThreadPool.cc

CMakeFiles/SERVER.dir/src/EventLoopThreadPool.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/SERVER.dir/src/EventLoopThreadPool.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ubuntu/TcpNetServer/src/EventLoopThreadPool.cc > CMakeFiles/SERVER.dir/src/EventLoopThreadPool.cc.i

CMakeFiles/SERVER.dir/src/EventLoopThreadPool.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/SERVER.dir/src/EventLoopThreadPool.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ubuntu/TcpNetServer/src/EventLoopThreadPool.cc -o CMakeFiles/SERVER.dir/src/EventLoopThreadPool.cc.s

CMakeFiles/SERVER.dir/src/TimeStamp.cc.o: CMakeFiles/SERVER.dir/flags.make
CMakeFiles/SERVER.dir/src/TimeStamp.cc.o: ../src/TimeStamp.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ubuntu/TcpNetServer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/SERVER.dir/src/TimeStamp.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/SERVER.dir/src/TimeStamp.cc.o -c /home/ubuntu/TcpNetServer/src/TimeStamp.cc

CMakeFiles/SERVER.dir/src/TimeStamp.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/SERVER.dir/src/TimeStamp.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ubuntu/TcpNetServer/src/TimeStamp.cc > CMakeFiles/SERVER.dir/src/TimeStamp.cc.i

CMakeFiles/SERVER.dir/src/TimeStamp.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/SERVER.dir/src/TimeStamp.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ubuntu/TcpNetServer/src/TimeStamp.cc -o CMakeFiles/SERVER.dir/src/TimeStamp.cc.s

CMakeFiles/SERVER.dir/src/TimerQueue.cc.o: CMakeFiles/SERVER.dir/flags.make
CMakeFiles/SERVER.dir/src/TimerQueue.cc.o: ../src/TimerQueue.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ubuntu/TcpNetServer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/SERVER.dir/src/TimerQueue.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/SERVER.dir/src/TimerQueue.cc.o -c /home/ubuntu/TcpNetServer/src/TimerQueue.cc

CMakeFiles/SERVER.dir/src/TimerQueue.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/SERVER.dir/src/TimerQueue.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ubuntu/TcpNetServer/src/TimerQueue.cc > CMakeFiles/SERVER.dir/src/TimerQueue.cc.i

CMakeFiles/SERVER.dir/src/TimerQueue.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/SERVER.dir/src/TimerQueue.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ubuntu/TcpNetServer/src/TimerQueue.cc -o CMakeFiles/SERVER.dir/src/TimerQueue.cc.s

CMakeFiles/SERVER.dir/src/Timer.cc.o: CMakeFiles/SERVER.dir/flags.make
CMakeFiles/SERVER.dir/src/Timer.cc.o: ../src/Timer.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ubuntu/TcpNetServer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object CMakeFiles/SERVER.dir/src/Timer.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/SERVER.dir/src/Timer.cc.o -c /home/ubuntu/TcpNetServer/src/Timer.cc

CMakeFiles/SERVER.dir/src/Timer.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/SERVER.dir/src/Timer.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ubuntu/TcpNetServer/src/Timer.cc > CMakeFiles/SERVER.dir/src/Timer.cc.i

CMakeFiles/SERVER.dir/src/Timer.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/SERVER.dir/src/Timer.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ubuntu/TcpNetServer/src/Timer.cc -o CMakeFiles/SERVER.dir/src/Timer.cc.s

CMakeFiles/SERVER.dir/src/main.cc.o: CMakeFiles/SERVER.dir/flags.make
CMakeFiles/SERVER.dir/src/main.cc.o: ../src/main.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ubuntu/TcpNetServer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Building CXX object CMakeFiles/SERVER.dir/src/main.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/SERVER.dir/src/main.cc.o -c /home/ubuntu/TcpNetServer/src/main.cc

CMakeFiles/SERVER.dir/src/main.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/SERVER.dir/src/main.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ubuntu/TcpNetServer/src/main.cc > CMakeFiles/SERVER.dir/src/main.cc.i

CMakeFiles/SERVER.dir/src/main.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/SERVER.dir/src/main.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ubuntu/TcpNetServer/src/main.cc -o CMakeFiles/SERVER.dir/src/main.cc.s

# Object files for target SERVER
SERVER_OBJECTS = \
"CMakeFiles/SERVER.dir/src/Buffer.cc.o" \
"CMakeFiles/SERVER.dir/src/Channel.cc.o" \
"CMakeFiles/SERVER.dir/src/EventLoop.cc.o" \
"CMakeFiles/SERVER.dir/src/InetAddress.cc.o" \
"CMakeFiles/SERVER.dir/src/TcpConnection.cc.o" \
"CMakeFiles/SERVER.dir/src/TcpServer.cc.o" \
"CMakeFiles/SERVER.dir/src/EventLoopThreadPool.cc.o" \
"CMakeFiles/SERVER.dir/src/TimeStamp.cc.o" \
"CMakeFiles/SERVER.dir/src/TimerQueue.cc.o" \
"CMakeFiles/SERVER.dir/src/Timer.cc.o" \
"CMakeFiles/SERVER.dir/src/main.cc.o"

# External object files for target SERVER
SERVER_EXTERNAL_OBJECTS =

SERVER: CMakeFiles/SERVER.dir/src/Buffer.cc.o
SERVER: CMakeFiles/SERVER.dir/src/Channel.cc.o
SERVER: CMakeFiles/SERVER.dir/src/EventLoop.cc.o
SERVER: CMakeFiles/SERVER.dir/src/InetAddress.cc.o
SERVER: CMakeFiles/SERVER.dir/src/TcpConnection.cc.o
SERVER: CMakeFiles/SERVER.dir/src/TcpServer.cc.o
SERVER: CMakeFiles/SERVER.dir/src/EventLoopThreadPool.cc.o
SERVER: CMakeFiles/SERVER.dir/src/TimeStamp.cc.o
SERVER: CMakeFiles/SERVER.dir/src/TimerQueue.cc.o
SERVER: CMakeFiles/SERVER.dir/src/Timer.cc.o
SERVER: CMakeFiles/SERVER.dir/src/main.cc.o
SERVER: CMakeFiles/SERVER.dir/build.make
SERVER: CMakeFiles/SERVER.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/ubuntu/TcpNetServer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_12) "Linking CXX executable SERVER"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/SERVER.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/SERVER.dir/build: SERVER

.PHONY : CMakeFiles/SERVER.dir/build

CMakeFiles/SERVER.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/SERVER.dir/cmake_clean.cmake
.PHONY : CMakeFiles/SERVER.dir/clean

CMakeFiles/SERVER.dir/depend:
	cd /home/ubuntu/TcpNetServer/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ubuntu/TcpNetServer /home/ubuntu/TcpNetServer /home/ubuntu/TcpNetServer/build /home/ubuntu/TcpNetServer/build /home/ubuntu/TcpNetServer/build/CMakeFiles/SERVER.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/SERVER.dir/depend

