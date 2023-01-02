cmake_minimum_required(VERSION 3.23)
project(3DRenderer)

set(CMAKE_CXX_STANDARD 20)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

file(GLOB_RECURSE SRC "src/*")

add_executable(3DRenderer ${SRC})

target_link_libraries(${PROJECT_NAME} PUBLIC ${SDL2_LIBRARIES})
