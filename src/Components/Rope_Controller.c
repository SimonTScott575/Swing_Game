#include "Rope_Controller.h"

#include <math.h>

#include "../Layers.h"

Rope_Controller* Create_Rope_Controller(mFrame2D* frame, grRenderer* renderer, phRod_Joint2D* rod_j, phSpring_Joint2D* spring_j) {

  Rope_Controller* rc = malloc(sizeof(Rope_Controller));

  frame->scale.i[0] = 0.1;
  renderer->_super->is_active = false;

  *rc = (Rope_Controller){
    .frame = frame,
    .renderer = renderer,
    .is_hitting = false,
    .rod_phase = false,
    .spring_phase = false,
    .rod_j = rod_j,
    .spring_j = spring_j
  };

  rc->_super = geCreate_Component();
  geSet_Sub_Component(rc, Update_Rope_Controller, Destroy_Rope_Controller_Sub_Component, rc->_super);

  return rc;

}

void Update_Rope_Controller(geComponent* component) {

  Rope_Controller* rc = component->_sub;

  phRigid_Body2D* source_rb = rc->rod_j->_super.rigid_body1;
  mFrame2D* source_f = source_rb->frame;
  mVector2f source_pos = source_f->position;

  bool start_rod_phase = false;
  bool start_spring_phase = false;

  int climb_sign =   glfwGetKey(geGet_Active_Game()->window->_window_ID, GLFW_KEY_W)
                   - glfwGetKey(geGet_Active_Game()->window->_window_ID, GLFW_KEY_S);

  mVector2f r = mSub_V2f(rc->dest_pos,source_rb->frame->position);
  float r_norm = mNorm_V2f(r);
  r = mMul_f_V2f(1/r_norm, r);

  if ( rc->is_hitting && !glfwGetMouseButton(geGet_Active_Window()->_window_ID, GLFW_MOUSE_BUTTON_1) ) {

    source_rb->angular_velocity = 0; //?
    if ( climb_sign ) {
      source_rb->velocity = mMul_f_V2f(1/phDELTA_T/2,rc->delta_pos);
    }

    rc->is_hitting = false;

    rc->renderer->_super->is_active = false;
    rc->rod_phase = false;
    rc->spring_phase = false;
    rc->rod_j->_super._super->is_active = false;
    rc->spring_j->_super._super->is_active = false;
    rc->dest_rb = NULL;

  }

  if (    rc->is_hitting
       && climb_sign
  ) {

    if (r_norm < 1.5 && climb_sign > 0) {
      rc->r_v = 0;
      rc->delta_pos = mVector2f_ZERO;
      goto EXIT_CLIMBING;
    }

    rc->r_v += ( (-0.1 < rc->r_v || rc->r_v < 0.1) ? climb_sign*0.01 : 0 );
    r = mMul_f_V2f(rc->r_v,r);

    mVector2f temp = rc->prev_pos;
    rc->prev_pos = source_rb->frame->position;
    source_rb->frame->position = mAdd_V2f(source_rb->frame->position, r); // somehow acceleratory ?
    rc->delta_pos = mSub_V2f(source_rb->frame->position, temp);

    source_pos = source_rb->frame->position;

    if ( rc->rod_phase ) {
      rc->rod_j->_super.position1 = mInv_Transform_2D(rc->dest_pos ,
                                                      *rc->rod_j->_super.rigid_body1->frame);
    }
    else
    if ( rc->spring_phase ) {
      // rc->spring_j->rest_length += rc->r_v; //! move towards velocity !
      start_rod_phase = true;
    }

  } else {

    rc->r_v = 0; // mDot_V2f(r, source_rb->velocity);
    rc->delta_pos = mVector2f_ZERO;

  } EXIT_CLIMBING:

  if ( !rc->is_hitting ) {

    mVector2f mouse_pos;

    phCollision2D collision;

    if ( glfwGetMouseButton(geGet_Active_Window()->_window_ID, GLFW_MOUSE_BUTTON_1) ) {

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

      source_pos = source_f->position;

      rc->is_hitting = phRay_Cast_Solver_Masked(source_f->position, mSub_V2f(mouse_pos, source_pos), &collision, 0, HOOK_SURFACE_LAYER, rc->rb_sys->_cs);
      rc->dest_pos = collision.position;
      rc->dest_rb = (collision.rigid_body1 == source_rb ? collision.rigid_body2 : collision.rigid_body1); //!!!

    }

  }

  if ( rc->is_hitting ) {

    mVector2f direction = mSub_V2f(rc->dest_pos, source_pos);
    if (fabs(direction.i[1]) < 0.001) { goto EXIT_HITTING; };

    float length = mNorm_V2f(direction);
    float angle = -atan(direction.i[0]/direction.i[1]);

    rc->frame->rotation = angle;
    rc->frame->scale.i[1] = length;
    rc->frame->position = mAdd_V2f( source_f->position , mMul_f_V2f(0.5, direction) );
    rc->renderer->_super->is_active = true;

    start_rod_phase |= (rc->spring_phase && mDot_V2f(source_rb->velocity, direction) > 0);
    start_spring_phase |= !rc->spring_phase && !rc->rod_phase;

    if (   !rc->rod_phase
        && !rc->spring_phase
        && mDot_V2f(source_rb->velocity, direction) > 0) {
      //???
    } else if (start_rod_phase) {

      rc->rod_j->_super.rigid_body2 = rc->dest_rb;
      rc->rod_j->_super.position1 = mInv_Transform_2D(rc->dest_pos ,
                                                      *rc->rod_j->_super.rigid_body1->frame);
      rc->rod_j->_super.position2 = mInv_Transform_2D(rc->dest_pos ,
                                                      *rc->rod_j->_super.rigid_body2->frame);

      rc->rod_phase = true;
      rc->spring_phase = false;

      rc->spring_j->_super._super->is_active = false;
      rc->rod_j->_super._super->is_active = true;

    } else if (start_spring_phase) {

      rc->spring_j->_super.rigid_body2 = rc->dest_rb;
      rc->spring_j->_super.position1 = mVector2f_ZERO;
      rc->spring_j->_super.position2 = mInv_Transform_2D(rc->dest_pos,
                                                         *rc->spring_j->_super.rigid_body2->frame);

      rc->spring_j->rest_length = length;

      rc->spring_j->_super._super->is_active = true;
      rc->rod_j->_super._super->is_active = false;

      rc->spring_phase = true;
      rc->rod_phase = false;

    }

  } EXIT_HITTING:

  return;

}

