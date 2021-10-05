#ifndef LEVEL_SELECT_NAVIGATOR_H
#define LEVEL_SELECT_NAVIGATOR_H

#include <Game_Engine/Game_Engine.h>

#include "../Components/Level_Select_Camera_Controller.h"

#define L1_OFFSET -9.0f

#define L1_MAX_X_LENGTH ( L1_A*2 + 2*L1_B + L1_C ) // distance level select camera 0 to edge
#define L2_MAX_X_LENGTH L2_TOTAL
#define L3_MAX_X_LENGTH L3_WIDTH

#define L1_MENU_POS L1_OFFSET
#define L2_MENU_POS (L1_MENU_POS + (L1_A*3/2.0 + 2*L1_B + L1_C) + L1_BUFFER + L2_BUFFER + L2_MAX_X_LENGTH/2)
#define L3_MENU_POS (L2_MENU_POS + L2_MAX_X_LENGTH/2            + L2_BUFFER + L3_BUFFER + L3_MAX_X_LENGTH/2)

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
