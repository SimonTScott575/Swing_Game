#include "Level_Title.h"

#include "../Scenes.h"

Level_Title* Create_Level_Title(float x, grText_Renderer* text_r) {

  Level_Title* lt = malloc(sizeof(Level_Title));

  *lt = (Level_Title){
    ._super = geCreate_Component(),
    .x = x,
    .text_r = text_r
  };

  geSet_Sub_Component(lt, Update_Level_Title, Destroy_Level_Title_Sub_Component, lt->_super);

  return lt;

}

void Update_Level_Title(geComponent* component) {

  Level_Title* lt = component->_sub;

  grSet_Text_Contents(level_names[focused_level_num], lt->text_r->text);

  lt->text_r->frame->position.i[0] = lt->x + focused_level_num*60;

}

void Destroy_Level_Title_Sub_Component(geComponent* component) {

  Level_Title* lt = component->_sub;

  free(lt);

}
