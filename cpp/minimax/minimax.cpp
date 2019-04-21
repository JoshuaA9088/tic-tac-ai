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
    vector<vector<int>> possible_moves = calc_moves();
    if (player == MAX)
    {
        best = {-1, -1, -INT8_MAX};
    }
    else
    {
        best = {1, 1, INT8_MAX};
    }
    if (depth == 0)
    {
        best = {-1, -1, 0};
    }
    else if (check_win(X, xPlayed))
    {
        best = {-1, -1, 1};
    }
    else if (check_win(O, oPlayed))
    {
        best = {-1, -1, -1};
    }

    for (vector<int> cell : possible_moves)
    {
        if (player == MAX)
        {
            xPlayed.push_back(cell);
            vector<int> score = minimax(depth - 1, MIN);
            // xPlayed.pop_back();
            xPlayed.erase(std::remove(xPlayed.begin(), xPlayed.end(), cell), xPlayed.end());
            score[0] = cell[1];
            score[1] = cell[0];

            if (score[2] > best[2])
            {
                best = score;
            }
        }
        else if (player == MIN)
        {
            oPlayed.push_back(cell);
            vector<int> score = minimax(depth - 1, MAX);
            // oPlayed.pop_back();
            oPlayed.erase(std::remove(oPlayed.begin(), oPlayed.end(), cell), oPlayed.end());
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
