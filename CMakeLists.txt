cmake_minimum_required(VERSION 3.16)
project(ray_tracer++)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# adding options

add_compile_options(-Wall -Wextra -pedantic)

#configure SDL2

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

# configure Catch2 unit testing framework

find_package(Catch2 REQUIRED)

add_executable( ray_tracer++ src/main.cpp)

INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS})
TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES} m Catch2::Catch2  )

# separate target for testing
add_executable( TEST_SOURCES test/test_main.cpp)


