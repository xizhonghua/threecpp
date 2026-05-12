add_compile_definitions(GL_SILENCE_DEPRECATION)

add_library(apps
  WindowApp.cpp)

add_dependencies(apps 
  core)
