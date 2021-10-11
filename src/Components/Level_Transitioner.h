#ifndef LEVEL_TRANSITIONER_H
#define LEVEL_TRANSITIONER_H

#include <Game_Engine/Game_Engine.h>

#include "Portal_Catcher.h"
#include "Timer_Clock.h"
#include "Player_Controller.h"

#define END_UI1_LENGTH 4
#define END_UI2_LENGTH 2

typedef struct Level_Transitioner Level_Transitioner;

struct Level_Transitioner {

  geComponent* _super;

  Portal_Catcher* pc;
  Timer_Clock* clock;
  Player_Controller* player_controller;

  geEntity* end_ui1_arr[END_UI1_LENGTH];
  geEntity* end_ui2_arr[END_UI2_LENGTH];

  float level_start_time;
  int cd_first_frame;
  int cd_over;

  grText* cd_text;
  grText_Renderer* cd_text_r;

};

Level_Transitioner* Create_Level_Transitioner(
  Portal_Catcher* pc, Timer_Clock* clock, Player_Controller* player_controller,
  grText_Renderer* cd_text_r,
  geEntity** end_ui1_arr, // restart and back : button/text entities
  geEntity** end_ui2_arr // next level : button/text entities
);

void Update_Level_Transitioner(geComponent* component);

void Destroy_Level_Transitioner_Sub_Component(geComponent* component);

void On_Click_Back_Button(geUI_Element* uie);
void On_Click_Restart_Button(geUI_Element* uie);
void On_Click_Next_Level_Button(geUI_Element* uie);

#endif
