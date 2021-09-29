#include <Game_Engine/Physics/phCollision_Solver.h>

//d
#include <stdio.h>

#include <stdlib.h>
#include <math.h>

#include <Game_Engine/Maths/mVector.h>

// ======
// static
// ======

static phDetect_Collisions_fn phDetect_Collisions_AABB_fns[PH_N_COLLIDER] = {
  phDetect_Collisions_AABB,
  phDetect_Collisions_AABB_CIRCLE,
  NULL //!!!
};
static phDetect_Collisions_fn phDetect_Collisions_CIRCLE_fns[PH_N_COLLIDER] = {
  NULL, //? never used etc ? (should swap so higher shape fns for lower shapes, then easier to add by user)
  phDetect_Collisions_CIRCLE,
  NULL
};
static phDetect_Collisions_fn phDetect_Collisions_POLYGON_fns[PH_N_COLLIDER] = {
  NULL,
  NULL, //? never used etc ?
  NULL
};
static phDetect_Collisions_fn* phDetect_Collisions_TYPE_fns[PH_N_COLLIDER] = {
  phDetect_Collisions_AABB_fns,
  phDetect_Collisions_CIRCLE_fns,
  phDetect_Collisions_POLYGON_fns
};

static phRay_Cast_fn phRay_Cast_fns[PH_N_COLLIDER] = {
  phRay_Cast_AABB,
  phRay_Cast_Circle,
  NULL
};

static void phSave_Collisions_In_Collider(phCollider2D* c, phCollision2D* collisions, uint64_t new_n_collisions) {

  if (c->_save_collisions) {

    // if (c->_n_collisions >= c->_max_collisions) {
    //   return;
    // }

    uint64_t save_n = (new_n_collisions > (c->_max_collisions - c->_n_collisions) ? c->_max_collisions - c->_n_collisions : new_n_collisions);

    phCollision2D* c_collisions = (phCollision2D*) c->_collisions + c->_n_collisions;

    for (uint64_t i = 0; i < save_n; i++) {
      *(c_collisions++) = *(collisions++);
    }

  }

}

// ==========================
// Initialization/Termination
// ==========================

phCollision_Solver2D* new_phCollision_Solver2D() {

  phCollision_Solver2D* result = malloc(sizeof(phCollision_Solver2D));

  result->_rigid_bodies = new_dLList(phRigid_Body2D_ptr)(0,NULL);
  result->_joints = new_dLList(phJoint2D_ptr)(0,NULL);

  for (int i = 0; i < 100; i++) {
    result->_collisions[i].accum_lambda = 0;
  }

  return result;

}

void del_phCollision_Solver2D(phCollision_Solver2D* cs) {

  del_dLList(phRigid_Body2D_ptr)(cs->_rigid_bodies);

  free(cs);

}

// ===

void phSolve_Collisions(phCollision_Solver2D* cs) {

  dNode_LL(phRigid_Body2D_ptr)* rb1_node = cs->_rigid_bodies->start;

  //
  while (rb1_node != NULL) {

    //... callbacks !

    rb1_node->element->collider->_n_collisions = 0;

    rb1_node = rb1_node->next;

  }

  //
  rb1_node = cs->_rigid_bodies->start;

  cs->_collisions_count = 0;
  phCollision2D* current_collision = cs->_collisions;

  for ( ; rb1_node != NULL; rb1_node = rb1_node->next) {

    dNode_LL(phRigid_Body2D_ptr)* rb2_node = rb1_node->next;

    for ( ; rb2_node != NULL; rb2_node = rb2_node->next) {

      if (rb1_node->element->_super != NULL && !rb1_node->element->_super->is_active) { continue; }
      if (rb1_node->element->_super != NULL && rb1_node->element->_super->_entity != NULL && !rb1_node->element->_super->_entity->is_active) { continue; }
      if (rb2_node->element->_super != NULL && !rb2_node->element->_super->is_active) { continue; }
      if (rb2_node->element->_super != NULL && rb2_node->element->_super->_entity != NULL && !rb2_node->element->_super->_entity->is_active) { continue; }

      uint64_t current_collision_count = phDetect_Collisions(rb1_node->element, rb2_node->element, current_collision);

      phSave_Collisions_In_Collider(rb1_node->element->collider, current_collision, current_collision_count);
      phSave_Collisions_In_Collider(rb2_node->element->collider, current_collision, current_collision_count);

      rb1_node->element->collider->_n_collisions += current_collision_count;
      rb2_node->element->collider->_n_collisions += current_collision_count;

      current_collision += current_collision_count;
      cs->_collisions_count += current_collision_count;

    }

  }

}

