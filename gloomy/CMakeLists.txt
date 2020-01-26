cmake_minimum_required(VERSION 3.16)

set(SOURCES "src/gloomy.cpp" "src/Image.cpp" "src/Objects/Program.cpp" "src/Objects/VertexArray.cpp")

add_library(gloomy ${SOURCES})

target_include_directories(gloomy PUBLIC ./include/)

target_include_directories(gloomy PRIVATE ${GLFW_INCLUDE_PATH})
target_include_directories(gloomy PRIVATE ${PROJECT_BINARY_DIR}/glad/include/)
target_include_directories(gloomy PRIVATE ${PROJECT_BINARY_DIR}/stb/include/)

target_link_directories(gloomy PRIVATE ${GLFW_LIB_PATH})
target_link_directories(gloomy PRIVATE ${PROJECT_BINARY_DIR}/glad/build/)
target_link_directories(gloomy PRIVATE ${PROJECT_BINARY_DIR}/stb/build/)

target_link_libraries(gloomy glfw3)
target_link_libraries(gloomy glad)
target_link_libraries(gloomy stb)

set_target_properties(gloomy PROPERTIES
                      CXX_STANDARD 20)