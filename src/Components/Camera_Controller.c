#include "Camera_Controller.h"

#include "../Glow.h"
#include "Gem_Controller.h"
#include "Portal_Catcher.h"

void Camera_Controller_ctor(
  Camera_Controller* self,
  mFrame2D* camera_frame,
  mFrame2D* player_frame,
  float x_length,
  grCamera2D* camera2D
) {

  *self = (Camera_Controller){
    .frame = camera_frame,
    .player_frame = player_frame,
    .x_length = x_length,
    .camera2D = camera2D
  };

  geComponent_ctor(&self->_super);

  geSet_Sub_Component(self, NULL, NULL, &self->_super);
  grSet_Sub_Camera2D(self, Prepare_Camera_Sub_Camera2D, camera2D);

}

void Prepare_Camera_Sub_Camera2D(grCamera2D* camera2D, grScreen* screen) {

  Camera_Controller* cc = camera2D->_sub;

  // Adjust for screen size changes
  float origianl_x = cc->x_length;

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

  // Render renderers
  grPrepare_Camera(camera2D, screen);

  // Glow PP
  mVector2f screen_pos1 = mAdd_V2f(cc->rs->camera->frame->position, (mVector2f){{-x_length/2,-y_length/2}} );
  mVector2f screen_pos2 = mAdd_V2f(cc->rs->camera->frame->position, (mVector2f){{ x_length/2, y_length/2}} );
  grSet_float2_by_name("screen_pos1", Glow_Shader,  screen_pos1.i[0], screen_pos1.i[1]);
  grSet_float2_by_name("screen_pos2", Glow_Shader,  screen_pos2.i[0], screen_pos2.i[1]);

  grSet_int_by_name("gem_count", Glow_Shader, g_gems_count);
  if (g_gems_count > 0) {
    grSet_float2v_by_name("gem_positions", Glow_Shader, (float*)g_gem_positions, g_gems_count); // g_gems_count); g_gem_positions[0].i
    grSet_intv_by_name("gems_is_caught", Glow_Shader, g_gems_is_caught, g_gems_count);
  }

  grSet_float2_by_name("portal_position", Glow_Shader, g_portal_pos.i[0], g_portal_pos.i[1]);
  grSet_int_by_name("portal_is_lit", Glow_Shader, g_gems_caught_count >= g_gems_count);
  grSet_int_by_name("portal_catches_player", Glow_Shader, g_portal_catches_player);
  grSet_float_by_name("portal_catch_time", Glow_Shader, g_portal_catch_time);
  grSet_float_by_name("current_time", Glow_Shader, geGet_Active_Game()->time);

}
