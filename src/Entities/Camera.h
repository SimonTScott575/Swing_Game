#ifndef CAMERA_H
#define CAMERA_H

#include <Game_Engine/Game_Engine.h>

#include "../Components/Camera_Controller.h"

typedef struct Camera Camera;

struct Camera {

  geEntity* _super;

  mFrame2D* frame;

  grCamera2D* camera2D;
  Camera_Controller* cc;

};

Camera* Create_Camera(mFrame2D* player_frame, float x_length);

void Destroy_Camera_Sub_Entity(geEntity* entity);

#endif