void Destroy_Rope_Controller_Sub_Component(geComponent* component) {

  Rope_Controller* rc = component->_sub;

  free(rc);

}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

// void Update_Rope_Controller(void* arg) {
//
//   Rope_Controller* rc = arg;
//
//   phRigid_Body2D* source_rb = rc->rod_j->_super.rigid_body1;
//   mFrame2D* source_f = source_rb->frame;
//   mVector2f source_pos = source_f->position;
//
//   if ( rc->is_hitting && !glfwGetMouseButton(geGet_Active_Window()->_window_ID, GLFW_MOUSE_BUTTON_1) ) {
//
//     rc->is_hitting = false;
//
//     rc->renderer->_super->is_active = false;
//     rc->rod_phase = false;
//     rc->rod_j->_super._super->is_active = false;
//     rc->spring_j->_super._super->is_active = false;
//
//   }
//
//   if ( !rc->is_hitting ) {
//
//     mVector2f mouse_pos;
//
//     phCollision2D collision;
//
//     if ( glfwGetMouseButton(geGet_Active_Window()->_window_ID, GLFW_MOUSE_BUTTON_1) ) {
//
//       double mouse_X;
//       double mouse_Y;
//       glfwGetCursorPos(geGet_Active_Window()->_window_ID, &mouse_X, &mouse_Y);
//       float camera_X_length = rc->camera2D->_X_length;
//       float camera_Y_length = camera_X_length * geGet_Active_Window()->_Y_pixels/geGet_Active_Window()->_X_pixels;
//       mouse_pos = (mVector2f){{
//         camera_X_length * ( mouse_X/geGet_Active_Window()->_X_pixels - 0.5 ),
//         camera_Y_length * ( (1 - mouse_Y/geGet_Active_Window()->_Y_pixels) - 0.5 )
//       }};
//       mouse_pos = mAdd_V2f(rc->camera2D->frame->position, mouse_pos);
//
//       source_pos = source_f->position;
//
//       rc->is_hitting = phRay_Cast_Solver_Masked(source_f->position, mSub_V2f(mouse_pos, source_pos), &collision, 0, GEM_LAYER, rc->rb_sys->_cs);
//       rc->dest_pos = collision.position;
//
//       rc->spring_j->rest_length = mNorm_V2f(mSub_V2f(rc->dest_pos,source_pos));
//
//     }
//
//   }
//
//   if ( rc->is_hitting ) {
//
//     mVector2f direction = mSub_V2f(rc->dest_pos, source_pos);
//     if (fabs(direction.i[1]) < 0.001) { goto exit_hitting; };
//
//     float length = mNorm_V2f(direction);
//     float angle = -atan(direction.i[0]/direction.i[1]);
//
//     rc->frame->rotation = angle;
//     rc->frame->scale.i[1] = length;
//     rc->frame->position = mAdd_V2f( source_f->position , mMul_f_V2f(0.5, direction) );
//
//     if (mDot_V2f(source_rb->velocity, direction) > 0) {
//
//       rc->rod_j->_super.position2 = rc->dest_pos;
//       rc->rod_j->length = length;
//
//       rc->rod_phase = true;
//       rc->spring_j->_super._super->is_active = false;
//       rc->rod_j->_super._super->is_active = true;
//
//     } else if (!rc->rod_phase) {
//
//       rc->spring_j->_super.position2 = rc->dest_pos;
//
//       rc->spring_j->_super._super->is_active = true;
//       rc->rod_j->_super._super->is_active = false;
//
//     }
//
//     rc->renderer->_super->is_active = true;
//     rc->is_hitting = true;
//
//   } exit_hitting:
//
//   return;
//
// }
