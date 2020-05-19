#include "game.h"
#include "globals.h"
#include <ncurses.h>

using namespace constants;

void TicTacToe::human_V_random()
{
    Pt h_move;
    Pt c_move;

    while (total_moves < 9)
    {
        h_move = human_move();
        if (check_win(X, h_move))
        {
            mvprintw(LINES - 2, 0, "                        ");
            mvprintw(LINES - 2, 0, "X (aka Human) Won!");
            break;
        }

        if (total_moves == 9)
            break;

        c_move = random_move();

        if (check_win(O, c_move))
        {
            mvprintw(LINES - 2, 0, "                        ");
            mvprintw(LINES - 2, 0, "O (aka Computer) Won!");
            break;
        }
    }
}

void TicTacToe::human_V_minimax()
{
    Pt h_move;
    Pt c_move;

    while (total_moves < 9)
    {

        c_move = comp_minimax_move();

        if (check_win(O, c_move))
        {
            mvprintw(LINES - 2, 0, "                        ");
            mvprintw(LINES - 2, 0, "O (aka Computer) Won!");
            break;
        }

        if (total_moves == 9)
            break;

        h_move = human_move();
        if (check_win(X, h_move))
        {
            mvprintw(LINES - 2, 0, "                        ");
            mvprintw(LINES - 2, 0, "X (aka Human) Won!");
            break;
        }
    }

    return;
}
