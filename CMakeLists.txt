cmake_minimum_required(VERSION 3.21)
project(MultithreadingHW)

set(CMAKE_CXX_STANDARD 14)
set(GCC_COVERAGE_COMPILE_FLAGS "-static -static-libgcc -static-libstdc++")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}" )


add_executable(MultithreadingHW main.cpp threadmethods.cpp threadmethods.h)
