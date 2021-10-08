#ifndef LEVEL_SELECTOR_H
#define LEVEL_SELECTOR_H

#include <Game_Engine/Game_Engine.h>

#include "../Components/Level_Select_Navigator.h"

typedef struct Level_Selector Level_Selector;

struct Level_Selector {

  geEntity* _super;

  Level_Select_Navigator* lsn;

};

Level_Selector* Create_Level_Selector(
  geButton_UI* next_level_b, grRenderer* next_level_r,
  geButton_UI* prev_level_b, grRenderer* prev_level_r,
  geButton_UI* play_level_b, grText_Renderer* play_level_tr,
  grText_Renderer* locked_tr,
  Level_Select_Camera_Controller* lscc
);

void Destroy_Level_Selector_Sub_Entity(geEntity* entity);

#endif
