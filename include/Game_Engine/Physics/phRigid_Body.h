//TODO: what if phDELTA_T = 0 ?

#ifndef PH_RIGID_BODY_H
#define PH_RIGID_BODY_H

#include <stdbool.h>

#include <Game_Engine/Maths/mVector.h>
#include <Game_Engine/Maths/mFrame.h>

#include <Game_Engine/ECS/geComponent.h>

#include "phCollider.h"

#define phDELTA_T 0.02

typedef struct phRigid_Body2D phRigid_Body2D;

D_HEADER_LLIST(phRigid_Body2D*, phRigid_Body2D_ptr);

typedef
struct phRigid_Body2D {

  geComponent _super;

  dNode_LL(phRigid_Body2D_ptr)* _rb_node;

  mFrame2D* frame;

  mVector2f velocity;
  float angular_velocity;

  float mass;
  float rotational_inertia;

  mVector2f force;
  float torque;

  phCollider2D* collider;

  bool is_kinetic;
  bool is_static;
  bool is_static_rotation;
  bool is_transparent;

  float restitution;

  bool _force_applied; //!TODO: should be with RB_System ?

} phRigid_Body2D;

// =========================
// Initalization/Termination
// =========================

void phRigid_Body2D_ctor(phRigid_Body2D* self, mFrame2D* frame, float mass, float rotational_inertia, phCollider2D* collider);

// ==============
// Set Properties
// ==============

void phSet_Force(mVector2f force, mVector2f position, phRigid_Body2D* rb);

// ============
// Apply Forces
// ============

void phApply_Force_On_Velocity_dt(phRigid_Body2D* rb, float delta_time);
void phApply_Velocity_On_Position_dt(phRigid_Body2D* rb, float delta_time);
void phApply_Force_dt(phRigid_Body2D* rb, float delta_time);

void phApply_Force_On_Velocity(phRigid_Body2D* rb);
void phApply_Velocity_On_Position(phRigid_Body2D* rb);
void phApply_Force(phRigid_Body2D* rb);

#endif
