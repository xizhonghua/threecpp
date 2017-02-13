cmake_minimum_required(VERSION 2.8.0)
project(threecpp)

# Modules
add_subdirectory(cameras)
add_subdirectory(core)
add_subdirectory(math)

set(LIBS
  cameras
  core
  math)

# Combine All
add_library(threecpp three.cc)
add_dependencies(threecpp ${LIBS})
target_link_libraries(threecpp ${LIBS})