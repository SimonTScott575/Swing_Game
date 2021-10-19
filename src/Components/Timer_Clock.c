#include "Timer_Clock.h"

#include <string.h>

void Timer_Clock_ctor(Timer_Clock* self, grText* text_sec, grText* text_msec) {

  *self = (Timer_Clock){
    .text_sec = text_sec,
    .text_msec = text_msec,
    .time_start = geGet_Active_Game()->time, //! should be set by level_transitioner
    .timer_val = 0,
    .is_first_frame = true,
    .is_started = false,
    .is_ended = false
  };
  
  geComponent_ctor(&self->_super);
  geSet_Sub_Component(self, Update_Timer_Clock, NULL, &self->_super);

}

void Update_Timer_Clock(geComponent* component) {

  Timer_Clock* clock = component->_sub;

  // //TODO: better way to "trigger" the start of the countdown timer, prefferably a short delay after first frame
  // if (clock->is_first_frame) {
  //   clock->time_start = geGet_Active_Game()->time;
  //   clock->is_first_frame = false;
  // }

  if (!clock->is_started || clock->is_ended) { return; }

  clock->timer_val = geGet_Active_Game()->time - clock->time_start;

  char s_sec[100];
  sprintf(s_sec, "%d", (int)clock->timer_val);

  char s_msec[100];
  sprintf(s_msec, "%.2f", clock->timer_val - (int)clock->timer_val);

  grSet_Text_Contents(s_sec, clock->text_sec);
  grSet_Text_Contents(s_msec+1, clock->text_msec);
  // clock->text->_contents = strdup("a");

}
