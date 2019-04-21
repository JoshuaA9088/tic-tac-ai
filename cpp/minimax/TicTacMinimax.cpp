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

	return 0;
}

void random_v_human()
{
	while (xPlayed.size() + oPlayed.size() < 9)
	{
		human_move();

		if (check_win(X, xPlayed))
		{
	        mvprintw(LINES - 2, 0, "                        ");
	        mvprintw(LINES - 2, 0, "X (aka Human) Won!");
			safe_exit();
	    }

		comp_move_random();

		if (check_win(O, oPlayed))
		{
	        mvprintw(LINES - 2, 0, "                        ");
	        mvprintw(LINES - 2, 0, "O (aka Computer) Won!");
			safe_exit();
	    }
	}
	safe_exit();
}

void human_v_minimax()
{
	while (xPlayed.size() + oPlayed.size() < 9)
	{
		human_move();

		if (check_win(X, xPlayed))
		{
	        mvprintw(LINES - 2, 0, "                        ");
	        mvprintw(LINES - 2, 0, "X (aka Human) Won!");
			safe_exit();
	    }

		comp_move_minimax();

		if (check_win(O, oPlayed))
		{
	        mvprintw(LINES - 2, 0, "                        ");
	        mvprintw(LINES - 2, 0, "O (aka Computer) Won!");
			safe_exit();
	    }
	}
	safe_exit();
}

void human_move()
{
    bool invalid_move = true;
    while (invalid_move)
    {
        vector<int> myMove = handleCursor();
        vector<vector<int>> possible_moves = calc_moves();
        if (std::find(possible_moves.begin(), possible_moves.end(), myMove) != possible_moves.end())
        {
            mvprintw(LINES - 2, 0, "                        ");
            xPlayed.push_back(myMove);
            mvaddch(myMove[0], myMove[1], X);
			move(myMove[0], myMove[1]);
			refresh();
            invalid_move = false;
        }
        else
        {
            mvprintw(LINES - 2, 0, "Invalid move, try again!");
			move(myMove[0], myMove[1]);
        }
    }
}

void comp_move_random()
{
    vector<vector<int>> possible_moves = calc_moves();
	int myMoveIndex = rand() % possible_moves.size();
	mvaddch(possible_moves[myMoveIndex][0], possible_moves[myMoveIndex][1], O);
	move(possible_moves[myMoveIndex][0], possible_moves[myMoveIndex][1]);
	oPlayed.push_back(possible_moves[myMoveIndex]);
	return;
}

void comp_move_minimax()
{
    vector<vector<int>> possible_moves = calc_moves();
	vector<int> myMove = minimax(possible_moves.size(), O);
	oPlayed.push_back({myMove[0], myMove[1]});
	mvaddch(myMove[0], myMove[1], O);
	move(myMove[0], myMove[1]);
	return;
}
