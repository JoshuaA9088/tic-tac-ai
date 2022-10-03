
#include <iostream>

#include "CLI/App.hpp"
#include "CLI/Config.hpp"
#include "CLI/Formatter.hpp"
#include "board.hpp"
#include "config.hpp"

int main(int argc, char** argv)
{
  CLI::App app{DESCRIPTION};

  bool version = false;
  CLI::Option* version_flag = app.add_flag(
      "-v, --version", version, "Output version information and exit");

  CLI::App* human_subcom =
      app.add_subcommand("human", "Play against another human.");
  CLI::App* random_subcom =
      app.add_subcommand("random", "Play against a random number generator.");
  CLI::App* minimax_subcom =
      app.add_subcommand("minimax", "Play against the minimax algorithm.");

  human_subcom->final_callback(
      []()
      {
        Board b;
        b.v_human();
      });
  random_subcom->final_callback(
      []()
      {
        Board b;
        b.v_random();
      });

  auto minimax_callback = []()
  {
    Board b;
    b.v_minimax();
  };
  minimax_subcom->final_callback(minimax_callback);

  CLI11_PARSE(app, argc, argv);

  if (version)
  {
    std::cout << VERSION << "\n";
    return 0;
  }

  // No subcommand specified, fallback to just minimax.
  minimax_callback();

  return 0;
}
