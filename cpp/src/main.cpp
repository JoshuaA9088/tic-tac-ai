
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
  app.add_flag("-v, --version", version, "Output version information and exit");

  CLI::App* human_subcom =
      app.add_subcommand("human", "Play against another human");
  CLI::App* random_subcom =
      app.add_subcommand("random", "Play against a random number generator");
  CLI::App* minimax_subcom =
      app.add_subcommand("minimax", "Play against the minimax algorithm");

  human_subcom->final_callback(
      []()
      {
        Board b;
        b.v_human();
        return 0;
      });
  random_subcom->final_callback(
      []()
      {
        Board b;
        b.v_random();
        return 0;
      });
  const auto minimax_callback = []()
  {
    Board b;
    b.v_minimax();
    return 0;
  };
  minimax_subcom->final_callback(minimax_callback);

  CLI11_PARSE(app, argc, argv);

  if (version)
  {
    std::cout << VERSION << "\n";
    return 0;
  }

  if (!app.got_subcommand(human_subcom) && !app.got_subcommand(random_subcom) &&
      !app.got_subcommand(minimax_subcom))
  {
    minimax_callback();
  }

  return 0;
}
