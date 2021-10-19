#ifndef GLOW_H
#define GLOW_H

#include <Game_Engine/Game_Engine.h>

extern float Screen_X1;
extern float Screen_Y1;
extern float Screen_X2;
extern float Screen_Y2;

extern grShader Glow_Shader;

void Init_Glow_PP(int x, int y);

void Glow_PP(grScreen* screen);

#endif
