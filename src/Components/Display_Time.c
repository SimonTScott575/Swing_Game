#include "Display_Time.h"

#include <string.h>

#include "../Scenes.h"

Display_Time* Create_Display_Time(char* prefix, float* display_times, grText_Renderer* text_r, float x) {

  Display_Time* dt = malloc(sizeof(Display_Time));

  *dt = (Display_Time){
    ._super = geCreate_Component(),
    .prefix = strdup(prefix),
    .prefix_length = strlen(prefix),
    .display_times = display_times,
    .text_r = text_r,
    .x = x
  };

  geSet_Sub_Component(dt, Update_Display_Time, Destroy_Display_Time_Sub_Component, dt->_super);

  return dt;

}

void Update_Display_Time(geComponent* component) {

  Display_Time* dt = component->_sub;

  char* to_set;

  char s[100];
  strcpy(s, dt->prefix);
  if (dt->display_times[focused_level_num] < 0) {
    to_set = "";
  } else {
    sprintf(s + dt->prefix_length,"%.2f",dt->display_times[focused_level_num]);
    to_set = s;
  }

  grSet_Text_Contents(to_set, dt->text_r->text);

  // dt->text_r->frame->position.i[0] = dt->x + focused_level_num*60;

};

void Destroy_Display_Time_Sub_Component(geComponent* component) {

  Display_Time* dt = component->_sub;

  free(dt->prefix);

  free(dt);

}
