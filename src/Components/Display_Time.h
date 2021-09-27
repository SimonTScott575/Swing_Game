#ifndef DISPLAY_TIME_H
#define DISPLAY_TIME_H

#include <Game_Engine/Game_Engine.h>

typedef
struct Display_Time {

  geComponent* _super;

  char* prefix;
  int prefix_length;
  float* display_times;
  grText_Renderer* text_r;

  float x;

} Display_Time;

Display_Time* Create_Display_Time(char* prefix, float* display_times, grText_Renderer* text_r, float x);
void Update_Display_Time(geComponent* component);
void Destroy_Display_Time_Sub_Component(geComponent* component);

#endif
