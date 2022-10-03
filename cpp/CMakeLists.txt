cmake_minimum_required(VERSION 3.11...3.16)

# Project name and a few useful settings. Other commands can pick up the results
project(tic-tac-ai
    VERSION 2.0
    DESCRIPTION "Tic-Tac-Toe with minimax!"
    LANGUAGES CXX)
configure_file(src/config.h.in config.hpp)

include(FetchContent)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(SRC_FILES
    ${PROJECT_SOURCE_DIR}/src/main.cpp
    ${PROJECT_SOURCE_DIR}/src/board.cpp
    ${PROJECT_SOURCE_DIR}/src/minimax.cpp)
add_executable(${PROJECT_NAME} ${SRC_FILES})

target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_BINARY_DIR})

# External Libraries
FetchContent_Declare(
  cli11
  GIT_REPOSITORY https://github.com/CLIUtils/CLI11
  GIT_TAG        v2.2.0
)
FetchContent_MakeAvailable(cli11)
include_directories(${CLI11_SOURCE_DIR}/include)

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} curses)

# Compiler warnings
# add_compile_options("$<$<CONFIG:Release>:-Wall;-pedantic;-O2;-DNDEBUG")
# add_compile_options("$<$<CONFIG:Debug>:-Wall;-pedantic;-O0;-ggdb;-fsanitize=address")

target_compile_options(
  ${PROJECT_NAME}
  PRIVATE
  -Wall
  -Wextra
  -pedantic)

if (CMAKE_BUILD_TYPE MATCHES "Debug")
  target_compile_options(${PROJECT_NAME} PRIVATE -Og -ggdb -fsanitize=address)
  target_link_options(${PROJECT_NAME} PRIVATE -fsanitize=address)
else()
  target_compile_options(${PROJECT_NAME} PRIVATE -O2)
endif()
