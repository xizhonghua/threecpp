add_library(renderers
  GLProgram.cpp  
  GLRenderer.cpp
  GLShader.cpp
  GLUniforms.cpp
  Shader.cpp
  Shaders/ShaderChunk.cpp
  Shaders/ShaderLib.cpp)

add_dependencies(renderers
  core)

target_link_libraries(renderers
  core
  ${OPENGL_LIBRARIES}
  ${OPENGL_glu_LIBRARY})
