#ifndef LEVEL_SELECT_NAVIGATOR_H
#define LEVEL_SELECT_NAVIGATOR_H

#include <Game_Engine/Game_Engine.h>

#include "../Components/Level_Select_Camera_Controller.h"

typedef struct Level_Select_Navigator Level_Select_Navigator;

struct Level_Select_Navigator {

  geComponent* _super;

  grRenderer* next_level_r;
  geButton_UI* next_level_b;
  grRenderer* prev_level_r;
  geButton_UI* prev_level_b;

  Level_Select_Camera_Controller* lscc;

};

extern Level_Select_Navigator* active_lsn;

Level_Select_Navigator* Create_Level_Select_Navigator(
  geButton_UI* next_level_b, grRenderer* next_level_r,
  geButton_UI* prev_level_b, grRenderer* prev_level_r,
  Level_Select_Camera_Controller* lscc
);
void Destroy_Level_Select_Navigator_Sub_Component(geComponent* component);

void On_Click_Play_Button(geUI_Element* uie);
void On_Click_End_Game_Button(geUI_Element* uie);
void On_Click_Main_Menu(geUI_Element* uie);
void On_Click_Next_Level(geUI_Element* uie);
void On_Click_Prev_Level(geUI_Element* uie);
void On_Click_Play_Level(geUI_Element* uie);

#endif
