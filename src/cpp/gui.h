#ifndef GUI_H
#define GUI_H

#include <ncurses.h>
#include "game.h"

Pt handleCursor(Pt min, Pt max);
void board(WINDOW *win, int starty, int startx, int lines, int cols,
           int tile_width, int tile_height);
void safe_exit(void);

#endif
