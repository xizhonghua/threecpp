find_package(PkgConfig REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)
find_package(OpenGL REQUIRED)

include_directories(${GLFW_INCLUDE_DIRS})
link_directories(/opt/local/lib)

add_executable(basic basic.cc)
add_dependencies(basic threecpp)


target_link_libraries(basic 
  threecpp 
  ${OPENGL_glu_LIBRARY}
  ${GLFW_LIBRARIES})