
# Note that headers are optional, and do not affect add_library, but they will not
# show up in IDEs unless they are listed in add_library.

# Optionally glob, but only for CMake 3.12 or later:
# file(GLOB HEADER_LIST CONFIGURE_DEPENDS "${ModernCMakeExample_SOURCE_DIR}/include/modern/*.hpp")
set(HEADER_LIST "${tic-tac-ai_SOURCE_DIR}/include/game.h"
                "${tic-tac-ai_SOURCE_DIR}/include/globals.h"
                "${tic-tac-ai_SOURCE_DIR}/include/gui.h"
                "${tic-tac-ai_SOURCE_DIR}/include/minimax.h")


find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

# Add all the src cpp files with the headers
add_executable(tic-tac-cpp.o game.cpp gamemodes.cpp gui.cpp main.cpp minimax.cpp ${HEADER_LIST})
# Include ncurses
target_link_libraries(tic-tac-cpp.o curses)

# Ensure everything in `include` is included.
target_include_directories(tic-tac-cpp.o PUBLIC ../include)

# C++11
target_compile_features(tic-tac-cpp.o PUBLIC cxx_std_11)

# IDEs should put the headers in a nice place
source_group(TREE "${PROJECT_SOURCE_DIR}/include" PREFIX "Header Files" FILES ${HEADER_LIST})
