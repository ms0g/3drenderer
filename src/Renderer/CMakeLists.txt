add_library(Renderer
        Renderer/Renderer.cpp
        Renderer/Renderer.h)

target_include_directories(Renderer PRIVATE
        ${CONST_INCLUDE}
        ${MATH_INCLUDE})

target_link_libraries(Renderer PRIVATE Math)