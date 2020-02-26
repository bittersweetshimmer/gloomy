cmake_minimum_required(VERSION 3.16)

project(gloomy_all VERSION 0.1 LANGUAGES CXX C)

option(GLOOMY_EXAMPLES "Build LearnOpenGL examples." OFF)

if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/vendor/bitmask/CMakeLists.txt)
add_subdirectory(vendor/bitmask)
else()
    message(FATAL_ERROR "gloomy: No bitmask submodule found. Have you run `git submodule update --init --recursive`?")
endif()

add_subdirectory(gloomy)

if(GLOOMY_EXAMPLES)
    if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/learnopengl/CMakeLists.txt)
        add_subdirectory(learnopengl)
    else()
        message(FATAL_ERROR "gloomy: No learnopengl submodule found. Have you run `git submodule update --init --recursive`?")
    endif()
endif()