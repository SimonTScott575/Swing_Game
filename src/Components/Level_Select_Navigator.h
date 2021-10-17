#ifndef LEVEL_SELECT_NAVIGATOR_H
#define LEVEL_SELECT_NAVIGATOR_H

#include <Game_Engine/Game_Engine.h>

#include "../Scenes.h"
#include "../Scenes/Level_1.h"
#include "../Scenes/Level_2.h"
#include "../Scenes/Level_3.h"
#include "../Scenes/Level_4.h"
#include "../Scenes/Level_5.h"

#include "../Components/Level_Select_Camera_Controller.h"

typedef struct Level_Select_Navigator Level_Select_Navigator;

struct Level_Select_Navigator {

  geComponent _super;

  geEntity* next_level_e;
  geEntity* prev_level_e;
  geEntity* play_level_e;
  geEntity* play_level_text_e;

  geEntity* locked_e;

  Level_Select_Camera_Controller* lscc;

};

extern Level_Select_Navigator* active_lsn;

void Level_Select_Navigator_ctor(
  Level_Select_Navigator* self,
  geEntity* next_level_e,
  geEntity* prev_level_e,
  geEntity* play_level_e,
  geEntity* play_level_text_e,
  geEntity* locked_e,
  Level_Select_Camera_Controller* lscc
);
void Level_Select_Navigator_Sub_Component_dtor(geComponent* component);

void Update_Level_Select_Navigator_Sub_Component(geComponent* component);

void On_Click_Play_Button(geUI_Element* uie);
void On_Click_End_Game_Button(geUI_Element* uie);
void On_Click_Main_Menu(geUI_Element* uie);
void On_Click_Next_Level(geUI_Element* uie);
void On_Click_Prev_Level(geUI_Element* uie);
void On_Click_Play_Level(geUI_Element* uie);

#endif
