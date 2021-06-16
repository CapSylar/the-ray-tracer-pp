add_library( tracerMath utilities.cpp Vec4.cpp Mat4.cpp  )
target_include_directories( tracerMath PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
