#ifndef SCORE_H
#define SCORE_H

#include <Game_Engine/Game_Engine.h>

#include "../Components/Score_Counter.h"

typedef
struct Score {

  geEntity* _super;

  Score_Counter* counter;

} Score;

Score* Create_Score(grText* text_num, grText_Renderer* text_r_num, grText* text_den, grText_Renderer* text_r_den);
void Destroy_Score_Sub_Entity(geEntity* entity);

#endif
