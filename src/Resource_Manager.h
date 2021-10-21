#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include <Game_Engine/Game_Engine.h>

#define MAIN_FONT_PATH "../Resources/Fonts/Fira/FiraSans-Heavy.ttf"
#define MAIN_FONT_RES 256

extern grFont* g_main_font;

void Init_Resource_Manager();

void Terminate_Resource_Manager();

#endif