// ===================
// Collision Detection
// ===================

uint64_t phDetect_Collisions(phRigid_Body2D* a, phRigid_Body2D* b, phCollision2D* collisions) {

  if (a->collider->_collider_ID <= b->collider->_collider_ID) {

    return phDetect_Collisions_TYPE_fns[a->collider->_collider_ID][b->collider->_collider_ID](a, b, collisions);

  } else {

    uint64_t result = phDetect_Collisions_TYPE_fns[b->collider->_collider_ID][a->collider->_collider_ID](b, a, collisions);
    for (uint64_t i = 0; i < result; i++) {
      collisions[i].normal = mMul_f_V2f(-1, collisions[i].normal);
      collisions[i].sep_vel = mMul_f_V2f(-1, collisions[i].sep_vel);
      collisions[i].accum_lambda = 0;
    }

    return result;

  }

}

uint64_t phDetect_Collisions_AABB(phRigid_Body2D* rb1, phRigid_Body2D* rb2, phCollision2D* collisions) {
  //TODO: if collisions not NULL
  //TODO: should handle ALL collisions points preferably
  //TODO: position in collisions
  //? should collision positions be adjusted so not intersecting ?
  //!!! ONLY USES least penetration, but still calculates retracing

  phCollider2D* c1 = rb1->collider;
  phCollider2D* c2 = rb2->collider;
  phAABB_Collider2D* g1 = (phAABB_Collider2D*)c1->_sub;
  phAABB_Collider2D* g2 = (phAABB_Collider2D*)c2->_sub;

  float scaled_X_length_1 = c1->frame->scale.i[0]*g1->X_length/2;
  float scaled_X_length_2 = c2->frame->scale.i[0]*g2->X_length/2;
  float scaled_Y_length_1 = c1->frame->scale.i[1]*g1->Y_length/2;
  float scaled_Y_length_2 = c2->frame->scale.i[1]*g2->Y_length/2;

  float distance_X_12 = c1->frame->position.i[0] + scaled_X_length_1 - (c2->frame->position.i[0] - scaled_X_length_2); // left 2 to right 1
  float distance_X_21 = c2->frame->position.i[0] + scaled_X_length_2 - (c1->frame->position.i[0] - scaled_X_length_1); // left 1 to right 2
  float distance_Y_12 = c1->frame->position.i[1] + scaled_Y_length_1 - (c2->frame->position.i[1] - scaled_Y_length_2); // bottom 2 to top 1
  float distance_Y_21 = c2->frame->position.i[1] + scaled_Y_length_2 - (c1->frame->position.i[1] - scaled_Y_length_1); // bottom 1 to top 2

  // return 0 if not colliding
  bool is_colliding;
  if (
       distance_X_12 < 0
    || distance_X_21 < 0
    || distance_Y_12 < 0
    || distance_Y_21 < 0
  ) {
    is_colliding = false;
  } else {
    is_colliding = true;
  }

  if (!is_colliding) {
    return 0;
  }
  if (collisions == NULL) {
    return 1; //!!! only here for single return collision point, otherwise must put below
  }

  mVector2f rel_vel = mSub_V2f(rb1->velocity, rb2->velocity);
  mVector2f neg_rel_vel = mMul_f_V2f(-1, rel_vel);

  mVector2f normal;
  float distance;
  float delta_time;

  // least penetrating axis values
  mVector2f lp_normal_X;
  float distance_X;
  if (distance_X_12 < distance_X_21) { // 2 right of 1
    lp_normal_X = (mVector2f){{-1,0}};
    distance_X = distance_X_12;
  } else {
    lp_normal_X = (mVector2f){{1,0}};
    distance_X = distance_X_21;
  }
  mVector2f lp_normal_Y;
  float distance_Y;
  if (distance_Y_12 < distance_Y_21) { // 2 above 1
    lp_normal_Y = (mVector2f){{0,-1}};
    distance_Y = distance_Y_12;
  } else {
    lp_normal_Y = (mVector2f){{0,1}};
    distance_Y = distance_Y_21;
  }

  //NOTE: doesn't properly handle equidistance
  bool X_candidate = distance_X <= 2*scaled_X_length_1 && distance_X <= 2*scaled_X_length_2;
  bool Y_candidate = distance_Y <= 2*scaled_Y_length_1 && distance_Y <= 2*scaled_Y_length_2;
  if (X_candidate && Y_candidate) {
    normal = distance_X < distance_Y ? lp_normal_X : lp_normal_Y;
    distance = distance_X < distance_Y ? distance_X : distance_Y;
  } else if (X_candidate) {
    normal = lp_normal_X;
    distance = distance_X;
  } else {
    normal = lp_normal_Y;
    distance = distance_Y;
  }

  float nrv_dot_n = mDot_V2f(neg_rel_vel, normal);
  delta_time = ( 0.0001 < nrv_dot_n ) ? distance / nrv_dot_n : 0;

  collisions[0].rigid_body1 = rb1;
  collisions[0].rigid_body2 = rb2;

  collisions[0].normal = normal;
  collisions[0].distance = distance;
  collisions[0].sep_vel = rel_vel;
  collisions[0].delta_time = delta_time;

  return 1;

}
uint64_t phDetect_Collisions_CIRCLE(phRigid_Body2D* rb1, phRigid_Body2D* rb2, phCollision2D* collisions) {
  //TODO: with scaling to some extent

  phCollider2D* c1 = rb1->collider;
  phCollider2D* c2 = rb2->collider;
  phCircle_Collider2D* circle1 = c1->_sub;
  phCircle_Collider2D* circle2 = c2->_sub;

  float radius1 = circle1->radius * c1->frame->scale.i[0];
  float radius2 = circle2->radius * c2->frame->scale.i[0];

  mVector2f pos12 = mSub_V2f(rb1->frame->position, rb2->frame->position);
  float pos12_norm = mNorm_V2f(pos12);

  if (pos12_norm <= radius1 + radius2 && pos12_norm > 0.001) {

    if (collisions == NULL) {
      return 1;
    }

    mVector2f pos12_normalized = mMul_f_V2f(1/pos12_norm, pos12);
    mVector2f pos12_n_normalized = {{ -pos12_normalized.i[1], pos12_normalized.i[0] }};

    mVector2f rb1_point_vel = mAdd_V2f(rb1->velocity, mMul_f_V2f(-rb1->angular_velocity*radius1, pos12_n_normalized));
    mVector2f rb2_point_vel = mAdd_V2f(rb2->velocity, mMul_f_V2f(rb2->angular_velocity*radius2, pos12_n_normalized));

    float rel_vel_norm = mNorm_V2f( mSub_V2f(rb1->velocity, rb2->velocity) );

    float distance = radius1 + radius2 - pos12_norm;

    collisions[0] = (phCollision2D){
      .rigid_body1 = rb1,
      .rigid_body2 = rb2,

      .position = mAdd_V2f( rb2->frame->position, mMul_f_V2f(radius2, pos12_normalized) ),
      .normal = pos12_normalized,
      .distance = distance,

      .sep_vel = mSub_V2f(rb1_point_vel, rb2_point_vel),
      .delta_time = ( rel_vel_norm > 0.001 ? distance/rel_vel_norm : 0 ),

      .accum_lambda = 0
    };

    return 1;

  }

  return 0;

}

