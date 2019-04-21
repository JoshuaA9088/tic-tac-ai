#include <iostream>
#include <ncurses.h>
#include <cstdlib>
#include <vector>
#include <unistd.h> // usleep
#include <algorithm> // std::find

#include "gui.h"
#include "game_rules.h"

#define X 'X'
#define O 'O'

using std::vector;
using std::cout;
using std::cin;
using std::endl;
using std::find;

int doMove(int dim, vector<vector<int>> coords, vector<vector<int>> &xPlayed, vector<vector<int>> &oPlayed);

int main(int argc, char *argv[])
{
	// initscr();
	cbreak();
    noecho();
	keypad(stdscr, TRUE);

/* --------------------------------------------------- Color Stuff */
	start_color();
	init_pair(1, COLOR_WHITE, COLOR_BLACK); // Black
	init_pair(2, COLOR_RED, COLOR_BLACK); // Red
/* --------------------------------------------------- Color Stuff */

	int dim = 3;

    vector<vector<int>> coords = map_coords(dim);
	// Vectors of played moves by each player
	vector<vector<int>> xPlayed, oPlayed;
	vector<vector<int>> possible_moves = calc_moves(3, xPlayed, oPlayed);
	//doMove(dim, coords, xPlayed, oPlayed);
    int y = 2, x = 2, w = 4, h = 2;
	// Create the initial playing board
    board(stdscr, y, x, dim, dim, w, h);
	// Move Cursor to center
	move(coords[4][0], coords[4][1]);

    // ------------- // DEBUG
    getch();
    endwin();
    clear();
    // ------------- // DEBUG

	return 0;
}

int doMove(int dim, vector<vector<int>> coords, vector<vector<int>> &xPlayed, vector<vector<int>> &oPlayed)
{
	vector<int> oVec;
	vector<int> xVec;

    bool awaiting = true;
    int cX, cY;
    int y = 2, x = 2, w = 4, h = 2;

	vector<int> max = getMax(map_coords(3));
	vector<int> min = getMin(map_coords(3));

	board(stdscr, y, x, dim, dim, w, h);
    move(coords[4][0], coords[4][1]);
	refresh();

    while (awaiting){
        int ch = getch();

		if(ch == 'q') // Q to exit
        {
            endwin();
            clear();
            exit(0);
        }
        else if(ch == KEY_LEFT || ch == 'h')
        {
            getyx(stdscr, cY, cX);
			if ((cX - 4) >= min[1]) move(cY, cX - 4);
        }
        else if(ch == KEY_RIGHT || ch == 'l')
        {
            getyx(stdscr, cY, cX);
            if ((cX + 4) <= max[1]) move(cY, cX + 4);
        }
        else if(ch == KEY_UP || ch == 'k')
        {
            getyx(stdscr, cY, cX);
            if ((cY - 2) >= min[0]) move(cY - 2, cX);
        }
        else if(ch == KEY_DOWN || ch == 'j')
        {
            getyx(stdscr, cY, cX);
            if ((cY + 2) <= max[0]) move(cY + 2, cX);
        }
        else if(ch == 'x')
        {
            getyx(stdscr, cY, cX);
            xVec.push_back(cY);
            xVec.push_back(cX);

            if (std::find(oPlayed.begin(), oPlayed.end(), xVec) != oPlayed.end() || std::find(xPlayed.begin(), xPlayed.end(), xVec) != xPlayed.end())
            {
                mvprintw(LINES - 2, 0, "Already played, try again!");
                move(cY, cX);
                refresh();
            }
            else
            {
				mvprintw(LINES - 2, 0, "                            ");
                mvaddch(cY, cX, X);
                move(cY, cX);
                xPlayed.push_back(xVec);
            }
            xVec.clear();
        }
        else if(ch == 'o')
        {
            getyx(stdscr, cY, cX);
            oVec.push_back(cY);
            oVec.push_back(cX);

            if (std::find(oPlayed.begin(), oPlayed.end(), oVec) != oPlayed.end() || std::find(xPlayed.begin(), xPlayed.end(), oVec) != xPlayed.end())
            {
                mvprintw(LINES - 2, 0, "Already played, try again!");
                move(cY, cX);
            }
            else
            {
				mvprintw(LINES - 2, 0, "                            ");
                mvaddch(cY, cX, O);
                move(cY, cX);
                oPlayed.push_back(oVec);
                // awaiting = false;
            }
            oVec.clear();
        }
        refresh();
		if (check_win(X, xPlayed)){
			mvprintw(LINES - 2, 0, "                          ");
			mvprintw(LINES - 2, 0, "X Wins!");
			return 0;
		}
		else if (check_win(O, oPlayed)){
			mvprintw(LINES - 2, 0, "                           ");
			mvprintw(LINES - 2, 0, "O Wins!");
			return 0;
		}
		else if ((oPlayed.size() + xPlayed.size()) == 9)
		{
			mvprintw(LINES - 2, 0, "                           ");
			mvprintw(LINES - 2, 0, "Stalemate!");
			return 0;
		}

    }
    return 0;
}
