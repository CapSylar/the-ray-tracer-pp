add_library( tracerMath utilities.cpp Vec4.cpp Mat4.cpp Transformation.cpp ../src/Ray.h Sphere.cpp Intersection.cpp )
target_include_directories( tracerMath PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
