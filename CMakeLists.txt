cmake_minimum_required(VERSION 3.23)
project(3drenderer)

set(CMAKE_CXX_STANDARD 20)

file(GLOB_RECURSE SRC "src/*")
file(GLOB_RECURSE IMGUI "libs/imgui/*")
set(UPNG libs/upng/upng.c libs/upng/upng.h)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_executable(${PROJECT_NAME} ${SRC} ${IMGUI} ${UPNG})
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES})

