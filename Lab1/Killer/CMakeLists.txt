cmake_minimum_required(VERSION 3.24)
project(Killer)

set(CMAKE_CXX_STANDARD 17)

include_directories(Monitor Process)

add_executable(Killer main.cpp Monitor/Monitor.cpp Monitor/Monitor.h Process/Process.cpp Process/Process.h)
