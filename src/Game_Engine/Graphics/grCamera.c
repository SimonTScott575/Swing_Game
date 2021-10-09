#include <Game_Engine/Graphics/grCamera.h>

#include <stdlib.h>
#include <string.h>
#include <math.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

// ====================
// Creation/Destruction
// ====================

grCamera2D* grCreate_Camera2D(mFrame2D* frame, float width, float height) { //TODO: ??? should set update via set frame ??? ?

  grCamera2D* camera = malloc(sizeof(grCamera2D));
  camera->frame = frame;
  camera->_X_length = 2;
  camera->_sub = NULL;
  camera->_prepare = grPrepare_Camera;
  memcpy(camera->background_colour, (float[4]){0,0,0,1}, 4*sizeof(float));

  camera->_super = geCreate_Component();
  geSet_Sub_Component(camera, NULL, grDestroy_Camera2D_Sub_Component, camera->_super);

  if (frame != NULL) {
    grSet_View_2D(frame, camera);
  }
  grSet_Projection_2D(width, height, camera);

  return camera;

}

void grDestroy_Camera2D_Sub_Component(geComponent* component) {

  grCamera2D* camera = component->_sub;

  free(camera);
}

void grSet_Sub_Camera2D(void* sub, grPrepare_Camera_fn prepare, grCamera2D* camera) {
  camera->_sub = sub;
  camera->_prepare = prepare;
}

// ===================
// View and Projection
// ===================

void grSet_View_2D(mFrame2D* frame, grCamera2D* camera) {

  mGenerate_transform_2D(frame);

  float inv_rot = -frame->rotation;
  float inv_posX = -frame->position.i[0];
  float inv_posY = -frame->position.i[1];

  camera->View3x3.i[0][0] =  cos(inv_rot);
  camera->View3x3.i[0][1] = -sin(inv_rot);
  camera->View3x3.i[1][0] =  sin(inv_rot);
  camera->View3x3.i[1][1] =  cos(inv_rot);

  camera->View3x3.i[0][2] =  cos(inv_rot)*inv_posX - sin(inv_rot)*inv_posY;
  camera->View3x3.i[1][2] =  sin(inv_rot)*inv_posX + cos(inv_rot)*inv_posY;

  camera->View3x3.i[2][0] = camera->View3x3.i[2][1] = 0;
  camera->View3x3.i[2][2] = 1;

}

void grSet_Projection_2D(float width, float height, grCamera2D* camera) {
  camera->_X_length = width;

  camera->Projection3x3.i[0][0] = 2/width;
  camera->Projection3x3.i[0][1] = camera->Projection3x3.i[0][2] = 0;

  camera->Projection3x3.i[1][0] = camera->Projection3x3.i[1][2] = 0;
  camera->Projection3x3.i[1][1] = 2/height;

  camera->Projection3x3.i[2][0] = camera->Projection3x3.i[2][1] = 0;
  camera->Projection3x3.i[2][2] = 1;
}

// ======
// Update
// ======

void grPrepare_Camera(grCamera2D* camera, grScreen* screen) {

  grSet_View_2D(camera->frame, camera);
  grSet_Clear_Screen_Colour(camera->background_colour, screen);
  if (camera->background_colour[3] != 0) {
    grClear_Screen(screen);
  }

}
