add_library( tracerMath utilities.cpp Vec4.cpp Mat4.cpp Transformation.cpp Ray.cpp Sphere.cpp Intersection.cpp Material.cpp Color.cpp )
target_include_directories( tracerMath PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
