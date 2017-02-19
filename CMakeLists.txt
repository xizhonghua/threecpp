cmake_minimum_required(VERSION 2.8)

enable_testing()

find_package(PkgConfig REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)
find_package(OpenGL REQUIRED)

include_directories(${GLFW_INCLUDE_DIRS})
link_directories(/opt/local/lib)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")


include_directories(.)
include_directories(src)

#link_directories(src)

add_subdirectory(src)
add_subdirectory(test)
add_subdirectory(examples)
