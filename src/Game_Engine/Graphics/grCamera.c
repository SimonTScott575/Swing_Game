#include <Game_Engine/Graphics/grCamera.h>

#include <stdlib.h>
#include <string.h>
#include <math.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

// ====================
// Creation/Destruction
// ====================

void grCamera2D_ctor(grCamera2D* self, mFrame2D* frame, float width, float height) { //TODO: ??? should set update via set frame ??? ?

  self->frame = frame;
  self->_X_length = 2;
  self->_sub = NULL;
  self->_prepare = grPrepare_Camera;
  memcpy(self->background_colour, (float[4]){0,0,0,1}, 4*sizeof(float));

  geComponent_ctor(&self->_super);
  geSet_Sub_Component(self, NULL, NULL, &self->_super);

  if (frame != NULL) {
    grSet_View_2D(frame, self);
  }
  grSet_Projection_2D(width, height, self);

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
