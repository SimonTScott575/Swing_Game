#include "Level_Selector.h"

Level_Selector* Create_Level_Selector(
  geButton_UI* next_level_b, grRenderer* next_level_r,
  geButton_UI* prev_level_b, grRenderer* prev_level_r,
  geButton_UI* play_level_b, grText_Renderer* play_level_tr,
  Level_Select_Camera_Controller* lscc
) {

  geEntity* entity = geCreate_Entity();

  Level_Select_Navigator* lsn = Create_Level_Select_Navigator(
    next_level_b, next_level_r,
    prev_level_b, prev_level_r,
    play_level_b, play_level_tr,
    lscc
  );

  geAdd_Component(lsn->_super, entity);

  Level_Selector* ls = malloc(sizeof(Level_Selector));
  *ls = (Level_Selector){
    ._super = entity,
    .lsn = lsn
  };

  geSet_Sub_Entity(ls, Destroy_Level_Selector_Sub_Entity, entity);

  return ls;

}

void Destroy_Level_Selector_Sub_Entity(geEntity* entity) {

  Level_Selector* ls = entity->_sub;

  free(ls);

}
