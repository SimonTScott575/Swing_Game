#if defined(M_AS_HEADER)
  #define M__Quaternion_SCOPE__ extern
#elif defined(M_AS_SOURCE)
  #define M__Quaternion_SCOPE__
#else
  #define M__Quaternion_SCOPE__ static
#endif

// ######
// HEADER
// ######

#ifndef M_Quaternion_H
#define M_Quaternion_H

#include <math.h>

#include <Game_Engine/Maths/mVector.h>
#include <Game_Engine/Maths/mMatrix.h>

// ============
// Declarations
// ============

#ifndef M_NO_DEFAULTS

  typedef mVector4f mQuaternion; // { x, y, z, w } is w + xi + yj + zk

  M__Quaternion_SCOPE__ const mQuaternion mQuaternion_I;

  M__Quaternion_SCOPE__ mQuaternion mQuaternion_axis_angle(mVector3f axis, float angle);
  M__Quaternion_SCOPE__ float mNorm_Q(mQuaternion q);
  M__Quaternion_SCOPE__ mQuaternion mNormalized_Q(mQuaternion q);
  M__Quaternion_SCOPE__ mQuaternion mInv_Q(mQuaternion q);
  M__Quaternion_SCOPE__ mQuaternion mMul_Q(mQuaternion qA, mQuaternion qB);
  M__Quaternion_SCOPE__ void mRotate_axis_angle_Q(mVector3f axis, float angle, mQuaternion* q);
  // This rotates result about global Y, X, then Z.
  // This is intrinsically about Z, X then Y where the inital axes align with the global.
  M__Quaternion_SCOPE__ void mRotate_YXZ_Q(mVector3f rotation, mQuaternion* quaternion);
  M__Quaternion_SCOPE__ void mQuaternion_to_Matrix4f_RONLY(mQuaternion q, mMatrix4f* result);

#endif

// ===========
// Definitions
// ===========

#ifndef M_NO_DEFAULTS

  // ======
  // Consts
  // ======

  M__Quaternion_SCOPE__ const mQuaternion mQuaternion_I = { .i = { 0, 0, 0, 1 } };

  // ===
  //
  // ===

  M__Quaternion_SCOPE__ mQuaternion mQuaternion_axis_angle(mVector3f axis, float angle) {
    mQuaternion result;
    float s = sin(angle / 2);
    result.i[0] = axis.i[0] * s;
    result.i[1] = axis.i[1] * s;
    result.i[2] = axis.i[2] * s;
    result.i[3] = cos(angle / 2);

    return result;
  }

  M__Quaternion_SCOPE__ float mNorm_Q(mQuaternion q) {
    return sqrt(q.i[0]*q.i[0] + q.i[1]*q.i[1] + q.i[2]*q.i[2] + q.i[3]*q.i[3]);
  }

  M__Quaternion_SCOPE__ mQuaternion mNormalized_Q(mQuaternion q) {
    return mMul_f_V4f(1/mNorm_Q(q), q);
  }

  M__Quaternion_SCOPE__ mQuaternion mInv_Q(mQuaternion q) {
    mQuaternion result;

    result.i[3] =  q.i[3];

    result.i[0] = -q.i[0];
    result.i[1] = -q.i[1];
    result.i[2] = -q.i[2];

    return result;
  }

  M__Quaternion_SCOPE__ mQuaternion mMul_Q(mQuaternion qA, mQuaternion qB) {
    mQuaternion result;
    result.i[3] = qA.i[3]*qB.i[3] - qA.i[0]*qB.i[0] - qA.i[1]*qB.i[1] - qA.i[2]*qB.i[2];

    result.i[0] = qA.i[1]*qB.i[2] - qA.i[2]*qB.i[1] + qA.i[3]*qB.i[0] + qA.i[0]*qB.i[3];
    result.i[1] = qA.i[2]*qB.i[0] - qA.i[0]*qB.i[2] + qA.i[3]*qB.i[1] + qA.i[1]*qB.i[3];
    result.i[2] = qA.i[0]*qB.i[1] - qA.i[1]*qB.i[0] + qA.i[3]*qB.i[2] + qA.i[2]*qB.i[3];

    return result;
  }

  M__Quaternion_SCOPE__ void mRotate_axis_angle_Q(mVector3f axis, float angle, mQuaternion* q) {
    mQuaternion axis_angle_q = mQuaternion_axis_angle(axis, angle);
    *q = mMul_Q(axis_angle_q, *q);
  }

  // This rotates result about global Y, X, then Z.
  // This is intrinsically about Z, X then Y where the inital axes align with the global.
  M__Quaternion_SCOPE__ void mRotate_YXZ_Q(mVector3f rotation, mQuaternion* quaternion) {
    mQuaternion q_rot_Y = { .i = {
      0,
      sin(rotation.i[0] / 2),
      0,
      cos(rotation.i[0] / 2)
    }};
    *quaternion = mMul_Q(q_rot_Y, *quaternion);

    mQuaternion q_rot_X = { .i = {
      sin(rotation.i[1] / 2),
      0,
      0,
      cos(rotation.i[1] / 2)
    }};
    *quaternion = mMul_Q(q_rot_X, *quaternion);

    mQuaternion q_rot_Z = { .i = {
      0,
      0,
      sin(rotation.i[2] / 2),
      cos(rotation.i[2] / 2)
    }};
    *quaternion = mMul_Q(q_rot_Z, *quaternion);
  }

  M__Quaternion_SCOPE__ void mQuaternion_to_Matrix4f_RONLY(mQuaternion q, mMatrix4f* result) {
    result->i[0][0] = 1 - 2*q.i[1]*q.i[1] - 2*q.i[2]*q.i[2];
    result->i[0][1] = 2*q.i[0]*q.i[1] - 2*q.i[3]*q.i[2];
    result->i[0][2] = 2*q.i[0]*q.i[2] + 2*q.i[3]*q.i[1];
    // result.i[0][3] = 0;

    result->i[1][0] = 2*q.i[0]*q.i[1] + 2*q.i[3]*q.i[2];
    result->i[1][1] = 1 - 2*q.i[0]*q.i[0] - 2*q.i[2]*q.i[2];
    result->i[1][2] = 2*q.i[1]*q.i[2] - 2*q.i[3]*q.i[0];
    // result.i[1][3] = 0;

    result->i[2][0] = 2*q.i[0]*q.i[2] - 2*q.i[3]*q.i[1];
    result->i[2][1] = 2*q.i[1]*q.i[2] + 2*q.i[3]*q.i[0];
    result->i[2][2] = 1 - 2*q.i[0]*q.i[0] - 2*q.i[1]*q.i[1];
    // result.i[2][3] = 0;

    // result.i[3][0] = 0;
    // result.i[3][1] = 0;
    // result.i[3][2] = 0;
    // result.i[3][3] = 1;
  }

#endif

#endif
