#ifndef UI_MANAGER_H
#define UI_MANAGER_H

#include "../Components/Level_Transitioner.h"

typedef struct UI_Manager UI_Manager;

struct UI_Manager {

  geEntity _super;

  Level_Transitioner lt;

};

UI_Manager* Create_UI_Manager(
  Portal_Catcher* pc, Timer_Clock* clock, Player_Controller* player_controller,
  grText_Renderer* cd_text_r,
  geEntity** end_ui1_arr, // restart and back : button/text entities
  geEntity** end_ui2_arr, // next level : button/text entities
  geScene* scene
);

void Destroy_UI_Manager_Sub_Entity(geEntity* entity);

#endif
