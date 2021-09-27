#include "Level_Select_Camera_Controller.h"

#include "../Scenes.h"

Level_Select_Camera_Controller* Create_Level_Select_Camera_Controller(mFrame2D* frame, float x_length) {

  Level_Select_Camera_Controller* lscc = malloc(sizeof(Level_Select_Camera_Controller));

  *lscc = (Level_Select_Camera_Controller){

    .frame = frame,
    .target_position = mVector2f_ZERO,
    .x_length = x_length,
    .rs = NULL

  };

  lscc->_super = geCreate_Component();
  geSet_Sub_Component(lscc, Update_Level_Select_Camera_Controller, Destroy_Level_Select_Camera_Controller_Sub_Component, lscc->_super);

  return lscc;

}

void Update_Level_Select_Camera_Controller(geComponent* component) {

  Level_Select_Camera_Controller* lscc = component->_sub;

  //TODO: camera projection shouldn't be set every frame prefferably
  float origianl_x = lscc->x_length;
  float ar = (float)geGet_Active_Window()->_Y_pixels/geGet_Active_Window()->_X_pixels;
  float x_length = lscc->rs->camera->_X_length;
  float y_length = x_length * ar;
  float min_length = origianl_x;

  if (ar*origianl_x < min_length) {
    grSet_Projection_2D(min_length/ar, min_length, lscc->rs->camera);
  } else {
    grSet_Projection_2D(origianl_x, ar * origianl_x, lscc->rs->camera);
  }

  lscc->frame->position = lscc->target_position; // (mVector2f){{focused_level_num*60,0}};

}

void Destroy_Level_Select_Camera_Controller_Sub_Component(geComponent* component) {

  Level_Select_Camera_Controller* lscc = component->_sub;

  free(lscc);

}
