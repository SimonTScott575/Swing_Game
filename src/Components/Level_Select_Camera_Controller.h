#ifndef LEVEL_SELECT_CAMERA_CONTROLLER_H
#define LEVEL_SELECT_CAMERA_CONTROLLER_H

#include <Game_Engine/Game_Engine.h>

typedef struct Level_Select_Camera_Controller Level_Select_Camera_Controller;

struct Level_Select_Camera_Controller {

  geComponent _super;

  mFrame2D* frame;
  mVector2f target_position;
  float target_x_length;

  float x_length; //TODO: target_x_length instead with smooth transition

  grRendering_System2D* rs;

};

void Level_Select_Camera_Controller_ctor(
  Level_Select_Camera_Controller* self,
  mFrame2D* frame,
  float x_length
);
void Update_Level_Select_Camera_Controller(geComponent* component);

#endif
