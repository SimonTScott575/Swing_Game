#ifndef SCENES_H
#define SCENES_H

#include <Game_Engine/Game_Engine.h>

#define LEVELS_COUNT 8

typedef
struct Level_Spec {

  float menu_camera_x_length;
  float menu_camera_x_pos;
  float menu_camera_y_pos;

  float offset_x;

  float max_x_length;

} Level_Spec;

extern Level_Spec g_level_specs[LEVELS_COUNT];

extern geScene* g_main_menu;
extern geScene* g_level_select_menu;

extern geScene* level_order[LEVELS_COUNT];
extern int focused_level_num;

extern float par_times[LEVELS_COUNT];
extern float best_times[LEVELS_COUNT];

extern char* level_names[LEVELS_COUNT];

extern char* level_name_TEST;

void Accumulate_Specs();

void Deport_Best_Times();
void Import_Best_Times();

#endif
