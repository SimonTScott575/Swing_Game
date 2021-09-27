#ifndef LEVEL_SELECT_CAMERA_CONTROLLER_H
#define LEVEL_SELECT_CAMERA_CONTROLLER_H

#include <Game_Engine/Game_Engine.h>

typedef struct Level_Select_Camera_Controller Level_Select_Camera_Controller;

struct Level_Select_Camera_Controller {

  geComponent* _super;

  mFrame2D* frame;
  mVector2f target_position;

  float x_length;

  grRendering_System2D* rs;

};

Level_Select_Camera_Controller* Create_Level_Select_Camera_Controller(mFrame2D* frame, float x_length);
void Update_Level_Select_Camera_Controller(geComponent* component);
void Destroy_Level_Select_Camera_Controller_Sub_Component(geComponent* component);

#endif
