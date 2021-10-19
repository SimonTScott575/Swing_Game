#include "Timer.h"

Timer* Create_Timer(grText* text_sec, grText* text_msec, geScene* scene) {

  Timer* timer = malloc(sizeof(Timer));
  if (timer == NULL) { return NULL; }

  geEntity_ctor(&timer->_super);
  geSet_Sub_Entity(timer, Destroy_Timer_Sub_Entity, &timer->_super);

  text_sec->alignment = GR_ALIGN_RIGHT;
  text_msec->alignment = GR_ALIGN_LEFT;
  timer->text_sec = text_sec;
  timer->text_msec = text_msec;

  Timer_Clock_ctor(&timer->clock, text_sec, text_msec);

  geAdd_Component(&timer->clock._super, &timer->_super);

  geAdd_Entity(&timer->_super, scene);

  return timer;

}

void Destroy_Timer_Sub_Entity(geEntity* entity) {

  Timer* timer = entity->_sub;

  free(timer);

}
