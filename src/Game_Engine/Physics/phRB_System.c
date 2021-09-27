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

  dNode_LL(phJoint2D_ptr)* joint_node = rb_sys->_cs->_joints->start;

  for ( ; joint_node != NULL; joint_node = joint_node->next) {

    phRigid_Body2D* rb1 = joint_node->element->rigid_body1;
    phRigid_Body2D* rb2 = joint_node->element->rigid_body2;

    if (rb1 != NULL && rb1->_super != NULL && !rb1->_super->is_active) { continue; }
    if (rb1 != NULL && rb1->_super != NULL && rb1->_super->_entity != NULL && !rb1->_super->_entity->is_active) { continue; }
    if (rb2 != NULL && rb2->_super != NULL && !rb2->_super->is_active) { continue; }
    if (rb2 != NULL && rb2->_super != NULL && rb2->_super->_entity != NULL && !rb2->_super->_entity->is_active) { continue; }

    if (!joint_node->element->active) { continue; }
    if (joint_node->element->_super != NULL && !joint_node->element->_super->is_active) { continue; }

    phApply_Joint2D(joint_node->element);

    // if (joint_node->element->active) {
    //   phApply_Joint2D(joint_node->element);
    // }

  }

}

void phZero_RB_System2D(phRB_System2D* rb_sys) { //TODO: should use phZero_RB

  dNode_LL(phRigid_Body2D_ptr)* rb_node = rb_sys->_cs->_rigid_bodies->start;

  for ( ; rb_node != NULL ; rb_node = rb_node->next) {

    if (rb_node->element->_super != NULL && !rb_node->element->_super->is_active) { continue; }
    if (rb_node->element->_super != NULL && rb_node->element->_super->_entity != NULL && !rb_node->element->_super->_entity->is_active) { continue; }

    rb_node->element->force = mVector2f_ZERO;
    rb_node->element->torque = 0;

  }

}

void phUpdate_RB_System2D(phRB_System2D* rb_sys) { //!!! if current_collision->delta_T < phDLETA_T dont apply collision force

  phAdd_Globals_RB_System2D(rb_sys);

  phApply_Joint2Ds(rb_sys);

  dNode_LL(phRigid_Body2D_ptr)* rbA_node = rb_sys->_cs->_rigid_bodies->start;
  if (rbA_node == NULL) { return; }

  for ( ; rbA_node != NULL; rbA_node = rbA_node->next ) {

    if (rbA_node->element->_super != NULL && !rbA_node->element->_super->is_active) { continue; }
    if (rbA_node->element->_super != NULL && rbA_node->element->_super->_entity != NULL && !rbA_node->element->_super->_entity->is_active) { continue; }

    if ( ! rbA_node->element->_force_applied ) {
      phApply_Force(rbA_node->element);
    } else {
      rbA_node->element->_force_applied = false;
    }

  }

  phSolve_Collisions(rb_sys->_cs);

  for (uint64_t i = 0; i < rb_sys->_cs->_collisions_count; i++) {

    phCollision2D collision = rb_sys->_cs->_collisions[i];

    phRigid_Body2D* rb1 = collision.rigid_body1;
    phRigid_Body2D* rb2 = collision.rigid_body2;

    if (rb1->is_transparent || rb2->is_transparent) {
      continue;
    }

    // colliding force
    if ( mDot_V2f(collision.sep_vel, collision.normal) < 0 ) {

      // move to TOI
      rb1->velocity = mMul_f_V2f(-1, rb1->velocity);
      rb2->velocity = mMul_f_V2f(-1, rb2->velocity);
      phApply_Velocity_On_Position_dt( rb1, collision.delta_time ); //!!!??? some error slack ?
      phApply_Velocity_On_Position_dt( rb2, collision.delta_time ); //!!!??? some error slack ?
      rb1->velocity = mMul_f_V2f(-1, rb1->velocity);
      rb2->velocity = mMul_f_V2f(-1, rb2->velocity);

      // apply force
      mVector2f force = mMul_f_V2f(
        phGet_Collision_Lambda(collision),
        collision.normal
      );

      rb1->force = force ;
      rb2->force = mMul_f_V2f(-1, force);

      phApply_Force(rb1);
      phApply_Force(rb2);

    }

  }

  phZero_RB_System2D(rb_sys);

}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

