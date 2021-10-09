#include <Game_Engine/Game_Engine.h>

#include "Scenes/Level_1_Surfaces_Build.h"
#include "Scenes/Level_2_Basic_Build.h"
#include "Scenes/Level_2_Basic_Build.h"

#define LEVELS_COUNT 4

extern geScene* main_menu;
extern geScene* level_select_menu;
extern geScene* level_1;
extern geScene* level_2;
extern geScene* level_3;
extern geScene* level_4;

extern geScene* level_order[LEVELS_COUNT];
extern int focused_level_num;

extern float par_times[LEVELS_COUNT];
extern float best_times[LEVELS_COUNT];

extern char* level_names[LEVELS_COUNT];

extern char* level_name_TEST;

void Init_Scenes();
void Terminate_Scenes();

void Deport_Best_Times();
void Import_Best_Times();
