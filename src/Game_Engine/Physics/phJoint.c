#include <Game_Engine/Physics/phJoint.h>

#include <stdlib.h>

D_SOURCE_dLList(phJoint2D*, phJoint2D_ptr);

// ======
// static
// ======

// static void del_phJoint2D_void(void* arg) {
//   del_phJoint2D(arg);
// }

// ==============
// Initialization
// ==============

phJoint2D init_phJoint2D(mVector2f position1, phRigid_Body2D* rb1, mVector2f position2, phRigid_Body2D* rb2, phApply_Joint2D_fn apply_fn) {
    return (phJoint2D){

      ._super = NULL,

      .active = true,
      ._joint_node = NULL,

      .rigid_body1 = rb1,
      .position1 = position1,
      .rigid_body2 = rb2,
      .position2 = position2,

      ._sub = NULL,
      ._apply_joint = apply_fn

    };
}

void phSet_Sub_Joint2D(void* sub, phJoint2D* joint) {
  joint->_sub = sub;
}

phSpring_Joint2D* new_phSpring_Joint2D(float k, float rest_length, mVector2f position1, phRigid_Body2D* rb1, mVector2f position2, phRigid_Body2D* rb2) {

  phSpring_Joint2D* spring = malloc(sizeof(phSpring_Joint2D));
  spring->k = k;
  spring->rest_length = rest_length;

  spring->_super = init_phJoint2D(position1, rb1, position2, rb2, phApply_Spring_Joint2D);
  phSet_Sub_Joint2D(spring, &spring->_super);

  spring->_super._super = geCreate_Component();
  geSet_Sub_Component(&spring->_super, NULL, del_phJoint2D_Sub_Component, spring->_super._super);

  return spring;

}

phRod_Joint2D* new_phRod_Joint2D(float length, mVector2f position1, phRigid_Body2D* rb1, mVector2f position2, phRigid_Body2D* rb2) {

  phRod_Joint2D* rod = malloc(sizeof(phRod_Joint2D));
  rod->length = length;

  rod->_super = init_phJoint2D(position1, rb1, position2, rb2, phApply_Rod_Joint2D);
  phSet_Sub_Joint2D(rod, &rod->_super);

  rod->_super._super = geCreate_Component();
  geSet_Sub_Component(&rod->_super, NULL, del_phJoint2D_Sub_Component, rod->_super._super);

  return rod;

}

// void del_phJoint2D(phJoint2D* joint) {
//
//   geDestroy_Component(joint->_super);
//   free(joint->_sub);
//
// }

void del_phJoint2D_Sub_Component(geComponent* component) {

  phJoint2D* joint = component->_sub;

  free(joint->_sub);

}

// =====
// Apply
// =====

void phApply_Joint2D(phJoint2D* joint) {
  if (joint->_apply_joint != NULL) {
    joint->_apply_joint(joint);
  }
}

void phApply_Spring_Joint2D(phJoint2D* joint) {

  phRigid_Body2D* rb1 = joint->rigid_body1;
  phRigid_Body2D* rb2 = joint->rigid_body2;

  mVector2f pos1_transformed = joint->position1;
  mVector2f pos2_transformed = joint->position2;
  if (rb1 != NULL) {
    mGenerate_transform_2D(rb1->frame);
    mVector3f pos1_transformed3 = mMul_M3f_V3f(rb1->frame->transform, (mVector3f){{joint->position1.i[0],joint->position1.i[1],1}});
    pos1_transformed = (mVector2f){{pos1_transformed3.i[0],pos1_transformed3.i[1]}};
  }
  if (rb2 != NULL) {
    mGenerate_transform_2D(rb2->frame);
    mVector3f pos2_transformed3 = mMul_M3f_V3f(rb2->frame->transform, (mVector3f){{joint->position2.i[0],joint->position2.i[1],1}});
    pos2_transformed = (mVector2f){{pos2_transformed3.i[0],pos2_transformed3.i[1]}};
  }

  phSpring_Joint2D* spring = joint->_sub;

  mVector2f pos12 = mSub_V2f(pos1_transformed, pos2_transformed);
  float distance = mNorm_V2f(pos12);

  if (distance > 0.001) {

    mVector2f force = mMul_f_V2f( - spring->k * (distance - spring->rest_length)/distance , pos12 );

    if (rb1 != NULL) {
      phSet_Force( mAdd_V2f( rb1->force, force ), pos1_transformed, joint->rigid_body1);
    }
    if (rb2 != NULL) {
      phSet_Force( mAdd_V2f( rb2->force, mMul_f_V2f(-1, force) ), pos2_transformed, joint->rigid_body2);
    }

    // rb1->force = mAdd_V2f( rb1->force, force );
    // rb2->force = mAdd_V2f( rb2->force, mMul_f_V2f(-1, force) );

  }

  if (rb1 != NULL) { phApply_Force(rb1); rb1->_force_applied = true; }
  if (rb2 != NULL) { phApply_Force(rb2); rb2->_force_applied = true; }

}

