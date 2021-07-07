add_library( graphics Canvas.cpp World.cpp Lighting.cpp Camera.cpp Shape.cpp Sphere.cpp Intersection.cpp Plane.cpp Plane.h LightComputations.cpp LightComputations.h Cube.cpp Cube.h Cylinder.cpp Cylinder.h ColorPattern.cpp ColorPattern.h StripedPattern.cpp StripedPattern.h PlainMaterial.cpp PlainMaterial.h PatternMaterial.cpp PatternMaterial.h GradientPattern.cpp GradientPattern.h CheckerPattern.cpp CheckerPattern.h RingPattern.cpp RingPattern.h)
target_include_directories( graphics PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} )
TARGET_LINK_LIBRARIES( graphics LINK_PUBLIC tracerMath )
