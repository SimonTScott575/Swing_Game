#include "Camera.h"

#include <string.h>

Camera* Create_Camera(mFrame2D* player_frame, float x_length) {

  geEntity* entity = geCreate_Entity();

  mFrame2D* frame = new_mFrame2D(mVector2f_ZERO, 0, mVector2f_ONE);

  grCamera2D* camera2D = grCreate_Camera2D(frame, x_length, x_length);
  memcpy(camera2D->background_colour,
         (float[4]){255/255.0,178/255.0,65/255.0,1},// 255/255.0, 182/255.0, 39/255.0, 1}, // 226/255.0, 113/255.0, 29/255.0, 1
         4*sizeof(float));

  Camera_Controller* cc = Create_Camera_Controller(frame, player_frame, x_length, camera2D);

  Camera* camera = malloc(sizeof(Camera));
  *camera = (Camera){
    ._super = entity,
    .frame = frame,
    .camera2D = camera2D,
    .cc = cc
  };

  geAdd_Component(frame->_super, entity);
  geAdd_Component(camera2D->_super, entity);
  geAdd_Component(cc->_super, entity);

  geSet_Sub_Entity(camera, Destroy_Camera_Sub_Entity, entity);

  return camera;

}

void Destroy_Camera_Sub_Entity(geEntity* entity) {

  Camera* c = entity->_sub;

  free(c);

}
