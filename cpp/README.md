# TicTacAi - C++ Implementation

Console TicTacToe with minimax implemented in C++ using ncurses.

## Dependencies

Currently this project is only compatible with Linux, but I do plan to
eventually port this to Windows once I find a suitable, portable, replacement
for ncurses. You will need the following:

- A C++11 compliant compiler (clang, gcc, etc.)
- cmake >= v3.11
- ncurses

## Compiling

1. Clone this repository

   ```sh
   $ git clone http://github.com/jarulsamy/tic-tac-ai
   $ cd tic-tac-ai
   ```

2. Initialize the build environment

   ```sh
   $ mkdir build
   $ cd build
   $ cmake .. -DCMAKE_BUILD_TYPE=Release
   ```

3. Build

   ```sh
   $ make
   ```

4. Run

   ```sh
   $ ./tic-tac-ai minimax
   ```

   There are multiple gamemodes available. More information can be found in the
   help page.

   ```sh
   $ ./tic-tac-ai --help
   Tic-Tac-Toe with minimax!
   Usage: ./tic-tac-ai [OPTIONS] SUBCOMMAND

   Options:
     -h,--help                   Print this help message and exit
     -v,--version                Output version information and exit

   Subcommands:
     human                       Play against another human
     random                      Play against a random number generator
     minimax                     Play against the minimax algorithm
   ```
