cmake_minimum_required(VERSION 3.23)
project(3DRenderer)

set(CMAKE_CXX_STANDARD 20)

file(GLOB_RECURSE SRC "src/*")
file(GLOB_RECURSE IMGUI "libs/imgui/*")

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_executable(${PROJECT_NAME} ${SRC} ${IMGUI})
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES})

