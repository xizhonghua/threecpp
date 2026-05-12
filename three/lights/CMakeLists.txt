add_library(lights
  Light.cpp
  AmbientLight.cpp
  PointLight.cpp)

add_dependencies(lights
  core)