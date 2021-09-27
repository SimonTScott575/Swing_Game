#include "Menu_Camera.h"

#include <string.h>

Menu_Camera* Create_Menu_Camera(float x_length) {

  geEntity* entity = geCreate_Entity();

  mFrame2D* frame = new_mFrame2D(mVector2f_ZERO, 0, mVector2f_ONE);

  float inv_ar = geGet_Active_Window()->_Y_pixels/(float)geGet_Active_Window()->_X_pixels;
  grCamera2D* camera2D = grCreate_Camera2D(frame, x_length, x_length*inv_ar);
  camera2D->background_colour[0] = 52/256.0;
  camera2D->background_colour[1] = 160/256.0;
  camera2D->background_colour[2] = 164/256.0;
  camera2D->background_colour[3] = 1;

  //! component for adjusting projection with aspect ratio needed

  geAdd_Component(frame->_super, entity);
  geAdd_Component(camera2D->_super, entity);

  Menu_Camera* lsc = malloc(sizeof(Menu_Camera));
  *lsc = (Menu_Camera){
    ._super = entity,
    .frame = frame,
    .camera2D = camera2D
  };

  geSet_Sub_Entity(lsc, Destroy_Menu_Camera_Sub_Entity, entity);

  return lsc;

}

void Destroy_Menu_Camera_Sub_Entity(geEntity* entity) {

  Menu_Camera* menu_camera = entity->_sub;

  free(menu_camera);

}