uint64_t phDetect_Collisions_AABB_CIRCLE(phRigid_Body2D* rb1, phRigid_Body2D* rb2, phCollision2D* collisions) {
  //TODO: scale, sort of
  //TODO: rb1 and rb2 wrong way round! (or change whole ordering)

  phCollider2D* c1 = rb1->collider;
  phCollider2D* c2 = rb2->collider;
  phAABB_Collider2D* aabb1 = c1->_sub; //!!!? wrrong
  phCircle_Collider2D* circle2 = c2->_sub;

  float radius2 = circle2->radius * c2->frame->scale.i[0];

  mVector2f bottom_left  = {{rb1->frame->position.i[0] - c1->frame->scale.i[0]*aabb1->X_length/2,
                             rb1->frame->position.i[1] - c1->frame->scale.i[1]*aabb1->Y_length/2}};
  mVector2f bottom_right = {{rb1->frame->position.i[0] + c1->frame->scale.i[0]*aabb1->X_length/2,
                             rb1->frame->position.i[1] - c1->frame->scale.i[1]*aabb1->Y_length/2}};
  mVector2f top_left = {{rb1->frame->position.i[0] - c1->frame->scale.i[0]*aabb1->X_length/2,
                         rb1->frame->position.i[1] + c1->frame->scale.i[1]*aabb1->Y_length/2}};
  mVector2f top_right = {{rb1->frame->position.i[0] + c1->frame->scale.i[0]*aabb1->X_length/2,
                         rb1->frame->position.i[1] + c1->frame->scale.i[1]*aabb1->Y_length/2}};

  mVector2f bottom_left_to_rb2 = mSub_V2f(rb2->frame->position, bottom_left);
  mVector2f bottom_right_to_rb2 = mSub_V2f(rb2->frame->position, bottom_right);
  mVector2f top_left_to_rb2 = mSub_V2f(rb2->frame->position, top_left);
  mVector2f top_right_to_rb2 = mSub_V2f(rb2->frame->position, top_right);

  float penetration_dist_left = bottom_left_to_rb2.i[0] + radius2;
  float penetration_dist_right = -bottom_right_to_rb2.i[0] + radius2;
  float penetration_dist_bottom = bottom_left_to_rb2.i[1] + radius2;
  float penetration_dist_top = -top_left_to_rb2.i[1] + radius2;

  mVector2f position;
  mVector2f normal;
  float distance;
  mVector2f sep_vel;
  float delta_time;

  if (    penetration_dist_left   > 0
       && penetration_dist_right  > 0
       && bottom_left_to_rb2.i[1] > 0
       && top_left_to_rb2.i[1]    < 0
  ) {

    if (penetration_dist_left < penetration_dist_right) {
      position = mAdd_V2f(rb2->frame->position, (mVector2f){{radius2,0}});
      normal = (mVector2f){{1,0}};
      distance = penetration_dist_left;
    } else {
      position = mAdd_V2f(rb2->frame->position, (mVector2f){{-radius2,0}});
      normal = (mVector2f){{-1,0}};
      distance = penetration_dist_right;
    }

  }
  else if (     penetration_dist_bottom  > 0
               && penetration_dist_top     > 0
               && bottom_left_to_rb2.i[0]  > 0
               && bottom_right_to_rb2.i[0] < 0
  ) {

    if (penetration_dist_bottom < penetration_dist_top) {
      position = mAdd_V2f(rb2->frame->position, (mVector2f){{0,radius2}});
      normal = (mVector2f){{0,1}};
      distance = penetration_dist_bottom;
    } else {
      position = mAdd_V2f(rb2->frame->position, (mVector2f){{0,-radius2}});
      normal = (mVector2f){{0,-1}};
      distance = penetration_dist_top;
    }

  } else if (
    (
      normal = bottom_left_to_rb2,
      distance = mNorm_V2f(normal)
    ) < radius2
  ) {

    if (distance < 0.001) {
      return 0;
    }
    position = mAdd_V2f( rb2->frame->position, mMul_f_V2f(-1, normal) );
    normal = mMul_f_V2f(-1/distance, normal);
    distance = radius2 - distance;

  } else if (
    (
      normal = bottom_right_to_rb2,
      distance = mNorm_V2f(normal)
    ) < radius2
  ) {

    if (distance < 0.001) {
      return 0;
    }
    position = mAdd_V2f( rb2->frame->position, mMul_f_V2f(-1, normal) );
    normal = mMul_f_V2f(-1/distance, normal);
    distance = radius2 - distance;

  } else if (
    (
      normal = top_left_to_rb2,
      distance = mNorm_V2f(normal)
    ) < radius2
  ) {

    if (distance < 0.001) {
      return 0;
    }
    position = mAdd_V2f( rb2->frame->position, mMul_f_V2f(-1, normal) );
    normal = mMul_f_V2f(-1/distance, normal);
    distance = radius2 - distance;

  } else if (
    (
      normal = top_right_to_rb2,
      distance = mNorm_V2f(normal)
    ) < radius2
  ) {

    if (distance < 0.001) {
      return 0;
    }
    position = mAdd_V2f( rb2->frame->position, mMul_f_V2f(-1, normal) );
    normal = mMul_f_V2f(-1/distance, normal);
    distance = radius2 - distance;

  } else {
    return 0;
  }

  sep_vel = mMul_f_V2f( rb2->angular_velocity*radius2, (mVector2f){{normal.i[1],-normal.i[0]}} );
  sep_vel = mSub_V2f(mSub_V2f(rb1->velocity, rb2->velocity), sep_vel);
  delta_time = mNorm_V2f(sep_vel) > 0.001 ? distance/mNorm_V2f(sep_vel) : 0;

  if (collisions != NULL) {

    collisions[0] = (phCollision2D){

      .rigid_body1 = rb2,
      .rigid_body2 = rb1,

      .position = position,
      .normal = normal,
      .distance = distance,
      .sep_vel = sep_vel,
      .delta_time = delta_time,

      .accum_lambda = 0

    };

  }

  return 1;

}

