#include <Game_Engine/Graphics/Defaults/grCamera.h>

#include <stdlib.h>
#include <string.h>
#include <math.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

//

// static void grDestroy_Camera2D_void(void* arg) {
//   grDestroy_Camera2D(arg);
// }
// static void grDestroy_Camera3D_void(void* arg) {
//   grDestroy_Camera3D(arg);
// }

// ====================
// Creation/Destruction
// ====================

grCamera2D* grCreate_Camera2D(mFrame2D* frame, float width, float height) { //TODO: ??? should set update via set frame ??? ?

  grCamera2D* camera = malloc(sizeof(grCamera2D));
  camera->frame = frame;
  camera->_X_length = 2;
  memcpy(camera->background_colour, (float[4]){0,0,0,1}, 4*sizeof(float));

  camera->_super = geCreate_Component();
  geSet_Sub_Component(camera, NULL, grDestroy_Camera2D_Sub_Component, camera->_super);

  if (frame != NULL) {
    grSet_View_2D(frame, camera);
  }
  grSet_Projection_2D(width, height, camera);

  return camera;

}
// grCamera3D* grCreate_Camera3D(mFrame3D* frame, float width, float height, float near_dist, float far_dist) { //TODO: ??? should set update via set frame ??? ?
//
//   grCamera3D* camera = malloc(sizeof(grCamera3D));
//   camera->frame = frame;
//   memcpy(camera->background_colour, (float[4]){0,0,0,1}, 4*sizeof(float));
//
//   camera->_super = geCreate_Component(camera, NULL, grDestroy_Camera3D_void);
//
//   grSet_View_3D(frame, camera);
//   grSet_Projection_3D(width, height, near_dist, far_dist, false, camera);
//
//   return camera;
//
// }

// void grDestroy_Camera2D(grCamera2D* camera) {
//
//   geDestroy_Component(camera->_super);
//
//   free(camera);
// }
// void grDestroy_Camera3D(grCamera3D* camera) {
//
//   geDestroy_Component(camera->_super);
//
//   free(camera);
// }
void grDestroy_Camera2D_Sub_Component(geComponent* component) {

  grCamera2D* camera = component->_sub;

  free(camera);
}

// ====
// View
// ====

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
// void grSet_View_3D(mFrame3D* frame, grCamera3D* camera) {
//
//   mGenerate_transform_3D(frame);
//
//   mQuaternion inv_q = mInv_Q(frame->quaternion);
//   mQuaternion_to_Matrix4f_RONLY(inv_q, &camera->View4x4);
//
//   // Translation
//   float inv_posX = - frame->position.i[0];
//   float inv_posY = - frame->position.i[1];
//   float inv_posZ = - frame->position.i[2];
//   camera->View4x4.i[0][3] =  camera->View4x4.i[0][0]*inv_posX + camera->View4x4.i[0][1]*inv_posY + camera->View4x4.i[0][2]*inv_posZ;
//   camera->View4x4.i[1][3] =  camera->View4x4.i[1][0]*inv_posX + camera->View4x4.i[1][1]*inv_posY + camera->View4x4.i[1][2]*inv_posZ;
//   camera->View4x4.i[2][3] =  camera->View4x4.i[2][0]*inv_posX + camera->View4x4.i[2][1]*inv_posY + camera->View4x4.i[2][2]*inv_posZ;
//
//   camera->View4x4.i[3][0] = 0;
//   camera->View4x4.i[3][1] = 0;
//   camera->View4x4.i[3][2] = 0;
//   camera->View4x4.i[3][3] = 1;
//
// }

// ==========
// Projection
// ==========

void grSet_Projection_2D(float width, float height, grCamera2D* camera) {
  camera->_X_length = width;

  camera->Projection3x3.i[0][0] = 2/width;
  camera->Projection3x3.i[0][1] = camera->Projection3x3.i[0][2] = 0;

  camera->Projection3x3.i[1][0] = camera->Projection3x3.i[1][2] = 0;
  camera->Projection3x3.i[1][1] = 2/height;

  camera->Projection3x3.i[2][0] = camera->Projection3x3.i[2][1] = 0;
  camera->Projection3x3.i[2][2] = 1;
}
// void grSet_Projection_3D(float width, float height, float near_dist, float far_dist, bool as_orthographic, grCamera3D* camera) {
//   if (as_orthographic) {
//     camera->Projection4x4.i[0][0] = 2/width;
//     camera->Projection4x4.i[0][1] = 0;
//     camera->Projection4x4.i[0][2] = 0;
//     camera->Projection4x4.i[0][3] = 0;
//
//     camera->Projection4x4.i[1][0] = 0;
//     camera->Projection4x4.i[1][1] = 2/height;
//     camera->Projection4x4.i[1][2] = 0;
//     camera->Projection4x4.i[1][3] = 0;
//
//     camera->Projection4x4.i[2][0] = 0;
//     camera->Projection4x4.i[2][1] = 0;
//     camera->Projection4x4.i[2][2] = -2 / (far_dist - near_dist);
//     camera->Projection4x4.i[2][3] = - (far_dist + near_dist) / (far_dist - near_dist);
//
//     camera->Projection4x4.i[3][0] = 0;
//     camera->Projection4x4.i[3][1] = 0;
//     camera->Projection4x4.i[3][2] = 0;
//     camera->Projection4x4.i[3][3] = 1;
//   } else {
//     camera->Projection4x4.i[0][0] = near_dist * 2/width;
//     camera->Projection4x4.i[0][1] = 0;
//     camera->Projection4x4.i[0][2] = 0;
//     camera->Projection4x4.i[0][3] = 0;
//
//     camera->Projection4x4.i[1][0] = 0;
//     camera->Projection4x4.i[1][1] = near_dist * 2/height;
//     camera->Projection4x4.i[1][2] = 0;
//     camera->Projection4x4.i[1][3] = 0;
//
//     camera->Projection4x4.i[2][0] = 0;
//     camera->Projection4x4.i[2][1] = 0;
//     camera->Projection4x4.i[2][2] = - (far_dist + near_dist) / (far_dist - near_dist);
//     camera->Projection4x4.i[2][3] = - 2 * far_dist * near_dist / (far_dist - near_dist);
//
//     camera->Projection4x4.i[3][0] = 0;
//     camera->Projection4x4.i[3][1] = 0;
//     camera->Projection4x4.i[3][2] = -1;
//     camera->Projection4x4.i[3][3] = 0;
//   }
// }
