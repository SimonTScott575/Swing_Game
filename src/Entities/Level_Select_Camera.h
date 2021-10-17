#ifndef LEVEL_SELECT_CAMERA_H
#define LEVEL_SELECT_CAMERA_H

#include <Game_Engine/Game_Engine.h>

#include "../Components/Level_Select_Camera_Controller.h"

typedef struct Level_Select_Camera Level_Select_Camera;

struct Level_Select_Camera {

  geEntity _super;

  mFrame2D frame;

  grCamera2D camera2D;
  Level_Select_Camera_Controller lscc;

};

Level_Select_Camera* Create_Level_Select_Camera(float x_length, geScene* scene);

void Destroy_Level_Select_Camera_Sub_Entity(geEntity* entity);

#endif
