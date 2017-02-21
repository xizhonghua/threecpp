add_library(cameras
  Camera.cpp
  OrthographicCamera.cpp
  PerspectiveCamera.cpp)

add_dependencies(cameras math)