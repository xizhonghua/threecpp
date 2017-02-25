add_library(renderers
  GLProgram.cpp
  GLRenderer.cpp)

add_dependencies(renderers
  core)

target_link_libraries(renderers
  core
  ${OPENGL_LIBRARIES}
  ${OPENGL_glu_LIBRARY})
