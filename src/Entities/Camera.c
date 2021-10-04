#include "Camera.h"

#include <string.h>

Camera* Create_Camera(mFrame2D* player_frame, float x_length) {

  geEntity* entity = geCreate_Entity();

  mFrame2D* frame = new_mFrame2D(mVector2f_ZERO, 0, mVector2f_ONE);

  grCamera2D* camera2D = grCreate_Camera2D(frame, x_length, x_length);
  memcpy(camera2D->background_colour, (float[4]){226/256.0, 113/256.0, 29/256.0, 1}, 4*sizeof(float));

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
