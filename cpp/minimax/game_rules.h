#ifndef GAME_RULE_H
#define GAME_RULE_H

#include <vector>
using std::vector;

vector<vector<int>> map_coords(int);
vector<vector<int>> calc_moves();
bool IsSubset(vector<vector<int>>, vector<vector<int>>);
bool check_win(char player, vector<vector<int>> played);

void reset(void);

#endif
