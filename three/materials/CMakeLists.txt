add_library(materials
  Material.cpp
  MeshBasicMaterial.cpp
  MeshDepthMaterial.cpp
  MeshNormalMaterial.cpp
  MeshPhongMaterial.cpp
)

add_dependencies(materials
  core)
