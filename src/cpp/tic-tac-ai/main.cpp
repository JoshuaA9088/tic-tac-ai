
#include "globals.h"
#include <ncurses.h>
#include <iostream>

#include "gui.h"
#include "game.h"

using namespace constants;

int main()
{
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    // srand(time(NULL));

    start_color();
    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    init_pair(2, COLOR_RED, COLOR_BLACK);

    board(stdscr, start_y, start_x, 3, 3, w, h);

    TicTacToe t;
    t.human_V_random();
    // t.human_V_minimax();
    safe_exit();

    return 0;
}
