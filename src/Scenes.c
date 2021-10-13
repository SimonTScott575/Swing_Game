#include "Scenes.h"

geScene* g_main_menu;
geScene* g_level_select_menu;

geScene* level_order[LEVELS_COUNT] = {0};
int focused_level_num = 0;

float par_times[LEVELS_COUNT] = {
  30,
  20,
  40,
  30,
  10,
  30
};

float best_times[LEVELS_COUNT] = {
  -1,
  -1,
  -1,
  -1,
  -1,
  -1
};

char* level_names[LEVELS_COUNT] = {
  "LEVEL 1",
  "LEVEL 2",
  "LEVEL 3",
  "LEVEL 4",
  "LEVEL 5",
  "LEVEL 6"
};

Level_Spec g_level_specs[LEVELS_COUNT] = {0};

void Accumulate_Specs() {

  g_level_specs[0].offset_x = -9;
  for (int i = 1; i < LEVELS_COUNT; i++) {
    g_level_specs[i].offset_x = g_level_specs[i-1].offset_x + g_level_specs[i-1].max_x_length/2 + g_level_specs[i].max_x_length/2;
    g_level_specs[i].menu_camera_x_pos = g_level_specs[i].offset_x;
  }

}

void Deport_Best_Times() {

  FILE* file = fopen("../Resources/Best_Times.txt", "rb+");

  for (
    int i = 0;
    i < LEVELS_COUNT;
    i++
  ) {

    fprintf(file, "%.2f\n", best_times[i]);

  }

  fclose(file);

}
void Import_Best_Times() { //!!! UPDATE array !

  FILE* file = fopen("../Resources/Best_Times.txt", "rb");

  char s[101] = {0};

  for (
    int i = 0;
    i < LEVELS_COUNT;
    i++
  ) {

    if (fgets(s,101,file) != NULL) {
      best_times[i] = atof(s);
    } else {
      best_times[i] = -1;
    }

  }

  fclose(file);

}
