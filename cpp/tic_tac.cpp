#include <iostream>
#include <ncurses.h>
#include <cstdlib>
#include <vector>
#include <unistd.h> // usleep
#include <algorithm> // std::find

#define X 'X'
#define O 'O'

using std::vector;
using std::cout;
using std::cin;
using std::endl;
using std::find;


int print(int dim, vector<vector<int>> coords, vector<vector<int>> &xPlayed, vector<vector<int>> &oPlayed);
bool IsSubset(vector<vector<int>>, vector<vector<int>>);
bool check_win(char player, vector<vector<int>> played);
vector<vector<int>> map_coords(int dim);
void board(WINDOW *win, int starty, int startx, int lines, int cols,
	   int tile_width, int tile_height);

int main(int argc, char *argv[])
{
	initscr();
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
    vector<vector<int>> xPlayed, oPlayed;
    print(dim, coords, xPlayed, oPlayed);
    int y = 2, x = 2, w = 4, h = 2;
    board(stdscr, y, x, dim, dim, w, h);
	// Move Cursor to center
	move(coords[4][0], coords[4][1]);
    // ------------- // DEBUG
    // for (int v = 0; v < coords.size(); v++)
    // {
    //     mvaddch(coords[4][0], coords[4][1], X);
    //     usleep(200000);
    //     refresh();
    // }
    getch();
    endwin();
    clear();
    // ------------- // DEBUG

	return 0;
}

vector<vector<int>> map_coords(int dim)
{
    vector<vector<int>> ret;
    vector<int> arr;
    int y = 2, x = 2, w = 4, h = 2;
    int tempy, tempx;

    for (int i = 1; i <= dim; ++i){
        for (int j = 1; j <= dim; ++j){
            int tempy = y + (i - 1) * h + h / 2;
			int tempx = x + (j - 1) * w + w / 2;
            arr.push_back(tempy);
            arr.push_back(tempx);
            ret.push_back(arr);
            arr.clear();
        }
    }
    return ret;
}

int print(int dim, vector<vector<int>> coords, vector<vector<int>> &xPlayed, vector<vector<int>> &oPlayed)
{
    bool awaiting = true;
    int cX, cY;
    int y = 2, x = 2, w = 4, h = 2;
	board(stdscr, y, x, dim, dim, w, h);
    move(coords[4][0], coords[4][1]);
    vector<int> oVec;
    vector<int> xVec;
	refresh();

    // --------------------------- // MOVEMENT MECHANISMS
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
            move(cY, cX - 4);
        }
        else if(ch == KEY_RIGHT || ch == 'l')
        {
            getyx(stdscr, cY, cX);
            move(cY, cX + 4);
        }
        else if(ch == KEY_UP || ch == 'k')
        {
            getyx(stdscr, cY, cX);
            move(cY - 2, cX);
        }
        else if(ch == KEY_DOWN || ch == 'j')
        {
            getyx(stdscr, cY, cX);
            move(cY + 2, cX);
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

    }
    // --------------------------- // MOVEMENT MECHANISMS
    return 0;
}

// Check and see if vec a is a subset of b
bool IsSubset(vector<vector<int>> A, vector<vector<int>> B)
{
    std::sort(A.begin(), A.end());
    std::sort(B.begin(), B.end());
    return std::includes(A.begin(), A.end(), B.begin(), B.end());
}

bool check_win(char player, vector<vector<int>> played)
{
	vector<vector<int>> coords = map_coords(3);

	// Horizontal
	vector<vector<int>> win_0 = {coords[0], coords[1], coords[2]};
	vector<vector<int>> win_1 = {coords[3], coords[4], coords[5]};
	vector<vector<int>> win_2 = {coords[6], coords[7], coords[8]};

	// Verical
	vector<vector<int>> win_3 = {coords[0], coords[3], coords[6]};
	vector<vector<int>> win_4 = {coords[1], coords[4], coords[7]};
	vector<vector<int>> win_5 = {coords[2], coords[5], coords[8]};

	// Diagonal
	vector<vector<int>> win_6 = {coords[0], coords[4], coords[8]};
	vector<vector<int>> win_7 = {coords[2], coords[4], coords[6]};

	// Check all the possible win conditions

	if (played.size() < 3){
		return false;
	}

	else if (IsSubset(played, win_0))
	{
		return true;
	}

	else if (IsSubset(played, win_1))
	{
		return true;
	}

	else if (IsSubset(played, win_2))
	{
		return true;
	}

	else if (IsSubset(played, win_3))
	{
		return true;
	}

	else if (IsSubset(played, win_4))
	{
		return true;
	}

	else if (IsSubset(played, win_5))
	{
		return true;
	}

	else if (IsSubset(played, win_6))
	{
		return true;
	}

	else if (IsSubset(played, win_7))
	{
		return true;
	}
	else
	{
		return false;
	}

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
