#include <iostream>
#include <ncurses.h>
#include <cstdlib> // exit
#include <vector>
#include <unistd.h> // usleep
#include <algorithm> // std::find
#include <time.h> // Randomize seed for rand

#include "globals.h"
#include "gui.h"
#include "game_rules.h"
#include "minimax.h"
#include "games.h"

#define X 'X'
#define O 'O'

using std::vector;
using std::cout;
using std::cin;
using std::endl;
using std::find;

// GLOBAL VARS //
int dim = 3;
int y = 2, x = 2, w = 4, h = 2;

vector<vector<int>> xPlayed;
vector<vector<int>> oPlayed;

vector<vector<int>> coords = map_coords(dim);

vector<int> min = getMin(map_coords(dim));
vector<int> max = getMax(map_coords(dim));
// GLOBAL VARS //

void random_v_human(void);
void human_v_minimax(void);

void human_move(void);
void comp_move_random(void);
void comp_move_minimax(void);

int main()
{
	initscr();
	cbreak();
    noecho();
	keypad(stdscr, TRUE);
	srand(time(NULL));

    // Color Pair Definitions
    start_color();
	init_pair(1, COLOR_WHITE, COLOR_BLACK); // Black
	init_pair(2, COLOR_RED, COLOR_BLACK); // Red

    // Create the initial playing board and move cursor to center
    board(stdscr, y, x, dim, dim, w, h);
	move(coords[4][0], coords[4][1]);

	// random_v_human();
	human_v_minimax();
	// minimax_v_minimax();
	// minimax_v_random();

	return 0;
}
