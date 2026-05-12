cmake_minimum_required(VERSION 2.8)
project(threecpp)

if(APPLE)
    execute_process(
        COMMAND xcrun --sdk macosx --show-sdk-path
        OUTPUT_VARIABLE CMAKE_OSX_SYSROOT
        OUTPUT_STRIP_TRAILING_WHITESPACE
        ERROR_QUIET
    )
    if(CMAKE_OSX_SYSROOT)
        set(CMAKE_OSX_SYSROOT "${CMAKE_OSX_SYSROOT}" CACHE PATH "OS X sysroot" FORCE)
    endif()
endif()

enable_testing()

find_package(PkgConfig REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)
find_package(OpenGL REQUIRED)

include_directories(${GLFW_INCLUDE_DIRS})
if(GLFW_LIBRARY_DIRS)
    link_directories(${GLFW_LIBRARY_DIRS})
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")


include_directories(.)

add_subdirectory(three)
add_subdirectory(test)
add_subdirectory(examples)