// ====================
// Collision Resolution
// ====================

float phGet_Collision_Lambda(phCollision2D collision) {

  phRigid_Body2D rb1 = *collision.rigid_body1; //? may want to change through fn
  phRigid_Body2D rb2 = *collision.rigid_body2;

  if (!rb1.is_kinetic && !rb2.is_kinetic) { return 0; }

  float inv_mass1 = (rb1.is_kinetic && !rb1.is_static) ? 1/rb1.mass : 0;
  float inv_mass2 = (rb2.is_kinetic && !rb2.is_static) ? 1/rb2.mass : 0;
  float inv_rot_inertia1 = (rb1.is_kinetic && !rb1.is_static_rotation) ? 1/rb1.rotational_inertia : 0;
  float inv_rot_inertia2 = (rb2.is_kinetic && !rb2.is_static_rotation) ? 1/rb2.rotational_inertia : 0;
  mVector2f r1 = mSub_V2f(collision.position, rb1.frame->position);
  mVector2f r2 = mSub_V2f(collision.position, rb2.frame->position);
  float r1_cross_n = r1.i[0]*collision.normal.i[1] - r1.i[1]*collision.normal.i[0];
  float r2_cross_n = r2.i[0]*collision.normal.i[1] - r2.i[1]*collision.normal.i[0];
  mVector2f rel_vel = mSub_V2f(rb1.velocity, rb2.velocity);

  float lambda =
      mDot_V2f( rel_vel, collision.normal )
    + rb1.angular_velocity*r1_cross_n
    - rb2.angular_velocity*r2_cross_n;
  lambda *= -(1 + (rb1.restitution + rb2.restitution)/2 ); // coefficient of restitution used here
  lambda += 0.2/phDELTA_T * (collision.distance > 0.01 ? collision.distance-0.01 : 0); // Baumgaute // +/- ?
  lambda /=
    inv_mass1
    + inv_mass2
    + inv_rot_inertia1*r1_cross_n*r1_cross_n
    + inv_rot_inertia2*r2_cross_n*r2_cross_n;

  lambda /= phDELTA_T; // delta time

  return lambda;

}

