add_executable(basic basic.cc)
add_dependencies(basic threecpp)


target_link_libraries(basic 
  threecpp 
  ${OPENGL_glu_LIBRARY}
  ${GLFW_LIBRARIES})