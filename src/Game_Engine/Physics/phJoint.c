#include <Game_Engine/Physics/phJoint.h>

#include <stdlib.h>

D_SOURCE_LLIST(phJoint2D*, phJoint2D_ptr);

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

void del_phJoint2D_Sub_Component(geComponent* component) {

  phJoint2D* joint = component->_sub;

  free(joint->_sub);

}

// =====
// Apply
// =====

void phApply_Joint2D(phJoint2D* joint) {
  if (joint->_super != NULL && !geComponent_Is_Active(joint->_super)) {
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
  // return;
  // printf("YES\n");

  phRod_Joint2D* rod = joint->_sub;
  phRigid_Body2D* rb1 = joint->rigid_body1;
  phRigid_Body2D* rb2 = joint->rigid_body2;

  mGenerate_transform_2D(rb1->frame);
  mGenerate_transform_2D(rb2->frame);
  mVector2f r1 = mTransform_RS_2D(joint->position1, *rb1->frame); // local -> world -> CoM to joint position in world
  mVector2f r2 = mTransform_RS_2D(joint->position2, *rb2->frame); // local -> world -> CoM to joint position in world

  // relative/delta velocity
  mVector2f r1_perp = {{r1.i[1],-r1.i[0]}};
  float rot_vel = rb1->angular_velocity; // mDot_V2f(rb1->velocity,r1); // rb1->angular_velocity;
  mVector2f rot_vel_cross_r1 = {{-rot_vel*r1.i[1], rot_vel*r1.i[0]}};
  mVector2f delta_vel = mAdd_V2f(rb1->velocity,rot_vel_cross_r1); // mMul_f_V2f(fabs(rot_vel),r1_perp)); //??? SIGN ?

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

  // printf("%f\n", rb1->torque);

  // phRod_Joint2D* rod = joint->_sub;
  // phRigid_Body2D* rb1 = joint->rigid_body1;
  //
  // mGenerate_transform_2D(rb1->frame);
  // mVector2f pos1_world = mTransform_2D(joint->position1, rb1->frame->transform);
  // mVector2f pos2_world = joint->position2;
  //
  // mVector2f pos12 = mSub_V2f(pos1_world, pos2_world);
  // float pos12_norm = mNorm_V2f(pos12);
  //
  // if ( pos12_norm > 0.001 && rod->length > 0.001 ) {
  //
  //   mVector2f direction = mMul_f_V2f(1/pos12_norm, pos12);
  //
  //   // move if not at length apart
  //   if (pos12_norm < rod->length - 0.01 || pos12_norm > rod->length + 0.01) {
  //
  //     mVector2f correction = mMul_f_V2f( (rod->length - pos12_norm), direction );
  //     if (!rb1->is_static) {
  //       rb1->frame->position = mAdd_V2f(rb1->frame->position, correction);
  //     }
  //
  //     mGenerate_transform_2D(rb1->frame);
  //     pos1_world = mTransform_2D(joint->position1, rb1->frame->transform);
  //
  //     pos12 = mSub_V2f(pos1_world, pos2_world);
  //
  //   }
  //
  //   //NOTE: (see TODO) here now ONLY allowing position1 at rb1 centre and only applying forces to rb1
  //   if ( !rb1->is_static ) {
  //
  //     mVector2f direction_perp = (mVector2f){{-direction.i[1],direction.i[0]}};
  //     float angular_vel = mDot_V2f(rb1->velocity, direction_perp) / rod->length;
  //
  //     float force_perp = mDot_V2f(rb1->force, direction_perp);
  //
  //     angular_vel += force_perp * phDELTA_T / rod->length;
  //     float delta_angle = angular_vel * phDELTA_T;
  //
  //     mMatrix2f rot_mat = { .i = {
  //       {cos(delta_angle), -sin(delta_angle)},
  //       {sin(delta_angle),  cos(delta_angle)}
  //     }};
  //     rb1->frame->position = mAdd_V2f( pos2_world , mMul_M2f_V2f(rot_mat, pos12) );
  //
  //     mVector2f final_velocity = mMul_f_V2f(rod->length*delta_angle / phDELTA_T, direction_perp);
  //
  //     // rb1->force = mMul_f_V2f( 1/phDELTA_T, mSub_V2f(final_velocity, rb1->velocity) );
  //     rb1->velocity = final_velocity;
  //
  //   }
  //
  // }
  //
  // // phApply_Force_On_Velocity(rb1);

}
