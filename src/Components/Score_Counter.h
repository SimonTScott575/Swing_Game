#ifndef SCORE_COUNTER_H
#define SCORE_COUNTER_H

#include <Game_Engine/Game_Engine.h>

typedef
struct Score_Counter {

  geComponent _super;

  grText* text_num;
  grText* text_den;

} Score_Counter;

void Score_Counter_ctor(Score_Counter* self, grText* text_num, grText* text_den);

void Update_Score_Counter(geComponent* component);

void Set_Score_Text(grText* text_num, grText* text_den);

#endif
