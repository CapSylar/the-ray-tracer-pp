add_library( tracerMath utilities.cpp Mat4.cpp Transformation.cpp Ray.cpp Material.cpp Color3f.cpp  Vec3f.cpp Vec3f.h Point3f.cpp Point3f.h)
target_include_directories( tracerMath PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
