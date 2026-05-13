add_library(materials
  Material.cpp
  MeshBasicMaterial.cpp
  MeshNormalMaterial.cpp
  MeshPhongMaterial.cpp
)

add_dependencies(materials
  core)
