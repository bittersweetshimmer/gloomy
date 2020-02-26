cmake_minimum_required(VERSION 3.16)

project(gloomy)
set(SOURCES "src/glad.cpp" "src/gloomy.cpp" "src/Objects/Program.cpp" "src/Objects/VertexArray.cpp")

option(GLOOMY_DEBUG "Check OpenGL errors after each call." off)

add_library(gloomy ${SOURCES})

if(WIN32)
    target_compile_definitions(gloomy PUBLIC -DNOMINMAX)
endif()

if(GLOOMY_DEBUG)
    target_compile_definitions(gloomy PUBLIC -DGLOOMY_DEBUG)
    message("gloomy: Compiling with OpenGL call error checks.")
endif()

target_include_directories(gloomy PUBLIC ./include/)
target_link_libraries(gloomy bitmask)

set_target_properties(gloomy PROPERTIES
                      CXX_STANDARD 20)