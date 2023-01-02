cmake_minimum_required(VERSION 3.23)
project(3DRenderer)

set(CMAKE_CXX_STANDARD 20)

set(MATH_INCLUDE ${CMAKE_SOURCE_DIR}/src/Math)
set(CONST_INCLUDE ${CMAKE_SOURCE_DIR}/src/Constants)
set(RENDER_INCLUDE ${CMAKE_SOURCE_DIR}/src/Renderer)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_subdirectory(src/Math)
add_subdirectory(src/Renderer)
add_subdirectory(src/Constants)
add_subdirectory(src/Main)
