#include "UI_Manager.h"

UI_Manager* Create_UI_Manager(Portal_Catcher* pc, Timer_Clock* clock, Player_Controller* player_controller,
                              grText* cd_text,           grText_Renderer* cd_text_r,
                              geButton_UI* back_b,       grRenderer* back_r,
                              geButton_UI* restart_b,    grRenderer* restart_r,
                              geButton_UI* next_level_b, grRenderer* next_level_r,
                              grText_Renderer* back_tr, grText_Renderer* restart_tr, grText_Renderer* next_level_tr) {

  geEntity* entity = geCreate_Entity();

  Level_Transitioner* lt = Create_Level_Transitioner(
    pc, clock, player_controller,
    cd_text,      cd_text_r,
    back_b,       back_r,
    restart_b,    restart_r,
    next_level_b, next_level_r,
    back_tr, restart_tr, next_level_tr
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
