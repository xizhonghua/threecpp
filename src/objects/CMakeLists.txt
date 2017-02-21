add_library(objects 
  Mesh.cpp
  RenderableObject.cpp)

add_dependencies(objects
  core)