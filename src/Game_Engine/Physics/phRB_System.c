#include <Game_Engine/Physics/phRB_System.h>

//d
#include <stdio.h>

// ======
// static
// ======

static void phUpdate_RB_System2D_void(void* arg) {
  phUpdate_RB_System2D(arg);
}
static void del_phRB_System2D_void(void* arg) {
  del_phRB_System2D(arg);
}

static void phZero_Rigid_Body2D(phRigid_Body2D* rb) {
  rb->force = mVector2f_ZERO;
  rb->torque = 0;
}

// ===
//
// ===

phRB_System2D* new_phRB_System2D() {

  phRB_System2D* result = malloc(sizeof(phRB_System2D));
  *result = (phRB_System2D){
    ._super = geCreate_System(result, phUpdate_RB_System2D_void, del_phRB_System2D_void),
    .global_force = mVector2f_ZERO,
    .gravity = mVector2f_ZERO,
    ._cs = new_phCollision_Solver2D()
  };

  return result;

}

void del_phRB_System2D(phRB_System2D* rb_sys) {

  geDestroy_System(rb_sys->_super);
  del_phCollision_Solver2D(rb_sys->_cs);

  free(rb_sys);

}

// ==========
// Add/Remove
// ==========

void phAdd_Rigid_Body2D(phRigid_Body2D* rb, phRB_System2D* rb_sys) {
  rb->_rb_node = dAppend_LL(phRigid_Body2D_ptr)(rb, rb_sys->_cs->_rigid_bodies);
}

void phRemove_Rigid_Body2D(phRigid_Body2D* rb, phRB_System2D* rb_sys) {
  dRemove_LL(phRigid_Body2D_ptr)(rb->_rb_node, rb_sys->_cs->_rigid_bodies);
}

void phAdd_Joint2D(phJoint2D* joint, phRB_System2D* rb_sys) {
  joint->_joint_node = dAppend_LL(phJoint2D_ptr)(joint, rb_sys->_cs->_joints);
}
void phRemove_Joint2D(phJoint2D* joint, phRB_System2D* rb_sys) {
  dRemove_LL(phJoint2D_ptr)(joint->_joint_node, rb_sys->_cs->_joints);
}

// ===
//
// ===

void phAdd_Globals_RB_System2D(phRB_System2D* rb_sys) {

  dNode_LL(phRigid_Body2D_ptr)* rb_node = rb_sys->_cs->_rigid_bodies->start;

  for ( ; rb_node != NULL; rb_node = rb_node->next ) {

    if (rb_node->element->_super != NULL && !rb_node->element->_super->is_active) { continue; }
    if (rb_node->element->_super != NULL && rb_node->element->_super->_entity != NULL && !rb_node->element->_super->_entity->is_active) { continue; }

    rb_node->element->force = mAdd_V2f( rb_node->element->force, rb_sys->global_force );

    rb_node->element->force = mAdd_V2f( rb_node->element->force, mMul_f_V2f(rb_node->element->mass, rb_sys->gravity) );

  }

}

void phApply_Joint2Ds(phRB_System2D* rb_sys) {

}

void phZero_RB_System2D(phRB_System2D* rb_sys) { //TODO: should use phZero_RB

  dNode_LL(phRigid_Body2D_ptr)* rb_node = rb_sys->_cs->_rigid_bodies->start;

  for ( ; rb_node != NULL ; rb_node = rb_node->next) {

    if (rb_node->element->_super != NULL && !geComponent_Is_Active(rb_node->element->_super)) { continue; }

    rb_node->element->force = mVector2f_ZERO;
    rb_node->element->torque = 0;

  }

}

void phUpdate_RB_System2D(phRB_System2D* rb_sys) { //!!! if current_collision->delta_T < phDLETA_T dont apply collision force

  phAdd_Globals_RB_System2D(rb_sys);

  for (
    dNode_LL(phRigid_Body2D_ptr)* rb_node = rb_sys->_cs->_rigid_bodies->start;
    rb_node != NULL;
    rb_node = rb_node->next
  ) {

    phRigid_Body2D* rb = rb_node->element;

    if (rb->_super != NULL && !geComponent_Is_Active(rb->_super)) {
      continue;
    }

    phApply_Force_On_Velocity(rb);

    // rb->_force_applied = false;

  }

  phSolve_Collisions(rb_sys->_cs);

  for (uint64_t iter_n = 0; iter_n < 1; iter_n++) {
  for (
    dNode_LL(phJoint2D_ptr)* joint_node = rb_sys->_cs->_joints->start;
    joint_node != NULL;
    joint_node = joint_node->next
  ) {

    phJoint2D* joint = joint_node->element;
    phRigid_Body2D* rb1 = joint->rigid_body1;

    if (joint->_super != NULL && !geComponent_Is_Active(joint->_super)) {
      continue;
    }
    if (rb1 == NULL || rb1->_super != NULL && !geComponent_Is_Active(rb1->_super)) {
      continue;
    }

    phApply_Joint2D(joint);

  }
  }

  for (uint64_t iter_n = 0; iter_n < 1; iter_n++) {
  for (uint64_t i = 0; i < rb_sys->_cs->_collisions_count; i++) {

    phCollision2D collision = rb_sys->_cs->_collisions[i];

    phRigid_Body2D* rb1 = collision.rigid_body1;
    phRigid_Body2D* rb2 = collision.rigid_body2;

    if (rb1->is_transparent || rb2->is_transparent) {
      continue;
    }

    // colliding force
    if ( mDot_V2f(collision.sep_vel, collision.normal) < 0 ) {

      // phApply_Velocity_On_Position_dt( rb1, -phDELTA_T );
      // phApply_Velocity_On_Position_dt( rb2, -phDELTA_T );

      // float old_accum = collision.accum_lambda;
      // float new_accum = old_accum + phGet_Collision_Lambda(collision);
      // new_accum = (new_accum > 0 ? new_accum : 0);
      float impulse = phGet_Collision_Lambda(collision); // new_accum - old_accum;
      // rb_sys->_cs->_collisions[i].accum_lambda = new_accum;

      rb1->force = mMul_f_V2f(
        impulse,
        collision.normal
      );
      rb2->force = mMul_f_V2f(
        -impulse,
        collision.normal
      );

      phApply_Force_On_Velocity(rb1);
      phApply_Force_On_Velocity(rb2);

      // rb1->_force_applied = rb2->_force_applied = true;

    }

  }
  }

  for (
    dNode_LL(phRigid_Body2D_ptr)* rb_node = rb_sys->_cs->_rigid_bodies->start;
    rb_node != NULL;
    rb_node = rb_node->next
  ) {

    phRigid_Body2D* rb = rb_node->element;

    if (rb->_super != NULL && !geComponent_Is_Active(rb->_super)) {
      continue;
    }

    phApply_Velocity_On_Position( rb );

  }

  phZero_RB_System2D(rb_sys);

}
