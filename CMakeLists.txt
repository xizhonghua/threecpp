cmake_minimum_required(VERSION 3.7)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")


include_directories(.)
include_directories(src)

link_directories(src)

add_subdirectory(src)
add_subdirectory(test)