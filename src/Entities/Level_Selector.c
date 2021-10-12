#include "Level_Selector.h"

Level_Selector* Create_Level_Selector(
  geEntity* next_level_e,
  geEntity* prev_level_e,
  geEntity* play_level_e,
  geEntity* play_level_text_e,
  geEntity* locked_e,
  Level_Select_Camera_Controller* lscc
) {

  geEntity* entity = geCreate_Entity();

  Level_Select_Navigator* lsn = Create_Level_Select_Navigator(
    next_level_e,
    prev_level_e,
    play_level_e,
    play_level_text_e,
    locked_e,
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
