#include "game.h"
#include "globals.h"
#include "gui.h"

#include <iostream>
#include <random>
#include <deque>

using namespace constants;
using std::deque;

int index_to_coord(int start, int i, int w)
{
    return start + (i * w) + (w / 2);
}

int coord_to_index(int start, int c, int w)
{
    return (c - start - (w / 2)) / w;
}

TicTacToe::TicTacToe()
{
    total_moves = 0;
    int tempy;
    int tempx;

    board = new char *[3];
    coords = new Pt *[3];

    // Set min and max to arbtriary values.
    min = Pt(100, 100);
    max = Pt(-1, -1);

    for (int i = 0; i < 3; i++)
    {
        board[i] = new char[3];
        coords[i] = new Pt[3];

        for (int j = 0; j < 3; j++)
        {
            board[i][j] = '0';

            tempx = index_to_coord(start_x, i, w);
            tempy = index_to_coord(start_y, j, h);

            if (tempx > max.x)
            {
                max.x = tempx;
            }
            if (tempx < min.x)
            {
                min.x = tempx;
            }

            if (tempy > max.y)
            {
                max.y = tempy;
            }
            if (tempy < min.y)
            {
                min.y = tempy;
            }

            coords[i][j].x = tempx;
            coords[i][j].y = tempy;
            coords[i][j] = Pt(tempx, tempy);
        }
    }
}

TicTacToe::~TicTacToe()
{
    for (int i = 0; i < 3; i++)
    {
        delete[] board[i];
        delete[] coords[i];
    }
    delete[] board;
    delete[] coords;
}

void TicTacToe::update_board()
{
    int x;
    int y;

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (board[i][j] != '0')
            {
                x = index_to_coord(start_x, j, w);
                y = index_to_coord(start_y, i, h);

                mvaddch(y, x, board[i][j]);
            }
        }
    }

    center();
    refresh();
}

void TicTacToe::center()
{
    move(coords[1][1].y, coords[1][0].x);
    return;
}

void TicTacToe::ascii_print()
{
    for (int i = 0; i < 3; i++)
    {
        std::cout << "\n";
        for (int j = 0; j < 3; j++)
        {
            std::cout << board[i][j] << "|";
        }
    }

    return;
}

bool TicTacToe::check_win(char player, Index last_move)
{
    int col, row, diag, rdiag;
    col = row = diag = rdiag = 0;

    int y = last_move.i;
    int x = last_move.j;

    for (int i = 0; i < 3; i++)
    {
        if (board[i][x] == player)
            col++;
        if (board[y][i] == player)
            row++;
        if (board[i][i] == player)
            diag++;
        if (board[2 - i][i] == player)
            rdiag++;
    }

    if (row == 3 || col == 3 || diag == 3 || rdiag == 3)
        return true;

    return false;
}

bool TicTacToe::check_win(char player, Pt last_move)
{
    int col, row, diag, rdiag;
    col = row = diag = rdiag = 0;

    int y = coord_to_index(start_y, last_move.y, h);
    int x = coord_to_index(start_x, last_move.x, w);

    return check_win(player, Index(x, y));
}

deque<Index> TicTacToe::calc_moves()
{
    deque<Index> moves;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (board[i][j] == '0')
                moves.push_back(Index(i, j));
        }
    }

    return moves;
}

Pt TicTacToe::human_move()
{
    Pt my_move;
    bool invalid_move = true;
    center();

    while (invalid_move)
    {
        my_move = handleCursor(min, max);
        int i = coord_to_index(start_y, my_move.y, h);
        int j = coord_to_index(start_x, my_move.x, w);

        if (board[i][j] == '0')
        {
            mvprintw(LINES - 2, 0, "                        ");
            board[i][j] = X;
            update_board();

            total_moves++;
            invalid_move = false;
        }
        else
        {
            mvprintw(LINES - 2, 0, "Invalid move, try again!");
            center();
        }
    }

    return my_move;
}

Pt TicTacToe::random_move()
{
    int i;
    int j;

    bool invalid = true;
    std::random_device rd;
    std::mt19937 eng(rd());
    std::uniform_int_distribution<> distr(0, 2);

    while (invalid)
    {
        i = distr(eng);
        j = distr(eng);

        if (board[i][j] == '0')
        {
            board[i][j] = O;
            update_board();

            total_moves++;
            invalid = false;
        }
    }

    return Pt(j, i);
}

Pt TicTacToe::comp_minimax_move()
{
    deque<Index> possible_moves = calc_moves();
    Score my_move = minimax(possible_moves.size(), O);

    int x = index_to_coord(start_x, my_move.index.i, w);
    int y = index_to_coord(start_y, my_move.index.j, h);

    board[my_move.index.i][my_move.index.j] = O;
    update_board();
    total_moves++;

    return Pt(x, y);
}
