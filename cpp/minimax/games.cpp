#include <iostream>
#include <vector>
#include <algorithm>
#include <unistd.h>

#include "globals.h"
#include "gui.h"
#include "game_rules.h"
#include "minimax.h"
#include "games.h"

#define X 'X'
#define O 'O'

using std::vector;

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

		comp_move_random(O);

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

		comp_move_minimax(O);

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

void comp_move_random(char player)
{
	vector<vector<int>> possible_moves;
	int myMoveIndex;
	if (player == O)
	{
		possible_moves = calc_moves();
		myMoveIndex = rand() % possible_moves.size();
		mvaddch(possible_moves[myMoveIndex][0], possible_moves[myMoveIndex][1], O);
		move(possible_moves[myMoveIndex][0], possible_moves[myMoveIndex][1]);
		oPlayed.push_back(possible_moves[myMoveIndex]);
	}
	else if (player == X)
	{
		possible_moves = calc_moves();
		myMoveIndex = rand() % possible_moves.size();
		mvaddch(possible_moves[myMoveIndex][0], possible_moves[myMoveIndex][1], X);
		move(possible_moves[myMoveIndex][0], possible_moves[myMoveIndex][1]);
		xPlayed.push_back(possible_moves[myMoveIndex]);
	}
	return;
}

void comp_move_minimax(char player)
{
    vector<vector<int>> possible_moves = calc_moves();
	vector<int> myMove;
	if (player == O)
	{
		myMove = minimax(possible_moves.size(), O);
		oPlayed.push_back({myMove[0], myMove[1]});
		mvaddch(myMove[0], myMove[1], O);
	}
	else
	{
		myMove = minimax(possible_moves.size(), X);
		xPlayed.push_back({myMove[0], myMove[1]});
		mvaddch(myMove[0], myMove[1], X);
	}
	move(myMove[0], myMove[1]);
	return;
}

void minimax_v_minimax()
{
	vector<vector<int>> possible_moves = calc_moves();
	vector<int> myMove;

	human_move();

	while (xPlayed.size() + oPlayed.size() < 9)
	{
		comp_move_minimax(O);
		refresh();
		// random
		refresh();
	}

	safe_exit();
	return;
}

void minimax_v_random()
{
	human_move();
	while (xPlayed.size() + oPlayed.size() < 9)
	{
		comp_move_minimax(O);
		refresh();

		if (check_win(O, oPlayed))
		{
	        mvprintw(LINES - 2, 0, "                        ");
	        mvprintw(LINES - 2, 0, "O (aka Computer) Won!");
			safe_exit();
	    }

		comp_move_random(X);
		refresh();

		if (check_win(X, xPlayed))
		{
	        mvprintw(LINES - 2, 0, "                        ");
	        mvprintw(LINES - 2, 0, "X (aka Human) Won!");
			safe_exit();
	    }

		usleep(2000);

	}
	safe_exit();
}