// ===============
// Collision Query
// ===============

bool phRay_Cast_Solver(mVector2f position, mVector2f direction, phCollision2D* collisions, phCollision_Solver2D* cs) { //? Ray_Cast_System ?

  dNode_LL(phRigid_Body2D_ptr)* rb_node = cs->_rigid_bodies->start;

  phCollision2D collision;

  bool is_colliding = false;

  for ( ; rb_node != NULL; rb_node = rb_node->next ) {

    bool this_is_colliding =
      phRay_Cast_fns[rb_node->element->collider->_collider_ID](
        position, direction, rb_node->element->collider, &collision
      ); // phRay_Cast_AABB(position, direction, rb_node->element->collider, &collision);

    if (collisions == NULL && this_is_colliding) {
      return true;
    }
    if ( this_is_colliding && ( !is_colliding || collision.distance < collisions[0].distance ) ) {
      collisions[0] = collision;
      collisions[0].rigid_body1 = rb_node->element;
    }

    is_colliding |= this_is_colliding;

  }

  return is_colliding;

}

bool phRay_Cast_Solver_Masked(
  mVector2f position,
  mVector2f direction,
  phCollision2D* collisions,
  geComponent_Layer_Mask c_req_lm,
  geEntity_Layer_Mask e_req_lm,
  phCollision_Solver2D* cs
) {
  //TODO: copy and past of above, probably a better rewrite ?

  dNode_LL(phRigid_Body2D_ptr)* rb_node = cs->_rigid_bodies->start;

  phCollision2D collision;

  bool is_colliding = false;

  for ( ; rb_node != NULL; rb_node = rb_node->next ) {

    if (    rb_node->element->_super != NULL
         && c_req_lm != 0
         && !(rb_node->element->_super->layer_mask & c_req_lm) ) {
      continue;
    }
    if (    rb_node->element->_super != NULL
         && rb_node->element->_super->_entity != NULL
         && e_req_lm != 0
         && !(rb_node->element->_super->_entity->layer_mask & e_req_lm) ) {
      continue;
    }

    bool this_is_colliding =
      phRay_Cast_fns[rb_node->element->collider->_collider_ID](
        position, direction, rb_node->element->collider, &collision
      ); // phRay_Cast_AABB(position, direction, rb_node->element->collider, &collision);

    if (collisions == NULL && this_is_colliding) {
      return true;
    }
    if ( this_is_colliding && ( !is_colliding || collision.distance < collisions[0].distance ) ) {
      collisions[0] = collision;
      collisions[0].rigid_body1 = rb_node->element;
    }

    is_colliding |= this_is_colliding;

  }

  return is_colliding;

}

