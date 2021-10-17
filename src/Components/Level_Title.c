#include "Level_Title.h"

#include "../Scenes.h"

void Level_Title_ctor(Level_Title* self, float x, grText_Renderer* text_r) {

  *self = (Level_Title){
    .x = x,
    .text_r = text_r
  };
  geComponent_ctor(&self->_super);

  geSet_Sub_Component(self, Update_Level_Title, NULL, &self->_super);

}
Level_Title* Level_Title_new(float x, grText_Renderer* text_r) {

  Level_Title* lt = malloc(sizeof *lt);

  Level_Title_ctor(lt, x, text_r);
  geSet_Sub_Component(lt, lt->_super._update, Level_Title_Sub_Component_del, &lt->_super);

  return lt;

}

void Level_Title_Sub_Component_del(geComponent* component) {

  Level_Title* lt = component->_sub;

  free(lt);

}

void Update_Level_Title(geComponent* component) {

  Level_Title* lt = component->_sub;

  grSet_Text_Contents(level_names[focused_level_num], lt->text_r->text);

  // lt->text_r->frame->position.i[0] = lt->x + focused_level_num*60;

}
