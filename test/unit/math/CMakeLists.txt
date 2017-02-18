add_executable(test_math 
	Math.cc
	Vector2.cc
	Vector3.cc
	Vector4.cc)
target_link_libraries(test_math math)

add_test(math_test math_test test_math)