void phApply_Rod_Joint2D(phJoint2D* joint) {
  //TODO: allow rb2 to not be static
  //TODO: allow position1 to not be at centre of rb1

  phRod_Joint2D* rod = joint->_sub;

  phRigid_Body2D* rb1 = joint->rigid_body1;
  phRigid_Body2D* rb2 = joint->rigid_body2;

  mVector2f pos1_world = joint->position1;
  mVector2f pos2_world = joint->position2;
  if (rb1 != NULL) {
    mGenerate_transform_2D(rb1->frame);
    mVector3f pos1_transformed3 = mMul_M3f_V3f(rb1->frame->transform, (mVector3f){{joint->position1.i[0],joint->position1.i[1],1}});
    pos1_world = (mVector2f){{pos1_transformed3.i[0],pos1_transformed3.i[1]}};
  }
  if (rb2 != NULL) {
    mGenerate_transform_2D(rb2->frame);
    mVector3f pos2_transformed3 = mMul_M3f_V3f(rb2->frame->transform, (mVector3f){{joint->position2.i[0],joint->position2.i[1],1}});
    pos2_world = (mVector2f){{pos2_transformed3.i[0],pos2_transformed3.i[1]}};
  }

  mVector2f rel_pos = mSub_V2f(pos1_world, pos2_world);
  float rel_pos_norm = mNorm_V2f(rel_pos);

  if ( rel_pos_norm > 0.001 && rod->length > 0.001 ) {

    mVector2f direction = mMul_f_V2f(1/rel_pos_norm, rel_pos);

    // move if not at length apart
    if (rel_pos_norm < rod->length - 0.01 || rel_pos_norm > rod->length + 0.01) {

      int n_static = (int) (rb1 == NULL || rb1->is_static) + (int) (rb2 == NULL || rb2->is_static);
      if (n_static > 0) {

        mVector2f correction = mMul_f_V2f( (rod->length - rel_pos_norm)/(2-n_static), direction);

        if (rb1 != NULL && !rb1->is_static) {
          rb1->frame->position = mAdd_V2f(rb1->frame->position, correction);
        }
        if (rb2 != NULL && !rb2->is_static) {
          rb2->frame->position = mAdd_V2f(rb2->frame->position, mMul_f_V2f(-1,correction));
        }

      }

      //!!! duplicated, should do quicker
      if (rb1 != NULL) {
        mGenerate_transform_2D(rb1->frame);
        mVector3f pos1_transformed3 = mMul_M3f_V3f(rb1->frame->transform, (mVector3f){{joint->position1.i[0],joint->position1.i[1],1}});
        pos1_world = (mVector2f){{pos1_transformed3.i[0],pos1_transformed3.i[1]}};
      }
      if (rb2 != NULL) {
        mGenerate_transform_2D(rb2->frame);
        mVector3f pos2_transformed3 = mMul_M3f_V3f(rb2->frame->transform, (mVector3f){{joint->position2.i[0],joint->position2.i[1],1}});
        pos2_world = (mVector2f){{pos2_transformed3.i[0],pos2_transformed3.i[1]}};
      }

      rel_pos = mSub_V2f(pos1_world, pos2_world);

    }

    //NOTE: (see TODO) here now ONLY allowing position1 at rb1 centre and only applying forces to rb1
    if ( rb1 != NULL && !rb1->is_static ) {

      // kinematics
      mVector2f direction_perp = (mVector2f){{-direction.i[1],direction.i[0]}};

      // float angle1 = asin( -direction.i[0] );
      float angular_vel1 = mDot_V2f(rb1->velocity, direction_perp) / rod->length;
      //... 2

      // apply forces
      float force1_perp = mDot_V2f(rb1->force, direction_perp);
      //... force2

      angular_vel1 += force1_perp * phDELTA_T / rod->length;
      float delta_angle = angular_vel1 * phDELTA_T;

      mMatrix2f rot_mat = (mMatrix2f){ .i = {
        {cos(delta_angle), -sin(delta_angle)},
        {sin(delta_angle),  cos(delta_angle)}
      }};
      rb1->frame->position = mAdd_V2f( pos2_world , mMul_M2f_V2f(rot_mat, rel_pos) );
      //... 2

      mVector2f final_velocity = mMul_f_V2f(rod->length * delta_angle/phDELTA_T, direction_perp);

      rb1->force = mMul_f_V2f( 1/phDELTA_T, mSub_V2f(final_velocity, rb1->velocity) );
      rb1->velocity = final_velocity; //!!! MUST account for dT = 0, here and elsewhere

    }

  }

  // phApply_Force(rb1);
  // phApply_Force(rb2);

  if (rb1 != NULL) { rb1->_force_applied = true; }
  if (rb2 != NULL) { rb2->_force_applied = true; }

}
