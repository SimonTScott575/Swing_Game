#ifndef CAMERA_CONTROLLER_H
#define CAMERA_CONTROLLER_H

#include <Game_Engine/Game_Engine.h>

typedef struct Camera_Controller Camera_Controller;

struct Camera_Controller {

  geComponent* _super;

  mFrame2D* frame;

  mFrame2D* player_frame;

  float x_length;

  grRendering_System2D* rs;
  grCamera2D* camera2D;

};

Camera_Controller* Create_Camera_Controller(
  mFrame2D* camera_frame,
  mFrame2D* player_frame,
  float x_length,
  grCamera2D* camera2D
);

// void Set_Gem_Positions(mVector2f* gem_positions, int gems_count, Camera_Controller* cc);

void Prepare_Camera_Sub_Camera2D(grCamera2D* camera2D, grScreen* screen);

void Destroy_Camera_Controller_Sub_Component(geComponent* component);

#endif
