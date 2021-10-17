#ifndef TIMER_CLOCK_H
#define TIMER_CLOCK_H

#include <stdbool.h>

#include <Game_Engine/Game_Engine.h>

typedef
struct Timer_Clock {

  geComponent _super;

  grText* text_sec;
  grText* text_msec;

  float time_start;
  float timer_val;

  bool is_first_frame;
  bool is_started;
  bool is_ended;

} Timer_Clock;

void Timer_Clock_ctor(Timer_Clock* self, grText* text_sec, grText* text_msec);

void Update_Timer_Clock(geComponent* component);

#endif
