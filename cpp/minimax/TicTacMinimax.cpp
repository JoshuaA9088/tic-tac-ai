#include <iostream>
#include <ncurses.h>
#include <cstdlib>
#include <vector>
#include <unistd.h>
#include <algorithm>
#include <time.h>

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

vector< vector<int> > xPlayed;
vector< vector<int> > oPlayed;

vector< vector<int> > coords = map_coords(dim);

vector<int> min = getMin(map_coords(dim));
vector<int> max = getMax(map_coords(dim));
// GLOBAL VARS //

void test(void);

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

	// human_v_minimax();
	minimax_v_human();
	// random_v_human();
	// minimax_v_minimax();
	// minimax_v_random();
	// test();

	safe_exit();
	return 0;
}

void test()
{
	char winner;
	int xW = 0;
	int oW = 0;
	int stale = 0;

	for (int i = 0; i < 10; i++)
	{
		winner = minimax_v_minimax();

		if (winner == X)
		{
			xW += 1;
		}
		else if (winner == O)
		{
			oW += 1;
		}
		else if (winner == 'S')
		{
			stale += 1;
		}

		reset();
		refresh();
	}

	endwin();
	clear();

	std::cout << "X Wins: " << xW << endl;
	std::cout << "O Wins: " << oW << endl;
	std::cout << "Stalemates: " << stale << endl;
	return;
}
