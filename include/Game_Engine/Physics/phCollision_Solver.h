#ifndef PH_Collision_Solver_H
#define PH_Collision_Solver_H

#include <stdint.h>
#include <stdbool.h>

#include <Game_Engine/Maths/mFrame.h>

#include <Game_Engine/ECS/geComponent.h>
#include <Game_Engine/ECS/geEntity.h>

#include "phCollider.h"
#include "phRigid_Body.h"
#include "phJoint.h"

typedef struct phCollision2D phCollision2D;
typedef struct phCollision_Solver2D phCollision_Solver2D;

typedef uint64_t (*phDetect_Collisions_fn)(phRigid_Body2D* a, phRigid_Body2D* b, phCollision2D* collisions);
typedef bool (*phRay_Cast_fn)(mVector2f position, mVector2f direction, phCollider2D* c, phCollision2D* collisions);

struct phCollision2D {

  phRigid_Body2D* rigid_body1;
  phRigid_Body2D* rigid_body2;

  mVector2f position;
  mVector2f normal;
  float distance;

  mVector2f sep_vel;
  float delta_time;

  float accum_lambda;

};

struct phCollision_Solver2D {

  dLList(phRigid_Body2D_ptr)* _rigid_bodies;
  dLList(phJoint2D_ptr)* _joints;

  phCollision2D _collisions[100];
  uint64_t _collisions_count;

};

// ==========================
// Initialization/Termination
// ==========================

phCollision_Solver2D* new_phCollision_Solver2D();

void del_phCollision_Solver2D(phCollision_Solver2D* cs);

// =================
// Collision Solving
// =================

void phSolve_Collisions(phCollision_Solver2D* cs);

// ===================
// Collision Detection
// ===================

uint64_t phDetect_Collisions(phRigid_Body2D* rb1, phRigid_Body2D* rb2, phCollision2D* collisions);

uint64_t phDetect_Collisions_AABB(phRigid_Body2D* rb1, phRigid_Body2D* rb2, phCollision2D* collisions);
uint64_t phDetect_Collisions_CIRCLE(phRigid_Body2D* rb1, phRigid_Body2D* rb2, phCollision2D* collisions);

uint64_t phDetect_Collisions_AABB_CIRCLE(phRigid_Body2D* rb1, phRigid_Body2D* rb2, phCollision2D* collisions);

// ====================
// Collision Resolution
// ====================

float phGet_Collision_Lambda(phCollision2D collision);

// ===============
// Collision Query
// ===============

bool phRay_Cast_Solver(mVector2f position, mVector2f direction, phCollision2D* collisions, phCollision_Solver2D* cs);

bool phRay_Cast_Solver_Masked(
  mVector2f position,
  mVector2f direction,
  phCollision2D* collisions,
  geComponent_Layer_Mask c_req_lm,
  geEntity_Layer_Mask e_req_lm,
  phCollision_Solver2D* cs
);

bool phRay_Cast_AABB(mVector2f position, mVector2f direction, phCollider2D* c, phCollision2D* collisions);
bool phRay_Cast_Circle(mVector2f position, mVector2f direction, phCollider2D* c, phCollision2D* collisions);

void phSave_Collider_Collisions(phCollider2D* collider, phCollision2D* collisions, uint64_t max_collisions);

#endif
