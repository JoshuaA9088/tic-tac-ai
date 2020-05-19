#ifndef GAME_H
#define GAME_H

#include <deque>
#include "globals.h"

using namespace constants;

class TicTacToe
{
public:
    TicTacToe();
    ~TicTacToe();

    void center();
    void ascii_print();

    bool check_win(char player, Pt last_move);
    bool check_win(char player, Index last_move);
    bool check_win(char player);

    std::deque<Index> calc_moves();
    Score minimax(int depth, char player);

    Pt human_move();
    Pt random_move();
    Pt comp_minimax_move();

    void human_V_random();
    void human_V_minimax();

    char **board;
    Pt **coords;

    Pt min;
    Pt max;

    int total_moves;
};

#endif
