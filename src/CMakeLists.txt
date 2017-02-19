cmake_minimum_required(VERSION 2.8.0)
project(threecpp)

# Modules
add_subdirectory(app)
add_subdirectory(cameras)
add_subdirectory(core)
add_subdirectory(geometries)
add_subdirectory(materials)
add_subdirectory(math)
add_subdirectory(objects)
add_subdirectory(renderers)
add_subdirectory(scenes)

set(LIBS
  apps
  cameras
  core
  geometries
  materials
  math
  objects
  renderers
  scenes)

# Combine All
add_library(threecpp three.cc)
add_dependencies(threecpp ${LIBS})
target_link_libraries(threecpp ${LIBS})