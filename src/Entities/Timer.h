#ifndef TIMER_H
#define TIMER_H

#include <Game_Engine/Game_Engine.h>

#include "../Components/Timer_Clock.h"

typedef
struct Timer {

  geEntity* _super;

  mFrame2D* frame;

  grText* text_sec;
  grText* text_msec;

  Timer_Clock* clock;

} Timer;

Timer* Create_Timer(grText* text_sec, grText* text_msec);

void Destroy_Timer_Sub_Entity(geEntity* entity);

#endif
