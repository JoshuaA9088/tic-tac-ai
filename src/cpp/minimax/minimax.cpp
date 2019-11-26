#include <iostream>
#include <vector>
#include <algorithm>

#include "globals.h"
#include "gui.h"
#include "game_rules.h"
#include "minimax.h"

#define X 'X'
#define O 'O'

#define MAX X
#define MIN O

using std::vector;

vector<int> minimax(int depth, char player)
{
    vector<int> best;
    vector<int> score;
    vector<vector<int>> possible_moves = calc_moves();

    if (player == MAX)
    {
        best = {coords[4][0], coords[4][1], -INT8_MAX};
    }
    else
    {
        best = {coords[4][0], coords[4][1], INT8_MAX};
    }

    // Win
    if (check_win(X, xPlayed))
    {
        best = {coords[4][0], coords[4][1], +1};
        return best;
    }
    // Loss
    else if (check_win(O, oPlayed))
    {
        best = {coords[4][0], coords[4][1], -1};
        return best;
    }
    // Draw
    else if (depth == 0)
    {
        best = {coords[4][0], coords[4][1], 0};
        return best;
    }

    for (vector<int> cell : possible_moves)
    {
        if (player == MAX)
        {
            xPlayed.push_back(cell);
            score = minimax(depth - 1, MIN);
            xPlayed.pop_back();

            score[0] = cell[0];
            score[1] = cell[1];

            if (score[2] > best[2])
            {
                best = score;
            }
        }
        else if (player == MIN)
        {
            oPlayed.push_back(cell);
            score = minimax(depth - 1, MAX);
            oPlayed.pop_back();

            score[0] = cell[0];
            score[1] = cell[1];

            if (score[2] < best[2])
            {
                best = score;
            }
        }
    }
    return best;
}
