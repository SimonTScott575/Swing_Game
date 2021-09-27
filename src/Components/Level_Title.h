#ifndef LEVEL_TITLE_H
#define LEVEL_TITLE_H

#include <Game_Engine/Game_Engine.h>

typedef
struct Level_Title {

  geComponent* _super;

  float x;
  grText_Renderer* text_r;

} Level_Title;

Level_Title* Create_Level_Title(float x, grText_Renderer* text_r);
void Update_Level_Title(geComponent* component);
void Destroy_Level_Title_Sub_Component(geComponent* component);

#endif
