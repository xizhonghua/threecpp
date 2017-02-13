add_executable(baisc basic.cc)
add_dependencies(baisc threecpp)
target_link_libraries(baisc threecpp)