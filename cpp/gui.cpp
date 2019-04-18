#include <ncurses.h>
#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <cstdint>

#include "gui.h"

#define X 'X';
#define O 'O';

using std::vector;
using std::find;

vector<int> getMin(vector<vector<int>> b)
{
    int minX = INT8_MAX;
    int minY = INT8_MAX;
    vector<int> ret;

    for (vector<int> v : b)
    {
        // Get min x / y coord
        if (v[0] < minY) minY = v[0];
        if (v[1] < minX) minX = v[1];
    }
    ret.push_back(minY);
    ret.push_back(minX);
    return ret;
}

vector<int> getMax(vector<vector<int>> b)
{
    int maxX = 0;
    int maxY = 0;
    vector<int> ret;

    for (vector<int> v : b)
    {
        // Get max x / y coord
        if (v[0] > maxY) maxY = v[0];
        if (v[1] > maxX) maxX = v[1];
    }
    ret.push_back(maxY);
    ret.push_back(maxX);
    return ret;
}

void board(WINDOW *win, int starty, int startx, int lines, int cols,
   int tile_width, int tile_height)
{
	int endy, endx, i, j;

	endy = starty + lines * tile_height;
	endx = startx + cols  * tile_width;

	for(j = starty; j <= endy; j += tile_height)
		for(i = startx; i <= endx; ++i)
			mvwaddch(win, j, i, ACS_HLINE);

	for(i = startx; i <= endx; i += tile_width)
		for(j = starty; j <= endy; ++j)
			mvwaddch(win, j, i, ACS_VLINE);

	mvwaddch(win, starty, startx, ACS_ULCORNER);
	mvwaddch(win, endy, startx, ACS_LLCORNER);
	mvwaddch(win, starty, endx, ACS_URCORNER);
	mvwaddch(win, 	endy, endx, ACS_LRCORNER);

	for (j = starty + tile_height; j <= endy - tile_height; j += tile_height)
	{
		mvwaddch(win, j, startx, ACS_LTEE);
		mvwaddch(win, j, endx, ACS_RTEE);
		for (i = startx + tile_width; i <= endx - tile_width; i += tile_width) mvwaddch(win, j, i, ACS_PLUS);
	}

	for (i = startx + tile_width; i <= endx - tile_width; i += tile_width)
	{
		mvwaddch(win, starty, i, ACS_TTEE);
		mvwaddch(win, endy, i, ACS_BTEE);
	}

	wrefresh(win);
}