/*

void phUpdate_RB_System2D(phRB_System2D* rb_sys) { //!!! if current_collision->delta_T < phDLETA_T dont apply collision force

  phAdd_Globals_RB_System2D(rb_sys);

  dLListRB2D_Node* rbA_node = rb_sys->_cs->_rigid_bodies->start;
  if (rbA_node == NULL) { return; }

  while (rbA_node != NULL) {

    // if (rbA_node->element->_is_resting) {
    //
    //   float f_dot_rn = mDot_V2f(rbA_node->element->force, rbA_node->element->_resting_normal);
    //   if ( f_dot_rn > 0 || rbA_node->element->_resting_f_dot_rn < f_dot_rn - 0.1 ) {
    //     //rbA_node->element->_is_resting = false;
    //   }
    //
    // }


    if ( ! rbA_node->element->_is_resting ) {

      phApply_Force(rbA_node->element);

    }

    rbA_node = rbA_node->next;

  }

  phSolve_Collisions(rb_sys->_cs);

  for (uint64_t i = 0; i < rb_sys->_cs->_collisions_count; i++) {

    phCollision2D collision = rb_sys->_cs->_collisions[i];

    phRigid_Body2D* rb1 = collision.rigid_body1;
    phRigid_Body2D* rb2 = collision.rigid_body2;

    mVector2f f1_dir = collision.normal;
    mVector2f f2_dir = mMul_f_V2f(-1,collision.normal);

    // colliding force
    if ( mDot_V2f(collision.sep_vel, collision.normal) < 0 ) {

      // move to TOI
      rb1->velocity = mMul_f_V2f(-1, rb1->velocity);
      rb2->velocity = mMul_f_V2f(-1, rb2->velocity);
      phApply_Velocity_On_Position_dt( rb1, collision.delta_time ); //!!!??? some error slack ?
      phApply_Velocity_On_Position_dt( rb2, collision.delta_time ); //!!!??? some error slack ?
      rb1->velocity = mMul_f_V2f(-1, rb1->velocity);
      rb2->velocity = mMul_f_V2f(-1, rb2->velocity);

      // // set _is_resting
      // if ( mNorm_V2f(rb1->velocity) < 0.1 ) {
      //   rb1->_is_resting = true;
      //   rb1->velocity = mVector2f_ZERO;
      //   rb1->_resting_normal = collision.normal;
      //   rb1->_resting_f_dot_rn = mDot_V2f(rb1->force, collision.normal);
      // }
      // if ( mNorm_V2f(rb2->velocity) < 0.1 ) {
      //   rb2->_is_resting = true;
      //   rb2->velocity = mVector2f_ZERO;
      //   rb2->_resting_normal = mMul_f_V2f(-1,collision.normal);
      //   rb2->_resting_f_dot_rn = mDot_V2f(rb2->force, mMul_f_V2f(-1,collision.normal));
      // }

      if ( !rb1->_is_resting || !rb2->_is_resting ) {

        // apply force
        mVector2f force = mMul_f_V2f(
          phGet_Collision_Lambda(collision),
          collision.normal
        );

        // float f1_dot_n = mDot_V2f(rb1->force,f1_dir); //? should better apply ext force with collision force but causes problems
        // f1_dot_n = (f1_dot_n < 0 ? f1_dot_n : 0);
        // rb1->force = mAdd_V2f(rb1->force, mMul_f_V2f(f1_dot_n,f1_dir));
        // float f2_dot_n = mDot_V2f(rb2->force,f2_dir);
        // f2_dot_n = (f2_dot_n < 0 ? f2_dot_n : 0);
        // rb2->force = mAdd_V2f(rb2->force, mMul_f_V2f(f2_dot_n,f2_dir));
        //
        // rb1->force = mAdd_V2f( rb1->force, force );
        // rb2->force = mAdd_V2f( rb2->force, mMul_f_V2f(-1, force) );

        rb1->force = force ;
        rb2->force = mMul_f_V2f(-1, force);

        phApply_Force(rb1);
        phApply_Force(rb2);

        // mVector2f fp_correction = mMul_f_V2f(-0.1*collision.distance, collision.normal);
        // rb1->frame->position = mAdd_V2f( rb1->frame->position, fp_correction );
        // rb2->frame->position = mAdd_V2f( rb2->frame->position, mMul_f_V2f(-1,fp_correction) );

      }

    }

  }

  phZero_RB_System2D(rb_sys);

}

*/
