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
	    }

		comp_move_random(O);

		if (check_win(O, oPlayed))
		{
	        mvprintw(LINES - 2, 0, "                        ");
	        mvprintw(LINES - 2, 0, "O (aka Computer) Won!");
	    }
	}
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
	    }

		comp_move_minimax(O);

		if (check_win(O, oPlayed))
		{
	        mvprintw(LINES - 2, 0, "                        ");
	        mvprintw(LINES - 2, 0, "O (aka Computer) Won!");
	    }
	}
}

void human_move()
{
    bool invalid_move = true;
	vector<int> myMove;
	vector<vector<int>> possible_moves;
    while (invalid_move)
    {
        myMove = handleCursor();
        possible_moves = calc_moves();
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
	move(coords[4][0], coords[4][1]);
	if (player == O)
	{
		myMove = minimax(possible_moves.size(), O);
		oPlayed.push_back({myMove[0], myMove[1]});
		mvaddch(myMove[0], myMove[1], O);
		move(myMove[0], myMove[1]);
	}
	else
	{
		myMove = minimax(possible_moves.size(), X);
		xPlayed.push_back({myMove[0], myMove[1]});
		mvaddch(myMove[0], myMove[1], X);
		move(myMove[0], myMove[1]);
	}
	return;
}

char minimax_v_minimax()
{
	vector<vector<int>> possible_moves = calc_moves();
	vector<int> myMove;

	// Decide the first move to reduce time to play just kidding
	// oPlayed.push_back(possible_moves[4]);
	// mvaddch(possible_moves[4][0], possible_moves[4][1], O);
	move(possible_moves[4][0], possible_moves[4][1]);

	while (xPlayed.size() + oPlayed.size() < 9)
	{
		comp_move_minimax(X);
		refresh();

		if (check_win(X, xPlayed))
		{
	        mvprintw(LINES - 2, 0, "                        ");
	        mvprintw(LINES - 2, 0, "X (aka Computer) Won!");
			return X;
		}

		comp_move_minimax(O);
		refresh();

		if (check_win(O, oPlayed))
		{
			mvprintw(LINES - 2, 0, "                        ");
			mvprintw(LINES - 2, 0, "O (aka Computer) Won!");
			return O;
		}
	}
	return 'S';
}

void minimax_v_random()
{
	// human_move();
	move(coords[4][0], coords[4][1]);
	while (xPlayed.size() + oPlayed.size() < 9)
	{
		comp_move_minimax(O);
		refresh();

		if (check_win(O, oPlayed))
		{
	        mvprintw(LINES - 2, 0, "                        ");
	        mvprintw(LINES - 2, 0, "O (aka Computer) Won!");
	    }

		usleep(100000);

		comp_move_random(X);
		refresh();

		if (check_win(X, xPlayed))
		{
	        mvprintw(LINES - 2, 0, "                        ");
	        mvprintw(LINES - 2, 0, "X (aka Human) Won!");
	    }

		usleep(100000);

	}
}
