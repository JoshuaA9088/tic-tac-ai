#include "board.hpp"

#include <algorithm>
#include <ctime>
#include <iostream>

using namespace constants;

// Helper ----------------------------------------------------------------------
template <typename T>
std::ostream& operator<<(std::ostream& os, const Pt<T>& pt)
{
  os << "Pt(x=" << pt.x << ", y=" << pt.y << ")";
  return os;
}

std::ostream& operator<<(std::ostream& os, const Cell& cell)
{
  os << "Cell(contents=" << cell.contents << ", pos=" << cell.pos
     << ", index=" << cell.index << ")";
  return os;
}

std::ostream& operator<<(std::ostream& os, const Move& move)
{
  os << "Move(cell=";
  if (move.cell != nullptr)
  {
    os << *move.cell;
  }
  else
  {
    os << "nullptr";
  }

  os << ", value=" << move.score << ")";
  return os;
}

std::ostream& operator<<(std::ostream& os,
                         const std::array<Cell, BOARD_DIM * BOARD_DIM> board)
{
  for (int i = 0; i < BOARD_DIM; ++i)
  {
    for (int j = 0; j < BOARD_DIM; ++j)
    {
      int index = (i * BOARD_DIM) + j;
      os << board[index].contents << " ";
    }
    os << "\n";
  }

  return os;
}

// Core ------------------------------------------------------------------------
Board::Board()
    : min(START_X + (CELL_WIDTH / 2), START_Y + (CELL_HEIGHT / 2)),
      max(START_X + (BOARD_DIM * CELL_WIDTH) + (CELL_WIDTH / 2),
          START_Y + (BOARD_DIM * CELL_HEIGHT) + (CELL_HEIGHT / 2))
{
  // Initialize the cells of the board.
  for (int i = 0; i < BOARD_DIM; ++i)
  {
    for (int j = 0; j < BOARD_DIM; ++j)
    {
      int index = (i * BOARD_DIM) + j;
      cells[index].contents = EMPTY;
      cells[index].pos.x = START_X + (i * CELL_WIDTH) + (CELL_WIDTH / 2);
      cells[index].pos.y = START_Y + (j * CELL_HEIGHT) + (CELL_HEIGHT / 2);
      cells[index].index = index;
    }
  }

  // Setup the ncurses GUI.
  initscr();
  cbreak();
  noecho();
  keypad(stdscr, true);

  start_color();
  init_pair(1, COLOR_WHITE, COLOR_BLACK);
  init_pair(2, COLOR_RED, COLOR_BLACK);

  draw();
  center_cursor();
}

Board::~Board()
{
  endwin();
  clear();
}

void Board::draw() const
{
  constexpr int end_y = START_Y + BOARD_DIM * CELL_HEIGHT;
  constexpr int end_x = START_X + BOARD_DIM * CELL_WIDTH;

  for (int j = START_Y; j <= end_y; j += CELL_HEIGHT)
  {
    for (int i = START_X; i <= end_x; ++i)
    {
      mvwaddch(stdscr, j, i, ACS_HLINE);
    }
  }

  for (int i = START_X; i <= end_x; i += CELL_WIDTH)
  {
    for (int j = START_Y; j <= end_y; ++j)
    {
      mvwaddch(stdscr, j, i, ACS_VLINE);
    }
  }

  mvwaddch(stdscr, START_Y, START_X, ACS_ULCORNER);
  mvwaddch(stdscr, end_y, START_X, ACS_LLCORNER);
  mvwaddch(stdscr, START_Y, end_x, ACS_URCORNER);
  mvwaddch(stdscr, end_y, end_x, ACS_LRCORNER);

  for (int j = START_Y + CELL_HEIGHT; j <= end_y - CELL_HEIGHT;
       j += CELL_HEIGHT)
  {
    mvwaddch(stdscr, j, START_X, ACS_LTEE);
    mvwaddch(stdscr, j, end_x, ACS_RTEE);
    for (int i = START_X + CELL_WIDTH; i <= end_x - CELL_WIDTH; i += CELL_WIDTH)
    {
      mvwaddch(stdscr, j, i, ACS_PLUS);
    }
  }

  for (int i = START_X + CELL_WIDTH; i <= end_x - CELL_WIDTH; i += CELL_WIDTH)
  {
    mvwaddch(stdscr, START_Y, i, ACS_TTEE);
    mvwaddch(stdscr, end_y, i, ACS_BTEE);
  }

  // Draw all the played positions
  for (auto& c : cells)
  {
    if (c.contents != EMPTY)
    {
      mvwaddch(stdscr, c.pos.y, c.pos.x, c.contents);
    }
  }

  wrefresh(stdscr);
  center_cursor();
}

