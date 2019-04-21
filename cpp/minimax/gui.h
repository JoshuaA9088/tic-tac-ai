#ifndef GUI_H
#define GUI_H

#include <vector>
#include <ncurses.h>
using std::vector;

vector<int> getMin(vector<vector<int>>);
vector<int> getMax(vector<vector<int>>);

vector<int> handleCursor(void);
void board(WINDOW *win, int starty, int startx, int lines, int cols,
	   int tile_width, int tile_height);
void safe_exit(void);

#endif
