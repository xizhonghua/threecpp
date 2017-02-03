cmake_minimum_required(VERSION 2.8.0)
project(threecpp)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories(.)

add_subdirectory(cameras)
add_subdirectory(core)
add_subdirectory(math)


