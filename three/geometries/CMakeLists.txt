add_library(geometries
  BoxGeometry.cpp)

add_dependencies(geometries
  core)
target_link_libraries(geometries
 core)
