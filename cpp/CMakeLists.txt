# Works with 3.11 and tested through 3.15
cmake_minimum_required(VERSION 3.11...3.16)

# Project name and a few useful settings. Other commands can pick up the results
project(tic-tac-ai
    VERSION 2.0
    DESCRIPTION "Tic-Tac-Toe with minimax!"
    LANGUAGES CXX)
configure_file(src/config.h.in config.h)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(SRC_FILES
    ${PROJECT_SOURCE_DIR}/src/main.cpp
    ${PROJECT_SOURCE_DIR}/src/board.cpp)
add_executable(${PROJECT_NAME} ${SRC_FILES})

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} curses)

# Compiler warnings
add_compile_options("$<$<CONFIG:Release>:-Wall;-pedantic;-O2;-DNDEBUG")
add_compile_options("$<$<CONFIG:Debug>:-Wall;-pedantic;-O0;-ggdb;-fsanitize=address")
