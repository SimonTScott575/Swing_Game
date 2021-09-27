#ifndef MENU_CAMERA_H
#define MENU_CAMERA_H

#include <Game_Engine/Game_Engine.h>

typedef struct Menu_Camera Menu_Camera;

struct Menu_Camera {

  geEntity* _super;

  mFrame2D* frame;

  grCamera2D* camera2D;

};

Menu_Camera* Create_Menu_Camera(float x_length);

void Destroy_Menu_Camera_Sub_Entity(geEntity* entity);

#endif
