add_library(apps
  WindowApp.cpp)

add_dependencies(apps 
  core)

target_link_libraries(apps
  ${GLFW_LIBRARIES})
