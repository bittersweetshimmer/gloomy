cmake_minimum_required(VERSION 3.16)

set(SOURCES "src/main.cpp")

add_executable(learnopengl_camera ${SOURCES})
set_target_properties(learnopengl_camera PROPERTIES
    OUTPUT_NAME "camera")

target_include_directories(learnopengl_camera PUBLIC ./include/)

if(WIN32)
    target_include_directories(learnopengl_camera PRIVATE ${GLFW_INCLUDE_DIRS})
    target_link_directories(learnopengl_camera PRIVATE ${GLFW_LIB_PATH})
    target_link_libraries(learnopengl_camera glfw3)
else()
    target_include_directories(learnopengl_camera PRIVATE ${GLFW_INCLUDE_DIRS})
    target_link_libraries(learnopengl_camera ${GLFW_STATIC_LIBRARIES})
endif()

target_link_libraries(learnopengl_camera gloomy)
target_link_libraries(learnopengl_camera glad)
target_link_libraries(learnopengl_camera stb)
target_link_libraries(learnopengl_camera glm)

set_target_properties(learnopengl_camera PROPERTIES
                        CXX_STANDARD 20)

file(COPY "assets" DESTINATION ".")