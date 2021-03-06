#include <Game_Engine/Physics/phRigid_Body.h>

//d
#include <stdio.h>

#include <math.h>

D_SOURCE_dLList(phRigid_Body2D*, phRigid_Body2D_ptr);

// =========================
// Initalization/Termination
// =========================

void phRigid_Body2D_ctor(phRigid_Body2D* self, mFrame2D* frame, float mass, float rotational_inertia, phCollider2D* collider) {

  *self = (phRigid_Body2D){

    .frame = frame,

    .velocity = mVector2f_ZERO,
    .angular_velocity = 0,

    .mass = mass,
    .rotational_inertia = rotational_inertia,

    .force = mVector2f_ZERO,
    .torque = 0,

    .collider = collider,

    .is_kinetic = true,
    .is_static = false,
    .is_static_rotation = (collider->_collider_ID == PH_AABB_COLLIDER) ? true : false, //? more general/safe way better
    .is_transparent = false,

    .restitution = 1,

    ._force_applied = false

  };

  geComponent_ctor(&self->_super);
  geSet_Sub_Component(self, NULL, NULL, &self->_super);

}

// ==============
// Set properties
// ==============

void phSet_Force(mVector2f force, mVector2f position, phRigid_Body2D* rb) {
  rb->force = force;

  mVector2f r = mSub_V2f(position, rb->frame->position);
  float r_cross_f = r.i[0]*force.i[1] - r.i[1]*force.i[0];

  rb->torque = r_cross_f;
}

// ============
// Apply Forces
// ============

void phApply_Force_On_Velocity_dt(phRigid_Body2D* rb, float delta_time) {
  if (rb->is_kinetic) {
    if (!rb->is_static) {
      rb->velocity = mAdd_V2f( rb->velocity, mMul_f_V2f( phDELTA_T / rb->mass, rb->force ) );
    }
    if (!rb->is_static_rotation) {
      rb->angular_velocity += phDELTA_T/rb->rotational_inertia * rb->torque;
    }
  }
}
void phApply_Velocity_On_Position_dt(phRigid_Body2D* rb, float delta_time) {
  if (!rb->is_static) {
    rb->frame->position = mAdd_V2f( rb->frame->position, mMul_f_V2f( delta_time, rb->velocity ) );
  }
  if (!rb->is_static_rotation) {
    rb->frame->rotation += delta_time * rb->angular_velocity;
  }
}
void phApply_Force_dt(phRigid_Body2D* rb, float delta_time) {
  phApply_Force_On_Velocity_dt(rb, delta_time);
  phApply_Velocity_On_Position_dt(rb, delta_time);
}

void phApply_Force_On_Velocity(phRigid_Body2D* rb) {
  phApply_Force_On_Velocity_dt(rb, phDELTA_T);
}
void phApply_Velocity_On_Position(phRigid_Body2D* rb) {
  phApply_Velocity_On_Position_dt(rb, phDELTA_T);
}
void phApply_Force(phRigid_Body2D* rb) {
  phApply_Force_dt(rb, phDELTA_T);
}
