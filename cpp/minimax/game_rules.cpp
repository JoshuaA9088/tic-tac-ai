#include <ncurses.h>
#include <algorithm>
#include <vector>

#include "globals.h"
#include "game_rules.h"

using std::vector;
using std::find;

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

vector<vector<int>> map_coords(int dim)
{
    vector<vector<int>> ret;
    vector<int> arr;
    int tempy, tempx;

    for (int i = 1; i <= dim; ++i){
        for (int j = 1; j <= dim; ++j){
            tempy = y + (i - 1) * h + h / 2;
			tempx = x + (j - 1) * w + w / 2;
            arr.push_back(tempy);
            arr.push_back(tempx);
            ret.push_back(arr);
            arr.clear();
        }
    }
    return ret;
}

vector<vector<int>> calc_moves()
{
    vector<vector<int>> playable = map_coords(dim);

    for (vector<int> move : xPlayed)
    {
        if (find(playable.begin(), playable.end(), move) != playable.end())
        {
            // Erase remove idiom
            playable.erase(std::remove(playable.begin(), playable.end(), move), playable.end());
        }
    }
    for (vector<int> move : oPlayed)
    {
        if (find(playable.begin(), playable.end(), move) != playable.end())
        {
            playable.erase(std::remove(playable.begin(), playable.end(), move), playable.end());
        }
    }
    return playable;
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

void reset()
{
    for (vector<int> i: coords)
    {
        mvaddch(i[0], i[1], ' ');
    }
    xPlayed.clear();
    oPlayed.clear();
    move(coords[4][0], coords[4][1]);
    return;
}
