#ifndef UI_MANAGER_H
#define UI_MANAGER_H

#include "../Components/Level_Transitioner.h"

typedef struct UI_Manager UI_Manager;

struct UI_Manager {

  geEntity* _super;

  Level_Transitioner* lt;

};

UI_Manager* Create_UI_Manager(Portal_Catcher* pc, Timer_Clock* clock, Player_Controller* player_controller,
                              grText* cd_text,           grText_Renderer* cd_text_r,
                              geButton_UI* back_b,       grRenderer* back_r,
                              geButton_UI* restart_b,    grRenderer* restart_r,
                              geButton_UI* next_level_b, grRenderer* next_level_r,
                              grText_Renderer* back_tr, grText_Renderer* restart_tr, grText_Renderer* next_level_tr);

void Destroy_UI_Manager_Sub_Entity(geEntity* entity);

#endif
