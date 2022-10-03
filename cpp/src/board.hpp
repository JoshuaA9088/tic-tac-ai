#ifndef BOARD_HPP
#define BOARD_HPP

#include <ncurses.h>

#include <array>
#include <iostream>
#include <vector>

namespace constants
{
// Player pieces
constexpr char X = 'X';
constexpr char O = 'O';
constexpr char EMPTY = '0';

// Minimax
constexpr char MAX_PLAYER = O;
constexpr char MIN_PLAYER = X;

// Board placement within terminal
constexpr size_t START_X = 2;
constexpr size_t START_Y = 2;

// Board dimensions
constexpr size_t CELL_WIDTH = 4;
constexpr size_t CELL_HEIGHT = 2;
constexpr int BOARD_DIM = 3;
}  // namespace constants

// Helper data structures ------------------------------------------------------

/**
 * @brief A simple representation of a point in 2D space.
 */
template <typename T>
struct Pt
{
  T x;
  T y;
  Pt(T X, T Y) : x(X), y(Y){};
};

template <typename T>
std::ostream& operator<<(std::ostream& os, const Pt<T>& pt);

/**
 * @brief A simple representation of a point in 2D space, type specialized for
 *        int for the sake of more sane default values.
 */
template <>
struct Pt<int>
{
  int x;
  int y;
  Pt() : x(0), y(0){};
  Pt(int X, int Y) : x(X), y(Y){};
};

/**
 * @brief Represents one 'square' within the TicTacToe board. Stores some extra
 *        info to make win checking a bit easier.
 */
struct Cell
{
  Pt<int> pos;
  int index;
  char contents;

  Cell(){};
  Cell(Pt<int> pos, int index) : pos(pos), index(index){};
};

std::ostream& operator<<(std::ostream& os, const Cell& cell);

/**
 * @brief Represents one move, placing a 'X' or 'O' within a square.
 */
struct Move
{
  Cell* cell;
  int score;

  Move() = default;
  Move(Cell* c, int v) : cell(c), score(v){};
};

std::ostream& operator<<(std::ostream& os, const Move& move);

// Debug to print board state to cerr.
std::ostream& operator<<(
    std::ostream& os,
    const std::array<Cell, constants::BOARD_DIM * constants::BOARD_DIM> board);

// Core ------------------------------------------------------------------------
/**
 * @brief Bulk of the game logic.
 */
class Board
{
 private:
  // Storage of the game board positions.
  // +---+---+---+
  // | 0 | 3 | 6 |
  // +---+---+---+
  // | 1 | 4 | 7 |
  // +---+---+---+
  // | 2 | 5 | 8 |
  // +---+---+---+
  std::array<Cell, constants::BOARD_DIM * constants::BOARD_DIM> cells;

  // Minimum and maximum coordinates of cells within terminal.
  // Used to keep the cursor within the board at all times.
  const Pt<int> min;
  const Pt<int> max;

  /**
   * @brief Compute a move given the current board state and player using
   * the minimax algorithm. Recursive implementation.
   *
   * @param depth: Depth of the recursion.
   * @param player: Current player to apply algorithm within.
   * @return: Max or min scored move (depends on player).
   */
  Move minimax(const int depth, const char player);

 public:
  /**
   * @brief Initialize the ncurses environment and display the gameboard.
   */
  Board();
  ~Board();

  /**
   * @brief Draw the gameboard and any other visual attributes.
   */
  void draw() const;

  // Movement
  /**
   * @brief Move the cursor.
   *
   * @param pt: Absolute point on the terminal to move cursor to.
   * @return: ERR on error, OK otherwise.
   */
  int move_cursor(const Pt<int>& pt) const;

  /**
   * @brief Move the cursor.
   *
   * @param index: Cell index to move cursor to.
   * @return: ERR on error, OK otherwise.
   */
  int move_cursor(const int& index) const;

  /**
   * @brief Center the cursor within the gameboard.
   *
   * TODO: Currently broken for gameboard sizes larger than 3x3.
   *
   * @return: ERR on error, OK otherwise.
   */
  int center_cursor() const;

  /**
   * @brief Handle cursor movements within the gameboard.
   *
   * @param pt: Output point the cursor was on when the user pressed SPC.
   * @return: True if the user pressed a valid entry key, false if the user
   *          wants to terminate the program.
   */
  bool handle_cursor(Pt<int>* pt) const;

  /**
   * @brief Check if a player has won the game given the last move.
   *        Since we have the last move, the search space within the board is
   *        generaly smaller. This typically performs better than any other
   *        overload, so use this whenver possible.
   *
   * @param player: Player to check win condition for.
   * @param last_move: Index of cell of last played position.
   * @return: True if player won, false otherwise.
   */
  bool check_win(const char& player, const int& last_move) const;

  /**
   * @brief Check if a player has won the game given the last move.
   *        Searches the entire board for win conditions. Avoid using this for
   *        the sake of performance whenever possible.
   *
   * @param player: Player to check win condition for.
   * @return: True if player won, false otherwise.
   */
  bool check_win(const char& player) const;

  /**
   * @brief Determine if any playable cells exist.
   *
   * @return: True if no playable cells exist, false otherwise.
   */
  bool is_game_over() const;

  /**
   * @brief Display a message depending on which player won, or if a stalemate
   *        occured.
   *
   * @param: Player that won. If player is 'EMPTY' display a stalemate message.
   */
  void win_handler(const char& player) const;

  /**
   * @brief Find all playable cells given the current board state.
   *
   * @return: Vector of all playable cells.
   */
  std::vector<Cell*> get_available_cells() const;

  /**
   * @brief Handy overload simplifying the calling of the private 'minimax'.
   *
   * @return: Move of 'MAX' player given the current board state.
   */
  Move minimax();

  // Game modes
  // TODO: Some simplification here is likely worthwhile.

  /**
   * @brief Play a game human vs. human.
   */
  void v_human();

  /**
   * @brief Play a game human vs. RNG.
   */
  void v_random();

  /**
   * @brief Play a game human vs. minimax algorithm.
   */
  void v_minimax();
};

#endif  // BOARD_HPP
