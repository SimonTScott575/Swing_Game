#include "Rope_Controller.h"

#include <math.h>

#include "../Layers.h"

void Rope_Controller_ctor(
  Rope_Controller* self,
  mFrame2D* frame, mFrame2D* hook_f,
  grRenderer* renderer, grRenderer* hook_r,
  phRod_Joint2D* rod_j, phSpring_Joint2D* spring_j
) {

  frame->scale.i[0] = 0.1;
  renderer->_super.is_active = false;

  *self = (Rope_Controller){
    .frame = frame,
    .renderer = renderer,
    .hook_f = hook_f,
    .hook_r = hook_r,
    .is_hitting = false,
    .init_rod_phase = false,
    .init_spring_phase = false,
    .rod_phase = false,
    .spring_phase = false,
    .climb_phase = false,
    .rod_j = rod_j,
    .spring_j = spring_j
  };

  geComponent_ctor(&self->_super);
  geSet_Sub_Component(self, Update_Rope_Controller, NULL, &self->_super);

}

void Update_Rope_Controller(geComponent* component) {

  Rope_Controller* rc = component->_sub;

  phRigid_Body2D* source_rb = rc->rod_j->_super.rigid_body1;
  mFrame2D* source_f = source_rb->frame;
  mVector2f source_pos = source_f->position;

  if ( !rc->is_hitting ) {

    if ( glfwGetMouseButton(geGet_Active_Window()->_window_ID, GLFW_MOUSE_BUTTON_1) ) {

      mVector2f mouse_pos;
      double mouse_X;
      double mouse_Y;
      glfwGetCursorPos(geGet_Active_Window()->_window_ID, &mouse_X, &mouse_Y);
      float camera_X_length = rc->camera2D->_X_length;
      float camera_Y_length = camera_X_length * geGet_Active_Window()->_Y_pixels/geGet_Active_Window()->_X_pixels;
      mouse_pos = (mVector2f){{
        camera_X_length * ( mouse_X/geGet_Active_Window()->_X_pixels - 0.5 ),
        camera_Y_length * ( (1 - mouse_Y/geGet_Active_Window()->_Y_pixels) - 0.5 )
      }};
      mouse_pos = mAdd_V2f(rc->camera2D->frame->position, mouse_pos);

      phCollision2D collision;
      rc->is_hitting = phRay_Cast_Solver_Masked(source_f->position, mSub_V2f(mouse_pos, source_pos), &collision, 0, HOOK_SURFACE_LAYER, rc->rb_sys->_cs);
      rc->dest_pos = collision.position;
      rc->dest_rb = (collision.rigid_body1 == source_rb ? collision.rigid_body2 : collision.rigid_body1); //!!!

    }

  } else {

    if ( !glfwGetMouseButton(geGet_Active_Window()->_window_ID, GLFW_MOUSE_BUTTON_1) ) {

      rc->renderer->_super.is_active = false;
      rc->hook_r->_super.is_active = false;

      rc->rod_j->_super._super.is_active = false;
      rc->spring_j->_super._super.is_active = false;

      rc->is_hitting = false;
      rc->init_rod_phase = false;
      rc->init_spring_phase = false;
      rc->rod_phase = false;
      rc->spring_phase = false;

    }

  }

  if ( rc->is_hitting ) {

    // set rope visuals
    mVector2f direction = mSub_V2f(rc->dest_pos, source_pos);
    float direction_norm = mNorm_V2f(direction);
    // if (fabs(direction.i[1]) < 0.001) { goto EXIT_HITTING; }

    mVector2f direction_unit = direction;
    if (!mNormalize_V2f(&direction_unit)) {
      goto EXIT_HITTING;
    }
    mVector2f direction_unit_perp = {{-direction_unit.i[1],direction_unit.i[0]}};

    float length = mNorm_V2f(direction);
    float angle = -atan(direction.i[0]/direction.i[1]);

    rc->frame->rotation = angle;
    rc->frame->scale.i[1] = length;
    rc->frame->position = mAdd_V2f( source_f->position , mMul_f_V2f(0.5, direction) );
    rc->renderer->_super.is_active = true;

    rc->hook_f->position = rc->dest_pos;
    rc->hook_r->_super.is_active = true;

    // set as rod or spring
    rc->init_rod_phase |= !rc->rod_phase && rc->spring_phase && mDot_V2f(source_rb->velocity, direction) >= 0;
    rc->init_spring_phase |= !rc->spring_phase && !rc->rod_phase && mDot_V2f(source_rb->velocity, direction) < 0;

    if ( rc->init_spring_phase ) {

      rc->spring_j->_super._super.is_active = true;

      rc->spring_j->_super.rigid_body1 = source_rb;
      rc->spring_j->_super.rigid_body2 = rc->dest_rb;
      rc->spring_j->_super.position1 = mVector2f_ZERO;
      rc->spring_j->_super.position2 = mInv_Transform_2D(rc->dest_pos,
                                                         *rc->spring_j->_super.rigid_body2->frame);

      rc->spring_j->rest_length = length;

      rc->init_spring_phase = false;
      rc->spring_phase = true;
      rc->rod_phase = false;

    }
    else
    if ( rc->init_rod_phase ) {

      rc->spring_j->_super._super.is_active = false;
      rc->rod_j->_super._super.is_active = true;

      rc->rod_j->_super.rigid_body1 = source_rb;
      rc->rod_j->_super.rigid_body2 = rc->dest_rb;
      rc->rod_j->_super.position1 = mInv_Transform_2D(rc->dest_pos ,
                                                      *rc->rod_j->_super.rigid_body1->frame);
      rc->rod_j->_super.position2 = mInv_Transform_2D(rc->dest_pos ,
                                                      *rc->rod_j->_super.rigid_body2->frame);

      rc->rod_phase = true;
      rc->spring_phase = false;
      rc->init_rod_phase = false;

    }
    else
    if ( direction.i[1] < 0 ) {

      float cos_theta = direction.i[0]/direction_norm;

      if ( fabs(rc->rb_sys->gravity.i[1]*cos_theta) > mNorm_V2f(source_rb->velocity)*mNorm_V2f(source_rb->velocity)/direction_norm ) {

        rc->rod_phase = false;
        rc->spring_phase = false;
        rc->init_rod_phase = false;
        rc->init_spring_phase = false;

        rc->spring_j->_super._super.is_active = false;
        rc->rod_j->_super._super.is_active = false;

      }

    }

    // input
    int climb_sign =   glfwGetKey(geGet_Active_Game()->window->_window_ID, GLFW_KEY_W)
                     - glfwGetKey(geGet_Active_Game()->window->_window_ID, GLFW_KEY_S);

    if ( climb_sign ) {

      rc->rod_j->_super._super.is_active = false;
      if (climb_sign < 0) { rc->spring_j->_super._super.is_active = false; }

      float vel_norm = mNorm_V2f(source_rb->velocity);
      float acc = vel_norm*vel_norm / direction_norm;

      float vel_dot_dir = mDot_V2f(source_rb->velocity, direction_unit);
      mVector2f vel_dir = mMul_f_V2f( vel_dot_dir, direction_unit );
      if (    !(vel_dot_dir >  MAX_ROPE_CLIMB_SPEED && climb_sign > 0)
           && !(vel_dot_dir < -MAX_ROPE_CLIMB_SPEED && climb_sign < 0)
      ) {
        vel_dir = mAdd_V2f(vel_dir, mMul_f_V2f(acc*phDELTA_T + climb_sign*ROPE_CLIMP_ACCELERATION, direction_unit));
      }

      mVector2f vel_dir_n = mMul_f_V2f( mDot_V2f(direction_unit_perp, source_rb->velocity), direction_unit_perp );

      source_rb->velocity = mAdd_V2f(
        vel_dir_n,
        vel_dir
      );

      rc->climb_phase = true;

    } else if (rc->climb_phase) {

      rc->init_rod_phase = rc->init_spring_phase = rc->rod_phase = rc->spring_phase = false;

      rc->climb_phase = false;

    }

  } EXIT_HITTING:

  return;

}
