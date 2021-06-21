add_library( graphics Canvas.cpp World.cpp tracing.cpp tracing.h)
target_include_directories( graphics PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} )
TARGET_LINK_LIBRARIES( graphics LINK_PUBLIC tracerMath )
