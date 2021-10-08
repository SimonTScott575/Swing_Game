#include "Scenes.h"

geScene* main_menu;
geScene* level_select_menu;
geScene* level_1;
geScene* level_2;
geScene* level_3;

geScene* level_order[LEVELS_COUNT] = {0};
int focused_level_num = 0;

float par_times[LEVELS_COUNT] = {
  30,
  20,
  40
};

float best_times[LEVELS_COUNT] = {
  -1,
  -1,
  -1
};

char* level_names[LEVELS_COUNT] = {
  "LEVEL 1",
  "LEVEL 2",
  "LEVEL 3"
};

char* level_name_TEST = "LEVEL 1";

void Init_Scenes() {

  Import_Best_Times();

}

void Terminate_Scenes() {

  Deport_Best_Times();

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
