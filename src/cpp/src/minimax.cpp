#include "minimax.h"
#include "globals.h"
#include <deque>
#include <algorithm>
#include <limits.h>

using std::deque;

using namespace constants;
using namespace minimax;

Score TicTacToe::minimax(int depth, char player)
{
    Score best;
    Score score;

    deque<Index> possible_moves = calc_moves();

    if (player == MAX)
    {
        best = Score(default_best_move, INT_MIN);
    }
    else
    {
        best = Score(default_best_move, INT_MAX);
    }

    // Win
    if (check_win(X, default_best_move))
    {
        best = Score(default_best_move, +1);
        return best;
    }
    // Loss
    else if (check_win(O, default_best_move))
    {
        best = Score(default_best_move, -1);
        return best;
    }
    // Draw
    else if (depth == 0)
    {
        best = Score(default_best_move, 0);
    }

    for (Index cell : possible_moves)
    {
        if (player == MAX)
        {
            board[cell.i][cell.j] = MAX;
            score = minimax(depth - 1, MIN);
            board[cell.i][cell.j] = '0';

            if (score.score > best.score)
            {

                score.index.i = cell.i;
                score.index.j = cell.j;
                best = score;
            }
        }

        else if (player == MIN)
        {
            board[cell.i][cell.j] = MIN;
            score = minimax(depth - 1, MAX);
            board[cell.i][cell.j] = '0';

            if (score.score < best.score)
            {
                score.index.i = cell.i;
                score.index.j = cell.j;
                best = score;
            }
        }
    }

    return best;
}