int Board::move_cursor(const Pt<int>& pt) const
{
  return move(pt.y, pt.x);
}

int Board::move_cursor(const int& index) const
{
  if (index < 0 || index > BOARD_DIM * BOARD_DIM - 1)
  {
    // Keep to the ncurses conventions...
    return ERR;
  }
  Pt<int> dst;

  const int x = index % BOARD_DIM;
  const int y = index / BOARD_DIM;

  dst.x = START_X + (x * CELL_WIDTH) + (CELL_WIDTH / 2);
  dst.y = START_Y + (y * CELL_HEIGHT) + (CELL_HEIGHT / 2);

  return move_cursor(dst);
}

int Board::center_cursor() const
{
  return move_cursor(BOARD_DIM + 1);
}

bool Board::handle_cursor(Pt<int>* pt) const
{
  // Pt<int> pt;
  int ch;

  do
  {
    // Get a keypress from ncurses
    ch = getch();
    getyx(stdscr, pt->y, pt->x);
    switch (ch)
    {
      case 'q':
        return false;

      case KEY_LEFT:
      case 'h':
        pt->x -= CELL_WIDTH;
        if (pt->x >= min.x) move_cursor(*pt);
        break;

      case KEY_RIGHT:
      case 'l':
        pt->x += CELL_WIDTH;
        if (pt->x < max.x) move_cursor(*pt);
        break;

      case KEY_UP:
      case 'k':
        pt->y -= CELL_HEIGHT;
        if (pt->y >= min.y) move_cursor(*pt);
        break;

      case KEY_DOWN:
      case 'j':
        pt->y += CELL_HEIGHT;
        if (pt->y < max.y) move_cursor(*pt);
        break;
    }
  } while (ch != ' ');

  return true;
}

bool Board::check_win(const char& player, const int& last_move) const
{
  int col, row, diag, rdiag;
  col = row = diag = rdiag = 0;

  const int y = last_move / BOARD_DIM;
  const int x = last_move % BOARD_DIM;

  int index;
  for (int i = 0; i < BOARD_DIM; i++)
  {
    index = (y * BOARD_DIM) + i;
    if (cells[index].contents == player)
    {
      ++col;
    }

    index = (i * BOARD_DIM) + x;
    if (cells[index].contents == player)
    {
      ++row;
    }

    index = (i * BOARD_DIM) + i;
    if (cells[index].contents == player)
    {
      ++diag;
    }

    index = (i * BOARD_DIM) + (BOARD_DIM - i - 1);
    if (cells[index].contents == player)
    {
      ++rdiag;
    }
  }

  return (col == BOARD_DIM || row == BOARD_DIM || diag == BOARD_DIM ||
          rdiag == BOARD_DIM);
}

bool Board::check_win(const char& player) const
{
  int col, row, diag, rdiag;
  col = row = diag = rdiag = 0;

  for (int i = 0; i < BOARD_DIM; i++)
  {
    for (int j = 0; j < BOARD_DIM; j++)
    {
      const int col_index = (j * BOARD_DIM) + i;
      const int row_index = (i * BOARD_DIM) + j;
      if (cells[col_index].contents == player)
      {
        ++col;
      }

      if (cells[row_index].contents == player)
      {
        ++row;
      }
    }

    if (col >= BOARD_DIM || row >= BOARD_DIM)
    {
      return true;
    }
    col = row = 0;
  }

  int diag_index = 0;
  for (int i = 0; i < BOARD_DIM; i++)
  {
    if (cells[diag_index].contents == player)
    {
      diag++;
    }
    diag_index += 4;
  }
  if (diag >= BOARD_DIM)
  {
    return true;
  }

  int rdiag_index = 2;
  for (int i = 0; i < BOARD_DIM; i++)
  {
    if (cells[rdiag_index].contents == player)
    {
      rdiag++;
    }
    rdiag_index += 2;
  }

  if (rdiag >= BOARD_DIM)
  {
    return true;
  }

  return false;
}

