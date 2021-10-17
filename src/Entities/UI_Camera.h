#ifndef UI_CAMERA_H
#define UI_CAMERA_H

#include <Game_Engine/Game_Engine.h>

typedef struct UI_Camera UI_Camera;

struct UI_Camera {

  geEntity _super;

  mFrame2D frame;

  grCamera2D camera;

};

UI_Camera* Create_UI_Camera(geScene* scene);

void Destroy_UI_Camera_Sub_Entity(geEntity* entity);

#endif