//TODO: better code structure, MESSY/inconsistent!
bool phRay_Cast_AABB(mVector2f p, mVector2f dir, phCollider2D* c, phCollision2D* collisions) {

  // phCollider2D* c = rb_node->element->collider;
  phAABB_Collider2D* aabb = c->_sub;

  uint64_t n_collisions = 0; // bool is_colliding = false;

  mVector2f norm_dir = dir;
  if (!mNormalize_V2f(&norm_dir)) { return false; }
  mVector2f norm_dir_perp = (mVector2f){{-norm_dir.i[1], norm_dir.i[0]}};

  float closest_distance = INFINITY;
  mVector2f closest_position;
  mVector2f closest_normal;

  int signs1_X[4] = {-1,1,1,-1};
  int signs1_Y[4] = {-1,-1,1,1};
  int signs2_X[4] = {1,1,-1,-1};
  int signs2_Y[4] = {-1,1,1,-1};

  mVector2f normals[4] = {
    (mVector2f){{0,-1}},
    (mVector2f){{1,0}},
    (mVector2f){{0,1}},
    (mVector2f){{-1,0}}
  };

  for (int i = 0; i < 4; i++) {

    // positions of line segment ends
    mVector2f r1 = mAdd_V2f(
      c->frame->position,
      (mVector2f){{ signs1_X[i] * c->frame->scale.i[0]*aabb->X_length/2, signs1_Y[i] * c->frame->scale.i[1]*aabb->Y_length/2}}
    );
    mVector2f r2 = mAdd_V2f(
      c->frame->position,
      (mVector2f){{ signs2_X[i] * c->frame->scale.i[0]*aabb->X_length/2, signs2_Y[i] * c->frame->scale.i[1]*aabb->Y_length/2}}
    );

    // positions relative to ray position
    mVector2f r1_from_p = mSub_V2f(r1, p);
    mVector2f r2_from_p = mSub_V2f(r2, p);

    if (
      mCross_V2f(r1_from_p,dir)*mCross_V2f(r2_from_p,dir) < 0
    ) {

      // signed distances along direction
      float d1 = mDot_V2f(r1_from_p, norm_dir);
      float d2 = mDot_V2f(r2_from_p, norm_dir);

      // signed distances along perpendicular to direction
      float d1_perp = mDot_V2f(norm_dir_perp, r1_from_p);
      float d2_perp = mDot_V2f(norm_dir_perp, r2_from_p);

      // if (approx) inside edge dont trigger
      if (fabs(d1_perp) + fabs(d2_perp) < 0.001) {
        continue;
      }

      float gradient = ( d1 - d2 ) / ( fabs(d1_perp) + fabs(d2_perp) );
      float min_distance = fabs(d1) < fabs(d2) ? fabs(d1) : fabs(d2);

      // intersection point
      mVector2f q = mAdd_V2f(
        p,
        mMul_f_V2f(d2, norm_dir)
      );
      q = mAdd_V2f(
        q,
        mMul_f_V2f(gradient*fabs(d2_perp), norm_dir)
      );

      // if this_position behind or at position, don't trigger yet
      if ( mDot_V2f(mSub_V2f(q,p), dir) <= 0 ) {
        continue;
      } else {

        // trigger !
        n_collisions += 1;

        if (mNorm_V2f(mSub_V2f(q, p)) < closest_distance) {

          closest_position = q;
          closest_distance = mNorm_V2f(mSub_V2f(q, p));
          closest_normal = normals[i];

        }

      }

    }

  }

  if (n_collisions > 0 && n_collisions%2 != 1) {

    if (collisions != NULL) {
      collisions->distance = closest_distance;
      collisions->normal = closest_normal;
      collisions->position = closest_position;
    }

    return true;

  } else {

    return false;

  }

}
bool phRay_Cast_Circle(mVector2f position, mVector2f direction, phCollider2D* c, phCollision2D* collisions) {

  phCircle_Collider2D* circle = c->_sub;
  float radius = circle->radius*c->frame->scale.i[0];
  mVector2f rel_pos = mSub_V2f(c->frame->position, position);
  if (mNorm_V2f(rel_pos) <= radius) { return false; }

  float direction_norm = mNorm_V2f(direction);
  if (direction_norm < 0.001) { return false; }
  mVector2f norm_dir = mMul_f_V2f(1/direction_norm, direction);
  mVector2f norm_dir_n = (mVector2f){{-norm_dir.i[1], norm_dir.i[0]}};

  float s_distance = mDot_V2f(rel_pos, norm_dir);
  float s_distance_n = mDot_V2f(rel_pos, norm_dir_n);

  if (0 < s_distance && s_distance_n < radius) {

    if (collisions != NULL) {

      float distance = s_distance - sqrt(radius*radius - s_distance_n*s_distance_n);
      mVector2f normal;
      float normal_norm;

      collisions[0].distance = distance;
      collisions[0].position = mAdd_V2f(position, mMul_f_V2f(distance, norm_dir));

      normal = mSub_V2f(collisions[0].position, c->frame->position);
      if ( (normal_norm = mNorm_V2f(normal)) > 0.001 ) {
        collisions[0].normal = mMul_f_V2f(1/normal_norm, normal);
      } else {
        return false;
      }

    }

    return true;

  }

  return false;

}

uint64_t phGet_Collisions(phCollider2D* c, phCollision2D* collisions, phCollision_Solver2D* cs) { //!!! UNTESTED

  dNode_LL(phRigid_Body2D_ptr)* rb_node = cs->_rigid_bodies->start;

  phRigid_Body2D c_rb = init_phRigid_Body2D(c->frame, 1,1, c); //? better way ?

  uint64_t total_collisions = 0;

  while (rb_node != NULL) {

    uint64_t n_collisions = phDetect_Collisions(&c_rb, rb_node->element, collisions);

    collisions += n_collisions;
    total_collisions += n_collisions;

  }

  return total_collisions;

}

void phSave_Collider_Collisions(phCollider2D* collider, phCollision2D* collisions, uint64_t max_collisions) {

  collider->_save_collisions = true;
  collider->_collisions = collisions;
  collider->_max_collisions = max_collisions;

}
