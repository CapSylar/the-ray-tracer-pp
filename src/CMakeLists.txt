add_library( graphics Canvas.cpp World.cpp Lighting.cpp Camera.cpp UnitShape.cpp Sphere.cpp Intersection.cpp Plane.cpp Plane.h LightComputations.cpp LightComputations.h Cube.cpp Cube.h Cylinder.cpp Cylinder.h ColorPattern.cpp ColorPattern.h StripedPattern.cpp StripedPattern.h PlainMaterial.cpp PlainMaterial.h PatternMaterial.cpp PatternMaterial.h GradientPattern.cpp GradientPattern.h CheckerPattern.cpp CheckerPattern.h RingPattern.cpp RingPattern.h Triangle.cpp Triangle.h Primitive.cpp Primitive.h Loader.cpp Loader.h Aggregate.cpp Aggregate.h Bounds3f.cpp Bounds3f.h GeometricPrimitive.cpp GeometricPrimitive.h KdTreeAccel.cpp KdTreeAccel.h)
target_include_directories( graphics PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} PUBLIC ../external/objloader )

if ( OpenMP_CXX_FOUND AND ${CMAKE_BUILD_TYPE} STREQUAL "Release" )
    TARGET_LINK_LIBRARIES( graphics LINK_PUBLIC tracerMath tinyobjloader   OpenMP::OpenMP_CXX )
else()
    TARGET_LINK_LIBRARIES( graphics LINK_PUBLIC tracerMath tinyobjloader )
endif()