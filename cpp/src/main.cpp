
#include <iostream>

#include "CLI/App.hpp"
#include "CLI/Config.hpp"
#include "CLI/Formatter.hpp"
#include "board.hpp"
#include "config.hpp"

int main(int argc, char** argv)
{
  CLI::App app{DESCRIPTION};

  CLI::Option* version_flag = app.add_flag("-v", "--version");

  CLI11_PARSE(app, argc, argv);

  // Board b;

  // b.game_loop();

  return 0;
}
