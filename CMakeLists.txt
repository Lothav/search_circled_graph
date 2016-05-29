# cmake_minimum_required(VERSION <specify CMake version here>)
project(GraphRobot)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.c)
add_executable(GraphRobot ${SOURCE_FILES})