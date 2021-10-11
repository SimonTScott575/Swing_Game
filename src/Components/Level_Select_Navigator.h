#ifndef LEVEL_SELECT_NAVIGATOR_H
#define LEVEL_SELECT_NAVIGATOR_H

#include <Game_Engine/Game_Engine.h>

#include "../Scenes.h"
#include "../Scenes/Level_1.h"
#include "../Scenes/Level_2.h"
#include "../Scenes/Level_3.h"
#include "../Scenes/Level_4.h"
#include "../Scenes/Level_5.h"
#include "../Scenes/Level_1_Surfaces_Build.h"

#include "../Components/Level_Select_Camera_Controller.h"

#define L1_OFFSET -9.0f

#define L1_MAX_X_LENGTH ( L1_A*2 + 2*L1_B + L1_C ) // distance level select camera 0 to edge
#define L2_MAX_X_LENGTH L2_TOTAL
#define L3_MAX_X_LENGTH L3_WIDTH
#define L4_MAX_X_LENGTH L4_TOTAL
#define L5_MAX_X_LENGTH L5_TOTAL

#define L1_MENU_POS L1_OFFSET
#define L2_MENU_POS (L1_MENU_POS + (L1_A*3/2.0 + 2*L1_B + L1_C) + L1_BUFFER + L2_BUFFER + L2_MAX_X_LENGTH/2)
#define L3_MENU_POS (L2_MENU_POS + L2_MAX_X_LENGTH/2            + L2_BUFFER + L3_BUFFER + L3_MAX_X_LENGTH/2)
#define L4_MENU_POS (L3_MENU_POS + L3_MAX_X_LENGTH/2            + L3_BUFFER + L4_BUFFER + L4_MAX_X_LENGTH/2)
#define L5_MENU_POS (L4_MENU_POS + L4_MAX_X_LENGTH/2            + L4_BUFFER + L5_BUFFER + L5_MAX_X_LENGTH/2)

typedef struct Level_Select_Navigator Level_Select_Navigator;

struct Level_Select_Navigator {

  geComponent* _super;

  geEntity* next_level_e;
  geEntity* prev_level_e;
  geEntity* play_level_e;

  geEntity* locked_e;

  Level_Select_Camera_Controller* lscc;

};

extern Level_Select_Navigator* active_lsn;

Level_Select_Navigator* Create_Level_Select_Navigator(
  geEntity* next_level_e,
  geEntity* prev_level_e,
  geEntity* play_level_e,
  geEntity* locked_e,
  Level_Select_Camera_Controller* lscc
);
void Update_Level_Select_Navigator_Sub_Component(geComponent* component);
void Destroy_Level_Select_Navigator_Sub_Component(geComponent* component);

void On_Click_Play_Button(geUI_Element* uie);
void On_Click_End_Game_Button(geUI_Element* uie);
void On_Click_Main_Menu(geUI_Element* uie);
void On_Click_Next_Level(geUI_Element* uie);
void On_Click_Prev_Level(geUI_Element* uie);
void On_Click_Play_Level(geUI_Element* uie);

#endif
