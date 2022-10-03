#include <limits>

#include "board.hpp"

using namespace constants;

Move Board::minimax(const int depth, const char player)
{
  Move best;
  Move tmp;

  if (player == MAX_PLAYER)
  {
    best = {/*cell = */ nullptr, /*value = */ std::numeric_limits<int>::min()};
  }
  else if (player == MIN_PLAYER)
  {
    best = {/*cell = */ nullptr, /*value = */ std::numeric_limits<int>::max()};
  }

  const bool max_win = check_win(MAX_PLAYER);
  const bool min_win = check_win(MIN_PLAYER);
  if (depth == 0 || max_win || min_win)
  {
    if (max_win)
    {
      best.score = 1;
    }
    else if (min_win)
    {
      best.score = -1;
    }
    else
    {
      best.score = 0;
    }
    best.cell = nullptr;
    return best;
  }

  std::vector<Cell*> available_cells = get_available_cells();
  for (auto& c : available_cells)
  {
    if (player == MAX_PLAYER)
    {
      c->contents = MAX_PLAYER;
      tmp = minimax(depth - 1, MIN_PLAYER);
      tmp.cell = c;
      c->contents = EMPTY;
      if (tmp.score > best.score)
      {
        best = tmp;
      }
    }
    else if (player == MIN_PLAYER)
    {
      c->contents = MIN_PLAYER;
      tmp = minimax(depth - 1, MAX_PLAYER);
      c->contents = EMPTY;
      tmp.cell = c;
      if (tmp.score < best.score)
      {
        best = tmp;
      }
    }
  }

  return best;
}

Move Board::minimax()
{
  const int depth = get_available_cells().size();
  return minimax(depth, MAX_PLAYER);
}
