#ifndef LEVEL_TITLE_H
#define LEVEL_TITLE_H

#include <Game_Engine/Game_Engine.h>

typedef
struct Level_Title {

  geComponent _super;

  float x;
  grText_Renderer* text_r;

} Level_Title;

void Level_Title_ctor(Level_Title* self, float x, grText_Renderer* text_r);
Level_Title* Level_Title_new(float x, grText_Renderer* text_r);
void Level_Title_Sub_Component_del(geComponent* component);

void Update_Level_Title(geComponent* component);

#endif
