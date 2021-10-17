#include "Level_Selector.h"

Level_Selector* Create_Level_Selector(
  geEntity* next_level_e,
  geEntity* prev_level_e,
  geEntity* play_level_e,
  geEntity* play_level_text_e,
  geEntity* locked_e,
  Level_Select_Camera_Controller* lscc,
  geScene* scene
) {

  Level_Selector* ls = malloc(sizeof(Level_Selector));
  if (ls == NULL) { return NULL; }

  ls->_super = geEntity_ctor(&ls->_super);
  geSet_Sub_Entity(ls, Destroy_Level_Selector_Sub_Entity, &ls->_super);

  Level_Select_Navigator_ctor(
    &ls->lsn,
    next_level_e,
    prev_level_e,
    play_level_e,
    play_level_text_e,
    locked_e,
    lscc
  );

  geAdd_Component(&ls->lsn._super, &ls->_super);

  geAdd_Entity(&ls->_super, scene);

  return ls;

}

void Destroy_Level_Selector_Sub_Entity(geEntity* entity) {

  Level_Selector* ls = entity->_sub;

  free(ls);

}
