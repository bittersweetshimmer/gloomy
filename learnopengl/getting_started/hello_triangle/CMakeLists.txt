cmake_minimum_required(VERSION 3.16)

set(SOURCES "src/main.cpp")

add_executable(learnopengl_hello_triangle ${SOURCES})
set_target_properties(learnopengl_hello_triangle PROPERTIES
    OUTPUT_NAME "hello_triangle")

target_include_directories(learnopengl_hello_triangle PUBLIC ./include/)

if(WIN32)
    target_include_directories(learnopengl_hello_triangle PRIVATE ${GLFW_INCLUDE_DIRS})
    target_link_directories(learnopengl_hello_triangle PRIVATE ${GLFW_LIB_PATH})
    target_link_libraries(learnopengl_hello_triangle glfw3)
else()
    target_include_directories(learnopengl_hello_triangle PRIVATE ${GLFW_INCLUDE_DIRS})
    target_link_libraries(learnopengl_hello_triangle ${GLFW_STATIC_LIBRARIES})
endif()

target_link_libraries(learnopengl_hello_triangle gloomy)
target_link_libraries(learnopengl_hello_triangle glad)

set_target_properties(learnopengl_hello_triangle PROPERTIES
                        CXX_STANDARD 20)