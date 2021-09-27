#ifndef GE_INPUT_H
#define GE_INPUT_H

#include <stdbool.h>

#include <Game_Engine/geInput_States.h>
#include <Game_Engine/geGame.h>

bool geKey_Down_Stroke(geGame* game, int key);
bool geKey_Up_Stroke(geGame* game, int key);
bool geMouse_Button_Down_Stroke(geGame* game, int button);
bool geMouse_Button_Up_Stroke(geGame* game, int button);

#endif
