add_library(materials 
  Material.cpp
  MeshBasicMaterial.cpp
  MeshPhongMaterial.cpp)

add_dependencies(materials
  core)