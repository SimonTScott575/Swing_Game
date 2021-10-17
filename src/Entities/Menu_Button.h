#ifndef MENU_BUTTON_H
#define MENU_BUTTON_H

#include <Game_Engine/Game_Engine.h>

typedef struct Menu_Button Menu_Button;

struct Menu_Button {

  geEntity _super;

  mFrame2D frame;

  grSprite* sprite;
  // grRenderer* renderer;
  geUI_Renderer* ui_r;

  geButton_UI button_ui;

};

Menu_Button* Create_Menu_Button(
  float x, float y,
  float x_offset, float y_offset,
  float width, float height,
  char* texture_path,
  geOn_Click_fn on_click,
  geScene* scene
);

void Destroy_Menu_Button_Sub_Entity(geEntity* entity);

#endif
