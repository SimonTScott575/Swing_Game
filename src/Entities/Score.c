#include "Score.h"

Score* Create_Score(grText* text_num, grText_Renderer* text_r_num, grText* text_den, grText_Renderer* text_r_den) {

  geEntity* entity = geCreate_Entity();

  Score_Counter* counter = Create_Score_Counter(text_num, text_den);

  text_num->alignment = GR_ALIGN_RIGHT;
  text_den->alignment = GR_ALIGN_LEFT;

  text_r_num->rel_X = text_r_den->rel_X = -1;
  text_r_num->rel_Y = text_r_den->rel_Y = 1;
  text_r_num->frame->position = (mVector2f){{0.2,-0.2}};
  text_r_den->frame->position = (mVector2f){{0.2,-0.2}};

  geAdd_Component(counter->_super, entity);

  Score* score = malloc(sizeof(Score));
  *score = (Score){
    ._super = entity,
    .counter = counter
  };

  geSet_Sub_Entity(score, Destroy_Score_Sub_Entity, entity);

  return score;

}

void Destroy_Score_Sub_Entity(geEntity* entity) {

  Score* score = entity->_sub;

  free(score);

}
