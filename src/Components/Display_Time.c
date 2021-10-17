#include "Display_Time.h"

#include <string.h>

#include "../Scenes.h"

void Display_Time_ctor(Display_Time* self, char* prefix, float* display_times, grText_Renderer* text_r, float x) {

  *self = (Display_Time){
    .prefix = strdup(prefix),
    .prefix_length = strlen(prefix),
    .display_times = display_times,
    .text_r = text_r,
    .x = x
  };

  geComponent_ctor(&self->_super);

  geSet_Sub_Component(self, Update_Display_Time, Display_Time_Sub_Component_dtor, &self->_super);

}

Display_Time* Display_Time_new(char* prefix, float* display_times, grText_Renderer* text_r, float x) {

  Display_Time* dt = malloc(sizeof *dt);

  Display_Time_ctor(dt, prefix, display_times, text_r, x);
  geSet_Sub_Component(dt, dt->_super._update, Display_Time_Sub_Component_del, &dt->_super);

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

void Display_Time_Sub_Component_dtor(geComponent* component) {

  Display_Time* dt = component->_sub;

  free(dt->prefix);

}

void Display_Time_Sub_Component_del(geComponent* component) {

  Display_Time* dt = component->_sub;

  Display_Time_Sub_Component_dtor(&dt->_super);
  free(dt);

}
