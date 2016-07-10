cmake_minimum_required(VERSION 3.5)
project(stepic)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(SOURCE_FILES main.cpp stepic63-7.cpp)
add_executable(stepic ${SOURCE_FILES})
target_link_libraries(stepic pthread)