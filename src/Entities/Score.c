#include "Score.h"

Score* Create_Score(
  grText* text_num, grText_Renderer* text_r_num,
  grText* text_den, grText_Renderer* text_r_den,
  geScene* scene
) {

  Score* score = malloc(sizeof(Score));
  if (score == NULL) { return NULL; }

  geEntity_ctor(&score->_super);
  geSet_Sub_Entity(score, Destroy_Score_Sub_Entity, &score->_super);

  Score_Counter_ctor(&score->counter, text_num, text_den);

  text_num->alignment = GR_ALIGN_RIGHT;
  text_den->alignment = GR_ALIGN_LEFT;

  geAdd_Component(&score->counter._super, &score->_super);

  geAdd_Entity(&score->_super, scene);

  return score;

}

void Destroy_Score_Sub_Entity(geEntity* entity) {

  Score* score = entity->_sub;

  free(score);

}
