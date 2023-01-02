add_executable(${PROJECT_NAME} Main.cpp)

target_include_directories(${PROJECT_NAME} PRIVATE
        ${CONST_INCLUDE}
        ${RENDER_INCLUDE})

target_link_libraries(${PROJECT_NAME} PUBLIC
        Renderer
        ${SDL2_LIBRARIES})