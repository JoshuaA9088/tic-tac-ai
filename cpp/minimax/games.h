#ifndef GAMES_H
#define GAMES_H

#include "globals.h"
#include "gui.h"
#include "game_rules.h"
#include "minimax.h"

void random_v_human(void);
void human_v_minimax(void);
void human_move(void);
void comp_move_random(char player);
void comp_move_minimax(char player);
char minimax_v_minimax(void);
void minimax_v_random(void);


#endif
