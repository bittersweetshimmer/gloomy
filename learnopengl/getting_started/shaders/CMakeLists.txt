cmake_minimum_required(VERSION 3.16)

set(SOURCES "src/main.cpp")

add_executable(learnopengl_shaders ${SOURCES})
set_target_properties(learnopengl_shaders PROPERTIES
    OUTPUT_NAME "shaders")

target_include_directories(learnopengl_shaders PUBLIC ./include/)

if(WIN32)
    target_include_directories(learnopengl_shaders PRIVATE ${GLFW_INCLUDE_DIRS})
    target_link_directories(learnopengl_shaders PRIVATE ${GLFW_LIB_PATH})
    target_link_libraries(learnopengl_shaders glfw3)
else()
    target_include_directories(learnopengl_shaders PRIVATE ${GLFW_INCLUDE_DIRS})
    target_link_libraries(learnopengl_shaders ${GLFW_STATIC_LIBRARIES})
endif()

target_link_libraries(learnopengl_shaders gloomy)
target_link_libraries(learnopengl_shaders glad)

set_target_properties(learnopengl_shaders PROPERTIES
                        CXX_STANDARD 20)

file(COPY "assets" DESTINATION ".")