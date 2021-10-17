#include <Game_Engine/Physics/phJoint.h>

#include <stdlib.h>

D_SOURCE_LLIST(phJoint2D*, phJoint2D_ptr);

// ==============
// Initialization
// ==============

void phJoint2D_ctor(phJoint2D* self, mVector2f position1, phRigid_Body2D* rb1, mVector2f position2, phRigid_Body2D* rb2) {

    *self = (phJoint2D){

      .active = true,
      ._joint_node = NULL,

      .rigid_body1 = rb1,
      .position1 = position1,
      .rigid_body2 = rb2,
      .position2 = position2,

      ._sub = NULL

    };

    geComponent_ctor(&self->_super);
    geSet_Sub_Component(self, NULL, NULL, &self->_super);

}

void phSet_Sub_Joint2D(void* sub, phApply_Joint2D_fn apply_fn, phJoint2D* joint) {
  joint->_sub = sub;
  joint->_apply_joint = apply_fn;
}

void phSpring_Joint2D_ctor(
  phSpring_Joint2D* self,
  float k, float rest_length,
  mVector2f position1, phRigid_Body2D* rb1,
  mVector2f position2, phRigid_Body2D* rb2
) {

  self->k = k;
  self->rest_length = rest_length;

  phJoint2D_ctor(&self->_super, position1, rb1, position2, rb2);
  phSet_Sub_Joint2D(self, phApply_Spring_Joint2D, &self->_super);

}

void phRod_Joint2D_ctor(
  phRod_Joint2D* self,
  float length,
  mVector2f position1, phRigid_Body2D* rb1,
  mVector2f position2, phRigid_Body2D* rb2
) {

  self->radial_velocity = 0;
  self->_is_radial_motion = false;

  phJoint2D_ctor(&self->_super, position1, rb1, position2, rb2);
  phSet_Sub_Joint2D(self, phApply_Rod_Joint2D, &self->_super);

}

// =====
// Apply
// =====

void phApply_Joint2D(phJoint2D* joint) {
  if (!geComponent_Is_Active(&joint->_super)) {
    return;
  }

  if (joint->_apply_joint != NULL) {
    joint->_apply_joint(joint);
  }
}

#include <stdio.h> //DEBUG
void phApply_Spring_Joint2D(phJoint2D* joint) {

  phSpring_Joint2D* spring = joint->_sub;
  phRigid_Body2D* rb1 = joint->rigid_body1;
  phRigid_Body2D* rb2 = joint->rigid_body2;

  mGenerate_transform_2D(rb1->frame);
  mGenerate_transform_2D(rb2->frame);
  mVector2f pos1_world = mTransform_2D(joint->position1, rb1->frame->transform);
  mVector2f pos2_world = mTransform_2D(joint->position2, rb2->frame->transform);

  mVector2f pos12 = mSub_V2f(pos1_world, pos2_world);
  float distance = mNorm_V2f(pos12);

  if (distance > 0.001) {

    mVector2f force = mMul_f_V2f( - spring->k * (distance - spring->rest_length)/distance , pos12 );
    rb1->force = mAdd_V2f(rb1->force, force);

  }

  phApply_Force_On_Velocity(rb1);

}

void phApply_Rod_Joint2D(phJoint2D* joint) {
  //TODO: allow position1 to not be at centre of rb1 (more complicated than you think, rewrite!)

  phRod_Joint2D* rod = joint->_sub;
  phRigid_Body2D* rb1 = joint->rigid_body1;
  phRigid_Body2D* rb2 = joint->rigid_body2;

  mVector2f r1 = mTransform_RS_2D(joint->position1, *rb1->frame); // local -> world CoM to joint position
  mVector2f r2 = mTransform_RS_2D(joint->position2, *rb2->frame); // local -> world CoM to joint position
  mVector2f r1_perp = {{r1.i[1],-r1.i[0]}};

  // relative/delta velocity
  float rot_vel = rb1->angular_velocity; // mDot_V2f(rb1->velocity,r1); // rb1->angular_velocity;
  mVector2f rot_vel_cross_r1 = {{-rot_vel*r1.i[1], rot_vel*r1.i[0]}};
  mVector2f delta_vel = mAdd_V2f(rb1->velocity,rot_vel_cross_r1);

  // K matrix
  float mass_factor = 1/rb1->mass;
  mMatrix2f K = {.i={
    {mass_factor + r1.i[1]*r1.i[1]/rb1->rotational_inertia,             - r1.i[0]*r1.i[1]/rb1->rotational_inertia},
    {            - r1.i[1]*r1.i[0]/rb1->rotational_inertia, mass_factor + r1.i[0]*r1.i[0]/rb1->rotational_inertia}
  }};

  // invert
  float det = K.i[0][0]*K.i[1][1] - K.i[1][0]*K.i[0][1];
  if (det < 0.001) {
    printf("DET == 0\n");
    return;
  }
  float a = K.i[0][0];
  K.i[0][0]  =  1/det * K.i[1][1];
  K.i[1][1]  =  1/det * a;
  K.i[1][0] *= -1/det;
  K.i[0][1] *= -1/det;

  // bias
  mVector2f bias = mAdd_V2f(rb1->frame->position, r1);
  bias = mSub_V2f(bias, mAdd_V2f(rb2->frame->position, r2));
  bias = mMul_f_V2f(-0.05/phDELTA_T, bias); //DEBUG

  // impulse
  mVector2f impulse = mMul_M2f_V2f( K, mAdd_V2f( mMul_f_V2f(-1,delta_vel) , bias ) );

  // apply
  phSet_Force(mMul_f_V2f(1/phDELTA_T,impulse), mAdd_V2f(rb1->frame->position,r1), rb1);
  phApply_Force_On_Velocity(rb1);

}
