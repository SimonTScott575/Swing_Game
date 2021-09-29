#include "Timer_Clock.h"

#include <string.h>

Timer_Clock* Create_Timer_Clock(grText* text_sec, grText* text_msec) {

  Timer_Clock* clock = malloc(sizeof(Timer_Clock));

  *clock = (Timer_Clock){
    ._super = geCreate_Component(),
    .text_sec = text_sec,
    .text_msec = text_msec,
    .time_start = geGet_Active_Game()->time, //! should be set by level_transitioner
    .timer_val = 0,
    .is_first_frame = true,
    .is_started = false,
    .is_ended = false
  };

  geSet_Sub_Component(clock, Update_Timer_Clock, Destroy_Timer_Clock_Sub_Component, clock->_super);

  return clock;

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

void Destroy_Timer_Clock_Sub_Component(geComponent* component) {

  Timer_Clock* clock = component->_sub;

  free(clock);

}
