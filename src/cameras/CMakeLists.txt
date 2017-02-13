add_library(cameras
  Camera.cpp
  PerspectiveCamera.cpp)

add_dependencies(cameras math)