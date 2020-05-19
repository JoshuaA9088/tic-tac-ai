
# Note that headers are optional, and do not affect add_library, but they will not
# show up in IDEs unless they are listed in add_library.

# Optionally glob, but only for CMake 3.12 or later:
# file(GLOB HEADER_LIST CONFIGURE_DEPENDS "${ModernCMakeExample_SOURCE_DIR}/include/modern/*.hpp")
set(HEADER_LIST "${tic-tac-ai_SOURCE_DIR}/include/tic-tac-ai/game.h"
                "${tic-tac-ai_SOURCE_DIR}/include/tic-tac-ai/globals.h"
                "${tic-tac-ai_SOURCE_DIR}/include/tic-tac-ai/gui.h"
                "${tic-tac-ai_SOURCE_DIR}/include/tic-tac-ai/minimax.h")

# Make an automatic library - will be static or dynamic based on user setting
add_library(tic-tac-library game.cpp gamemodes.cpp gui.cpp main.cpp minimax.cpp ${HEADER_LIST})

# We need this directory, and users of our library will need it too
target_include_directories(tic-tac-library PUBLIC ../include)

# All users of this library will need at least C++11
target_compile_features(tic-tac-library PUBLIC cxx_std_11)

# IDEs should put the headers in a nice place
source_group(TREE "${PROJECT_SOURCE_DIR}/include" PREFIX "Header Files" FILES ${HEADER_LIST})
