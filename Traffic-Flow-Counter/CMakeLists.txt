cmake_minimum_required(VERSION 3.21)
project(Traffic_Flow_Counter_script)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_EXE_LINKER_FLAGS ${CMAKE_EXE_LINKER_FLAGS} "-static")
add_executable(Traffic_Flow_Counter_script Traffic-Flow-Counter.cpp)
