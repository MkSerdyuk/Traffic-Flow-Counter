cmake_minimum_required(VERSION 3.21)
project(Traffic_Flow_Counter)

set(CMAKE_CXX_STANDARD 14)

add_library(Traffic_Flow_Counter SHARED
        EXCLUDE_FROM_ALL Traffic-Flow-Counter.cpp)
