#include "Camera.h"

#include <string.h>

Camera* Create_Camera(mFrame2D* player_frame, float x_length, geScene* scene) {

  Camera* camera = malloc(sizeof(Camera));

  camera->_super = geEntity_ctor(&camera->_super);
  geSet_Sub_Entity(camera, Destroy_Camera_Sub_Entity, &camera->_super);

  camera->frame = mFrame2D_init(mVector2f_ZERO, 0, mVector2f_ONE);

  grCamera2D_ctor(&camera->camera2D, &camera->frame, x_length, x_length);
  memcpy(camera->camera2D.background_colour,
         (float[4]){255/255.0,178/255.0,65/255.0,1},// 255/255.0, 182/255.0, 39/255.0, 1}, // 226/255.0, 113/255.0, 29/255.0, 1
         4*sizeof(float));

  Camera_Controller_ctor(&camera->cc, &camera->frame, player_frame, x_length, &camera->camera2D);

  geAdd_Component(&camera->camera2D._super, &camera->_super);
  geAdd_Component(&camera->cc._super, &camera->_super);

  geAdd_Entity(&camera->_super, scene);

  return camera;

}

void Destroy_Camera_Sub_Entity(geEntity* entity) {

  Camera* c = entity->_sub;

  free(c);

}
