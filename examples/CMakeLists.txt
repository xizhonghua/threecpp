file( GLOB APP_SOURCES *.cc )
foreach( src ${APP_SOURCES} )
    get_filename_component( example_name ${src} NAME)
    string( REPLACE ".cc" "" example_name ${example_name} )
    set(example_name "example-${example_name}")

    add_executable( ${example_name} ${src} )
    add_dependencies( ${example_name} threecpp)
    target_link_libraries( ${example_name} 
      threecpp
      ${OPENGL_glu_LIBRARY}
      ${GLFW_LIBRARIES})

endforeach( src ${APP_SOURCES} )