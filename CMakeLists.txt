cmake_minimum_required(VERSION 3.5)
project(stepic)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp stepic62-8.cpp)
add_executable(stepic ${SOURCE_FILES})