#include "UI_Manager.h"

UI_Manager* Create_UI_Manager(
  Portal_Catcher* pc, Timer_Clock* clock, Player_Controller* player_controller,
  grText_Renderer* cd_text_r,
  geEntity** end_ui1_arr, // restart and back : button/text entities
  geEntity** end_ui2_arr // next level : button/text entities
) {

  geEntity* entity = geCreate_Entity();

  Level_Transitioner* lt = Create_Level_Transitioner(
    pc, clock, player_controller,
    cd_text_r,
    end_ui1_arr, // restart and back : button/text entities
    end_ui2_arr // next level : button/text entities
  );

  geAdd_Component(lt->_super, entity);

  UI_Manager* uim = malloc(sizeof(UI_Manager));
  *uim = (UI_Manager){
    ._super = entity,
    .lt = lt
  };

  geSet_Sub_Entity(uim, Destroy_UI_Manager_Sub_Entity, entity);

  return uim;

}

void Destroy_UI_Manager_Sub_Entity(geEntity* entity) {

  UI_Manager* uim = entity->_sub;

  free(uim);

}
