#include "Level_Select_Camera.h"

#include <string.h>

Level_Select_Camera* Create_Level_Select_Camera(float x_length, geScene* scene) {

  Level_Select_Camera* lsc = malloc(sizeof(Level_Select_Camera));
  if (lsc == NULL) { return NULL; }

  geEntity_ctor(&lsc->_super);
  geSet_Sub_Entity(lsc, Destroy_Level_Select_Camera_Sub_Entity, &lsc->_super);

  lsc->frame = mFrame2D_init(mVector2f_ZERO, 0, mVector2f_ONE);

  float inv_ar = geGet_Active_Window()->_Y_pixels/(float)geGet_Active_Window()->_X_pixels;
  grCamera2D_ctor(&lsc->camera2D, &lsc->frame, x_length, inv_ar*x_length);
  memcpy(lsc->camera2D.background_colour,
         (float[4]){255/255.0,178/255.0,65/255.0,1},// 255/255.0, 182/255.0, 39/255.0, 1}, // 226/255.0, 113/255.0, 29/255.0, 1
         4*sizeof(float));

  Level_Select_Camera_Controller_ctor(&lsc->lscc, &lsc->frame, x_length);

  geAdd_Component(&lsc->camera2D._super, &lsc->_super);
  geAdd_Component(&lsc->lscc._super, &lsc->_super);

  geAdd_Entity(&lsc->_super, scene);

  return lsc;

}

void Destroy_Level_Select_Camera_Sub_Entity(geEntity* entity) {

  Level_Select_Camera* lsc = entity->_sub;

  free(lsc);

}
