cmake_minimum_required(VERSION 3.16)

set(SOURCES "src/main.cpp")

add_executable(learnopengl_coordinate_systems ${SOURCES})
set_target_properties(learnopengl_coordinate_systems PROPERTIES
    OUTPUT_NAME "coordinate_systems")

target_include_directories(learnopengl_coordinate_systems PUBLIC ./include/)

if(WIN32)
    target_include_directories(learnopengl_coordinate_systems PRIVATE ${GLFW_INCLUDE_DIRS})
    target_link_directories(learnopengl_coordinate_systems PRIVATE ${GLFW_LIB_PATH})
    target_link_libraries(learnopengl_coordinate_systems glfw3)
else()
    target_include_directories(learnopengl_coordinate_systems PRIVATE ${GLFW_INCLUDE_DIRS})
    target_link_libraries(learnopengl_coordinate_systems ${GLFW_STATIC_LIBRARIES})
endif()

target_link_libraries(learnopengl_coordinate_systems gloomy)
target_link_libraries(learnopengl_coordinate_systems glad)
target_link_libraries(learnopengl_coordinate_systems stb)
target_link_libraries(learnopengl_coordinate_systems glm)

set_target_properties(learnopengl_coordinate_systems PROPERTIES
                        CXX_STANDARD 20)

file(COPY "assets" DESTINATION ".")