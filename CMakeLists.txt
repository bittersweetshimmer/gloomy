cmake_minimum_required(VERSION 3.16)

project(gloomy VERSION 0.1 LANGUAGES CXX C)

set(GLFW_PATH "C:/Path/glfw-3.3.2.bin.WIN64")
set(GLFW_INCLUDE_PATH ${GLFW_PATH}/include/)
set(GLFW_LIB_PATH ${GLFW_PATH}/lib-vc2019/)

add_subdirectory(glad)
add_subdirectory(stb)
add_subdirectory(gloomy)
add_subdirectory(sandbox)