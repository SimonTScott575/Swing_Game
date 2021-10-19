#include "UI_Manager.h"

UI_Manager* Create_UI_Manager(
  Portal_Catcher* pc, Timer_Clock* clock, Player_Controller* player_controller,
  grText_Renderer* cd_text_r,
  geEntity** end_ui1_arr, // restart and back : button/text entities
  geEntity** end_ui2_arr, // next level : button/text entities
  geScene* scene
) {

  UI_Manager* uim = malloc(sizeof(UI_Manager));
  if (uim == NULL) { return NULL; }

  geEntity_ctor(&uim->_super);
  geSet_Sub_Entity(uim, Destroy_UI_Manager_Sub_Entity, &uim->_super);

  Level_Transitioner_ctor(
    &uim->lt,
    pc, clock, player_controller,
    cd_text_r,
    end_ui1_arr, // restart and back : button/text entities
    end_ui2_arr // next level : button/text entities
  );

  geAdd_Component(&uim->lt._super, &uim->_super);

  geAdd_Entity(&uim->_super, scene);

  return uim;

}

void Destroy_UI_Manager_Sub_Entity(geEntity* entity) {

  UI_Manager* uim = entity->_sub;

  free(uim);

}
