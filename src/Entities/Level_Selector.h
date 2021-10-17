#ifndef LEVEL_SELECTOR_H
#define LEVEL_SELECTOR_H

#include <Game_Engine/Game_Engine.h>

#include "../Components/Level_Select_Navigator.h"

typedef struct Level_Selector Level_Selector;

struct Level_Selector {

  geEntity _super;

  Level_Select_Navigator lsn;

};

Level_Selector* Create_Level_Selector(
  geEntity* next_level_e,
  geEntity* prev_level_e,
  geEntity* play_level_e,
  geEntity* play_level_text_e,
  geEntity* locked_e,
  Level_Select_Camera_Controller* lscc,
  geScene* scene
);

void Destroy_Level_Selector_Sub_Entity(geEntity* entity);

#endif
