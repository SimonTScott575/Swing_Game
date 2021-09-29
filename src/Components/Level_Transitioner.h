#ifndef LEVEL_TRANSITIONER_H
#define LEVEL_TRANSITIONER_H

#include <Game_Engine/Game_Engine.h>

#include "Portal_Catcher.h"
#include "Timer_Clock.h"
#include "Player_Controller.h"

typedef struct Level_Transitioner Level_Transitioner;

struct Level_Transitioner {

  geComponent* _super;

  Portal_Catcher* pc;
  Timer_Clock* clock;
  Player_Controller* player_controller;

  grRenderer* back_r;
  geButton_UI* back_b;

  grRenderer* restart_r;
  geButton_UI* restart_b;

  grRenderer* next_level_r;
  geButton_UI* next_level_b;

  grText_Renderer* back_tr;
  grText_Renderer* restart_tr;
  grText_Renderer* next_level_tr;

  float level_start_time;
  int cd_first_frame;
  int cd_over;

  grText* cd_text;
  grText_Renderer* cd_text_r;

};

Level_Transitioner* Create_Level_Transitioner(
  Portal_Catcher* pc, Timer_Clock* clock, Player_Controller* player_controller,
  grText* cd_text,           grText_Renderer* cd_text_r,
  geButton_UI* back_b,       grRenderer* back_r,
  geButton_UI* restart_b,    grRenderer* restart_r,
  geButton_UI* next_level_b, grRenderer* next_level_r,
  grText_Renderer* back_tr, grText_Renderer* restart_tr, grText_Renderer* next_level_tr
);

void Update_Level_Transitioner(geComponent* component);

void Destroy_Level_Transitioner_Sub_Component(geComponent* component);

void On_Click_Back_Button(geUI_Element* uie);
void On_Click_Restart_Button(geUI_Element* uie);
void On_Click_Next_Level_Button(geUI_Element* uie);

#endif
