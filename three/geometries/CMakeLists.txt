add_library(geometries
  BoxGeometry.cpp
  SphereGeometry.cpp)

add_dependencies(geometries
  core)
target_link_libraries(geometries
 core)
