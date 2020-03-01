if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/bitmask/CMakeLists.txt)
    add_subdirectory(bitmask)
else()
    message(FATAL_ERROR "gloomy: No bitmask submodule found. Have you run `git submodule update --init --recursive`?")
endif()

add_subdirectory(glad)