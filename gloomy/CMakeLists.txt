cmake_minimum_required(VERSION 3.16)

set(SOURCES "src/gloomy.cpp" "src/Objects/Program.cpp" "src/Objects/VertexArray.cpp")

add_library(gloomy ${SOURCES})

target_include_directories(gloomy PUBLIC ./include/)

target_include_directories(gloomy PRIVATE ${PROJECT_BINARY_DIR}/glad/include/)
target_link_directories(gloomy PRIVATE ${PROJECT_BINARY_DIR}/glad/build/)
target_link_libraries(gloomy glad)

set_target_properties(gloomy PROPERTIES
                      CXX_STANDARD 20)