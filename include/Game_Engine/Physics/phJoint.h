#ifndef PH_JOINT_H
#define PH_JOINT_H

#include <stdbool.h>

#include <Game_Engine/ECS/geComponent.h>
#include <Game_Engine/ECS/geEntity.h>

#include "phRigid_Body.h"

typedef struct phJoint2D phJoint2D;

typedef void (*phApply_Joint2D_fn)(phJoint2D* joint);

D_HEADER_LLIST(phJoint2D*, phJoint2D_ptr);

typedef
struct phJoint2D {

  geComponent _super;

  bool active;
  dNode_LL(phJoint2D_ptr)* _joint_node;

  phRigid_Body2D* rigid_body1;
  mVector2f position1;
  phRigid_Body2D* rigid_body2;
  mVector2f position2;

  void* _sub;
  phApply_Joint2D_fn _apply_joint;

} phJoint2D;

typedef
struct phSpring_Joint2D {

  phJoint2D _super;

  float k;
  float rest_length;

} phSpring_Joint2D;
typedef
struct phRod_Joint2D {

  phJoint2D _super;

  float radial_velocity;
  bool _is_radial_motion;

} phRod_Joint2D;

// ==========================
// Initialization/Termination
// ==========================

//IMPORTANT: rb1 MUST NOT be NULL, rb2 MUST be NULL

void phJoint2D_ctor(phJoint2D* self, mVector2f position1, phRigid_Body2D* rb1, mVector2f position2, phRigid_Body2D* rb2);

void phSpring_Joint2D_ctor(
  phSpring_Joint2D* self,
  float k, float rest_length,
  mVector2f position1, phRigid_Body2D* rb1,
  mVector2f position2, phRigid_Body2D* rb2
);
void phRod_Joint2D_ctor(
  phRod_Joint2D* self,
  float length,
  mVector2f position1, phRigid_Body2D* rb1,
  mVector2f position2, phRigid_Body2D* rb2
);

void phSet_Sub_Joint2D(void* sub, phApply_Joint2D_fn apply, phJoint2D* joint);

// =====
// Apply
// =====

void phApply_Joint2D(phJoint2D* joint);

void phApply_Spring_Joint2D(phJoint2D* joint);
void phApply_Rod_Joint2D(phJoint2D* joint);


#endif
