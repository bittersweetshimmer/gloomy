cmake_minimum_required(VERSION 3.16)

set(SOURCES "src/main.cpp")

add_executable(sandbox ${SOURCES})

target_include_directories(sandbox PUBLIC ./include/)

if(WIN32)
    set(GLFW_PATH "C:/Path/glfw-3.3.2.bin.WIN64")
    set(GLFW_INCLUDE_DIRS ${GLFW_PATH}/include/)
    set(GLFW_LIB_PATH ${GLFW_PATH}/lib-vc2019/)

    target_include_directories(sandbox PRIVATE ${GLFW_INCLUDE_DIRS})
    target_link_directories(sandbox PRIVATE ${GLFW_LIB_PATH})
    target_link_libraries(sandbox glfw3)
else()
    find_package(PkgConfig REQUIRED)
    pkg_search_module(GLFW REQUIRED glfw3)
    target_include_directories(sandbox PRIVATE ${GLFW_INCLUDE_DIRS})
    target_link_libraries(sandbox ${GLFW_STATIC_LIBRARIES})
endif()

target_include_directories(sandbox PRIVATE ${PROJECT_BINARY_DIR}/gloomy/include/)
target_include_directories(sandbox PRIVATE ${PROJECT_BINARY_DIR}/glad/include/)
target_include_directories(sandbox PRIVATE ${PROJECT_BINARY_DIR}/stb/include/)

target_link_directories(sandbox PRIVATE ${PROJECT_BINARY_DIR}/gloomy/build/)
target_link_directories(sandbox PRIVATE ${PROJECT_BINARY_DIR}/glad/build/)
target_link_directories(sandbox PRIVATE ${PROJECT_BINARY_DIR}/stb/build/)

target_link_libraries(sandbox gloomy)
target_link_libraries(sandbox glad)
target_link_libraries(sandbox stb)

set_target_properties(sandbox PROPERTIES
                        CXX_STANDARD 20)

file(COPY "assets" DESTINATION ".")