bool Board::is_game_over() const
{
  for (auto& c : cells)
  {
    if (c.contents == EMPTY)
    {
      return false;
    }
  }

  return true;
}

void Board::win_handler(const char& player) const
{
  const int pos = LINES - 2;
  mvprintw(pos, 0, "                            ");
  if (player != EMPTY)
  {
    mvprintw(pos, 0, "Player %c Won!", player);
  }
  else
  {
    mvprintw(pos, 0, "Stalemate!");
  }
}

std::vector<Cell*> Board::get_available_cells() const
{
  std::vector<Cell*> result;
  result.reserve(16);

  for (auto& c : cells)
  {
    if (c.contents == EMPTY)
    {
      result.push_back(const_cast<Cell*>(&c));
    }
  }

  return result;
}

void Board::v_human()
{
  char current_turn = X;
  int i, x, y;
  Cell* current_cell;
  Pt<int> move;
  while (handle_cursor(&move) && !is_game_over())
  {
    x = (move.x - START_X - (CELL_WIDTH / 2)) / CELL_WIDTH;
    y = (move.y - START_Y - (CELL_HEIGHT / 2)) / CELL_HEIGHT;
    i = (x * BOARD_DIM) + y;
    current_cell = &cells[i];

    switch (current_turn)
    {
      case X:
        if (current_cell->contents != EMPTY)
        {
          continue;
        }

        current_cell->contents = X;
        break;

      case O:
        if (current_cell->contents != EMPTY)
        {
          continue;
        }

        current_cell->contents = O;
        break;
    }

    if (check_win(current_turn, i))
    {
      win_handler(current_turn);
      draw();
      getch();
      break;
    }
    current_turn = current_turn == X ? O : X;

    draw();
  }

  win_handler(EMPTY);
  draw();
  getch();
}

void Board::v_random()
{
  char current_turn = X;
  int i, x, y;
  Cell* current_cell;
  Pt<int> move;

  srand(std::time(0));
  while (!is_game_over())
  {
    // Handle an input from the user.
    while (current_turn == X)
    {
      if (!handle_cursor(&move))
      {
        return;
      }
      x = (move.x - START_X - (CELL_WIDTH / 2)) / CELL_WIDTH;
      y = (move.y - START_Y - (CELL_HEIGHT / 2)) / CELL_HEIGHT;
      i = (x * BOARD_DIM) + y;
      current_cell = &cells[i];

      if (current_cell->contents != EMPTY)
      {
        continue;
      }
      current_cell->contents = X;

      if (check_win(current_turn, i))
      {
        win_handler(current_turn);
        draw();
        getch();
        return;
      }
      current_turn = O;

      draw();
    }

    // Simulate a machine move.
    const std::vector<Cell*> available_moves = get_available_cells();
    const int random_index = std::rand() % available_moves.size();
    available_moves[random_index]->contents = O;

    if (check_win(current_turn, available_moves[random_index]->index))
    {
      win_handler(current_turn);
      getch();
      draw();
      return;
    }

    current_turn = X;
    draw();
  }

  win_handler(EMPTY);
  draw();
  getch();
}

void Board::v_minimax()
{
  char current_turn = X;
  int i, x, y;
  Cell* current_cell;
  Pt<int> move;

  srand(std::time(0));
  while (!is_game_over())
  {
    // Handle an input from the user.
    while (current_turn == X)
    {
      if (!handle_cursor(&move))
      {
        return;
      }
      x = (move.x - START_X - (CELL_WIDTH / 2)) / CELL_WIDTH;
      y = (move.y - START_Y - (CELL_HEIGHT / 2)) / CELL_HEIGHT;
      i = (x * BOARD_DIM) + y;
      current_cell = &cells[i];

      if (current_cell->contents != EMPTY)
      {
        continue;
      }
      current_cell->contents = X;

      if (check_win(current_turn, i))
      {
        win_handler(current_turn);
        draw();
        getch();
        return;
      }
      current_turn = O;

      draw();
    }

    Move comp_move = minimax();
    if (comp_move.cell == nullptr)
    {
      // Stalemate
      break;
    }
    comp_move.cell->contents = O;

    if (check_win(current_turn, comp_move.cell->index))
    {
      win_handler(current_turn);
      draw();
      getch();
      return;
    }

    current_turn = X;
    draw();
  }

  win_handler(EMPTY);
  draw();
  getch();
}
