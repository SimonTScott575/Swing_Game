#include "Menu_Camera.h"

#include <string.h>

Menu_Camera* Create_Menu_Camera(float x_length, geScene* scene) {

  Menu_Camera* mc = malloc(sizeof(Menu_Camera));
  if (mc == NULL) { return NULL; }

  geEntity_ctor(&mc->_super);
  geSet_Sub_Entity(mc, Destroy_Menu_Camera_Sub_Entity, &mc->_super);

  mc->frame = mFrame2D_init(mVector2f_ZERO, 0, mVector2f_ONE);

  float inv_ar = geGet_Active_Window()->_Y_pixels/(float)geGet_Active_Window()->_X_pixels;
  grCamera2D_ctor(&mc->camera2D, &mc->frame, x_length, x_length*inv_ar);
  mc->camera2D.background_colour[0] = 52/256.0;
  mc->camera2D.background_colour[1] = 160/256.0;
  mc->camera2D.background_colour[2] = 164/256.0;
  mc->camera2D.background_colour[3] = 1;

  //! component for adjusting projection with aspect ratio needed

  geAdd_Component(&mc->camera2D._super, &mc->_super);

  geAdd_Entity(&mc->_super, scene);

  return mc;

}

void Destroy_Menu_Camera_Sub_Entity(geEntity* entity) {

  Menu_Camera* menu_camera = entity->_sub;

  free(menu_camera);

}
