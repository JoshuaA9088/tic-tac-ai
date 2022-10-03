#ifndef BOARD_HPP
#define BOARD_HPP

#include <ncurses.h>

#include <array>
#include <initializer_list>
#include <iostream>
#include <memory>

namespace constants
{
// Player pieces
constexpr char X = 'X';
constexpr char O = 'O';
constexpr char EMPTY = '0';

// Board placement within terminal
constexpr size_t START_X = 2;
constexpr size_t START_Y = 2;

constexpr size_t CELL_WIDTH = 4;
constexpr size_t CELL_HEIGHT = 2;

constexpr int BOARD_DIM = 3;
}  // namespace constants

template <typename T>
struct Pt
{
  T x;
  T y;
  Pt(T X, T Y) : x(X), y(Y){};
};

template <typename T>
std::ostream& operator<<(std::ostream& os, const Pt<T>& pt);

template <>
struct Pt<int>
{
  int x;
  int y;
  Pt() : x(0), y(0){};
  Pt(int X, int Y) : x(X), y(Y){};
};

struct Cell
{
  Pt<int> pos;
  char contents;

  Cell(){};
  Cell(Pt<int> pos) : pos(pos){};
};

std::ostream& operator<<(std::ostream& os, const Cell& cell);

class Board
{
 private:
  // +---+---+---+
  // | 0 | 1 | 2 |
  // +---+---+---+
  // | 3 | 4 | 5 |
  // +---+---+---+
  // | 6 | 7 | 8 |
  // +---+---+---+
  std::array<Cell, constants::BOARD_DIM * constants::BOARD_DIM> cells;
  const Pt<int> min;
  const Pt<int> max;

 public:
  Board();
  ~Board();

  // UI
  void draw() const;

  // Movement
  int move_cursor(const Pt<int>& pt) const;
  int move_cursor(const int& index) const;
  int center_cursor() const;

  bool handle_cursor(Pt<int>* pt) const;

  // Game logic
  bool check_win(const char& player, const int& last_move) const;
  void game_loop();
};

#endif  // BOARD_HPP
