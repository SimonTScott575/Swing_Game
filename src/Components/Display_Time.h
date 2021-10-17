#ifndef DISPLAY_TIME_H
#define DISPLAY_TIME_H

#include <Game_Engine/Game_Engine.h>

typedef
struct Display_Time {

  geComponent _super;

  char* prefix;
  int prefix_length;
  float* display_times;
  grText_Renderer* text_r;

  float x;

} Display_Time;

void Display_Time_ctor(Display_Time* self, char* prefix, float* display_times, grText_Renderer* text_r, float x);
void Display_Time_Sub_Component_dtor(geComponent* component);

Display_Time* Display_Time_new(char* prefix, float* display_times, grText_Renderer* text_r, float x);
void Display_Time_Sub_Component_del(geComponent* component);

void Update_Display_Time(geComponent* component);

#endif
