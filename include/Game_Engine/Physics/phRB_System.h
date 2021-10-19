#ifndef PH_RB_SYSTEM_H
#define PH_RB_SYSTEM_H

#include <stdint.h>
#include <stdbool.h>

#include <Game_Engine/dATUM/dLList.h>

#include <Game_Engine/ECS/geSystem.h>

#include "phCollider.h"
#include "phRigid_Body.h"
#include "phCollision_Solver.h"

typedef
struct phRB_System2D {

  geSystem* _super;

  mVector2f global_force;
  mVector2f gravity;

  phCollision_Solver2D* _cs;

} phRB_System2D;

// ==========================
// Initialization/Termination
// ==========================

phRB_System2D* new_phRB_System2D();

void del_phRB_System2D(phRB_System2D* rb_sys);

// ==========
// Add/Remove
// ==========

void phAdd_Rigid_Body2D(phRigid_Body2D* rb, phRB_System2D* rb_sys);
void phRemove_Rigid_Body2D(phRigid_Body2D* rb, phRB_System2D* rb_sys);

void phAdd_Joint2D(phJoint2D* joint, phRB_System2D* rb_sys);
void phRemove_Joint2D(phJoint2D* joint, phRB_System2D* rb_sys);

// ======
// Forces
// ======

void phZero_RB_System2D(phRB_System2D* system);

void phAdd_Globals_Rigid_Body2D(phRigid_Body2D* rb, phRB_System2D* rb_sys);

void phApply_Joint2Ds(phRB_System2D* rb_sys);

void phUpdate_RB_System2D(phRB_System2D* system);

#endif
