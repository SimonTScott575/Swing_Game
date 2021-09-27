#ifndef TIMER_CLOCK_H
#define TIMER_CLOCK_H

#include <stdbool.h>

#include <Game_Engine/Game_Engine.h>

typedef
struct Timer_Clock {

  geComponent* _super;

  grText* text_sec;
  grText* text_msec;

  float time_start;
  float timer_val;

  bool is_first_frame;
  bool is_started;
  bool is_ended;

} Timer_Clock;

Timer_Clock* Create_Timer_Clock(grText* text_sec, grText* text_msec);
void Destroy_Timer_Clock_Sub_Component(geComponent* component);

void Update_Timer_Clock(geComponent* component);

#endif
