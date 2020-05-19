#include <ncurses.h>
#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <cstdint>

#include "globals.h"
#include "gui.h"
#include "game.h"

Pt handleCursor(Pt min, Pt max)
{
    int cX, cY;
    char ch;
    do
    {
        ch = getch();
        if (ch == 'q') // Q to exit gracefully
        {
            safe_exit();
        }
        else if (ch == KEY_LEFT || ch == 'h')
        {
            getyx(stdscr, cY, cX);
            if ((cX - 4) >= min.x)
                move(cY, cX - 4);
        }
        else if (ch == KEY_RIGHT || ch == 'l')
        {
            getyx(stdscr, cY, cX);
            if ((cX + 4) <= max.x)
                move(cY, cX + 4);
        }
        else if (ch == KEY_UP || ch == 'k')
        {
            getyx(stdscr, cY, cX);
            if ((cY - 2) >= min.y)
                move(cY - 2, cX);
        }
        else if (ch == KEY_DOWN || ch == 'j')
        {
            getyx(stdscr, cY, cX);
            if ((cY + 2) <= max.y)
                move(cY + 2, cX);
        }
    } while (ch != ' ');

    getyx(stdscr, cY, cX);
    return Pt(cX, cY);
}

void board(WINDOW *win, int starty, int startx, int lines, int cols,
           int tile_width, int tile_height)
{
    int endy, endx, i, j;

    endy = starty + lines * tile_height;
    endx = startx + cols * tile_width;

    for (j = starty; j <= endy; j += tile_height)
        for (i = startx; i <= endx; ++i)
            mvwaddch(win, j, i, ACS_HLINE);

    for (i = startx; i <= endx; i += tile_width)
        for (j = starty; j <= endy; ++j)
            mvwaddch(win, j, i, ACS_VLINE);

    mvwaddch(win, starty, startx, ACS_ULCORNER);
    mvwaddch(win, endy, startx, ACS_LLCORNER);
    mvwaddch(win, starty, endx, ACS_URCORNER);
    mvwaddch(win, endy, endx, ACS_LRCORNER);

    for (j = starty + tile_height; j <= endy - tile_height; j += tile_height)
    {
        mvwaddch(win, j, startx, ACS_LTEE);
        mvwaddch(win, j, endx, ACS_RTEE);
        for (i = startx + tile_width; i <= endx - tile_width; i += tile_width)
            mvwaddch(win, j, i, ACS_PLUS);
    }

    for (i = startx + tile_width; i <= endx - tile_width; i += tile_width)
    {
        mvwaddch(win, starty, i, ACS_TTEE);
        mvwaddch(win, endy, i, ACS_BTEE);
    }
    wrefresh(win);
}

void safe_exit()
{
    mvprintw(LINES - 1, 0, "Press any key to exit...");
    getch();
    endwin();
    clear();
    exit(0);
}
