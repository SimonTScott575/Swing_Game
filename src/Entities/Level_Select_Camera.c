#include "Level_Select_Camera.h"

#include <string.h>

Level_Select_Camera* Create_Level_Select_Camera(float x_length) {

  geEntity* entity = geCreate_Entity();

  mFrame2D* frame = new_mFrame2D(mVector2f_ZERO, 0, mVector2f_ONE);

  float inv_ar = geGet_Active_Window()->_Y_pixels/(float)geGet_Active_Window()->_X_pixels;
  grCamera2D* camera2D = grCreate_Camera2D(frame, x_length, inv_ar*x_length);
  camera2D->background_colour[0] = 204/255.0;
  camera2D->background_colour[1] = 88/255.0;
  camera2D->background_colour[2] = 3/255.0;
  camera2D->background_colour[3] = 1;

  Level_Select_Camera_Controller* lscc = Create_Level_Select_Camera_Controller(frame, x_length);

  geAdd_Component(frame->_super, entity);
  geAdd_Component(camera2D->_super, entity);
  geAdd_Component(lscc->_super, entity);

  Level_Select_Camera* lsc = malloc(sizeof(Level_Select_Camera));
  *lsc = (Level_Select_Camera){
    ._super = entity,
    .frame = frame,
    .camera2D = camera2D,
    .lscc = lscc
  };

  geSet_Sub_Entity(lsc, Destroy_Level_Select_Camera_Sub_Entity, entity);

  return lsc;

}

void Destroy_Level_Select_Camera_Sub_Entity(geEntity* entity) {

  Level_Select_Camera* lsc = entity->_sub;

  free(lsc);

}
