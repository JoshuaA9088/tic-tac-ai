# Works with 3.11 and tested through 3.15
cmake_minimum_required(VERSION 3.11...3.16)

# Project name and a few useful settings. Other commands can pick up the results
project(tic-tac-ai
    VERSION 0.1
    DESCRIPTION "Tic-Tac-Toe with minimax!"
    LANGUAGES CXX)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Only do these if this is the main project, and not if it is included through add_subdirectory
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)

    # Optionally set things like CMAKE_CXX_STANDARD, CMAKE_POSITION_INDEPENDENT_CODE here

    # Ensure -std=c++xx instead of -std=g++xx
    set(CMAKE_CXX_EXTENSIONS OFF)

    # Nicely support folders in IDE's
    set_property(GLOBAL PROPERTY USE_FOLDERS ON)

    find_package(Curses REQUIRED)
    include_directories(${CURSES_INCLUDE_DIR})
endif()

add_subdirectory(src)

