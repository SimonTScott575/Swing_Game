#include "Timer.h"

Timer* Create_Timer(grText* text_sec, grText* text_msec) {

  geEntity* entity = geCreate_Entity();

  text_sec->alignment = GR_ALIGN_RIGHT;
  text_msec->alignment = GR_ALIGN_LEFT;

  Timer_Clock* clock = Create_Timer_Clock(text_sec, text_msec);

  geAdd_Component(clock->_super, entity);

  Timer* timer = malloc(sizeof(Timer));
  entity->_sub = timer;
  *timer = (Timer){

    ._super = entity,

    .text_sec = text_sec,
    .text_msec = text_msec,

    .clock = clock

  };

  geSet_Sub_Entity(timer, Destroy_Timer_Sub_Entity, entity);

  return timer;

}

void Destroy_Timer_Sub_Entity(geEntity* entity) {

  Timer* timer = entity->_sub;

  free(timer);

}
