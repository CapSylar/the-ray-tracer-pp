add_executable( TEST_SOURCES Vec4_Tests.cpp Mat4_Tests.cpp )
TARGET_LINK_LIBRARIES( TEST_SOURCES LINK_PUBLIC Catch2::Catch2 tracerMath )