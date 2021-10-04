#include "Camera_Controller.h"

#include "../Glow.h"

Camera_Controller* Create_Camera_Controller(
  mFrame2D* camera_frame,
  mFrame2D* player_frame,
  float x_length,
  grCamera2D* camera2D
) {

  Camera_Controller* cc = malloc(sizeof(Camera_Controller));

  *cc = (Camera_Controller){
    ._super = geCreate_Component(),
    .frame = camera_frame,
    .player_frame = player_frame,
    .gem_positions = NULL,
    .gems_count = 0,
    .x_length = x_length,
    .camera2D = camera2D
  };

  geSet_Sub_Component(cc, NULL, Destroy_Camera_Controller_Sub_Component, cc->_super);
  grSet_Sub_Camera2D(cc, Prepare_Camera_Sub_Camera2D, camera2D);

  return cc;

}

void Set_Gem_Positions(mVector2f* gem_positions, int gems_count, Camera_Controller* cc) {

  cc->gems_count = gems_count;
  cc->gem_positions = malloc(gems_count*sizeof(mVector2f));

  for (int i = 0; i < gems_count; i++) {
    cc->gem_positions[i] = gem_positions[i];
  }

}

void Prepare_Camera_Sub_Camera2D(grCamera2D* camera2D, grScreen* screen) {

  Camera_Controller* cc = camera2D->_sub;

  float origianl_x = cc->x_length;
  // if (origianl_x == 0) {
  //   origianl_x = cc->rs->camera->_X_length;
  // }

  float ar = (float)geGet_Active_Window()->_Y_pixels/geGet_Active_Window()->_X_pixels;
  float x_length = cc->rs->camera->_X_length;
  float y_length = x_length * ar;
  float min_length = origianl_x;

  if (ar*origianl_x < min_length) {
    grSet_Projection_2D(min_length/ar, min_length, cc->rs->camera);
  } else {
    grSet_Projection_2D(origianl_x, ar * origianl_x, cc->rs->camera);
  }

  cc->frame->position = cc->player_frame->position;

  grPrepare_Camera(camera2D, screen);

  mVector2f screen_pos1 = mAdd_V2f(cc->rs->camera->frame->position, (mVector2f){{-x_length/2,-y_length/2}} );
  mVector2f screen_pos2 = mAdd_V2f(cc->rs->camera->frame->position, (mVector2f){{ x_length/2, y_length/2}} );
  grSet_float2_by_name("screen_pos1", Glow_Shader,  screen_pos1.i[0], screen_pos1.i[1]);
  grSet_float2_by_name("screen_pos2", Glow_Shader,  screen_pos2.i[0], screen_pos2.i[1]);

  if (cc->gems_count > 0) {
    grSet_float2_by_name("gem_pos", Glow_Shader, cc->gem_positions[0].i[0], cc->gem_positions[0].i[1]);
  }

}

void Destroy_Camera_Controller_Sub_Component(geComponent* component) {

  Camera_Controller* cc = component->_sub;

  free(cc->gem_positions);

  free(cc);

}
