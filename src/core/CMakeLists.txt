add_library(core
    Face3.cpp
    Geometry.cpp
    Object3D.cpp)

add_dependencies(core math)