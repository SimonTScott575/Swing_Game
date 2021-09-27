#if defined(M_AS_HEADER)
  #define M__Frame_SCOPE__ extern
#elif defined(M_AS_SOURCE)
  #define M__Frame_SCOPE__
#else
  #define M__Frame_SCOPE__ static
#endif

// ######
// HEADER
// ######

#ifndef M_Frame_H
#define M_Frame_H

#include <math.h>

#include <Game_Engine/ECS/geComponent.h>

#include "mVector.h"
#include "mMatrix.h"
#include "mQuaternion.h"

// ============
// Declarations
// ============

#ifndef M_NO_DEFAULTS

  typedef struct mFrame2D mFrame2D;
  typedef struct mFrame3D mFrame3D;

  struct mFrame2D {
    geComponent* _super;

    mMatrix3f transform;

    mVector2f position;
    float rotation;
    mVector2f scale;
  };
  struct mFrame3D {
    geComponent* _super;

    mMatrix4f transform;

    mVector3f position;
    mQuaternion quaternion;
    mVector3f scale;
  };

  M__Frame_SCOPE__ const mFrame2D mFrame2D_I;
  M__Frame_SCOPE__ const mFrame3D mFrame3D_I;

  M__Frame_SCOPE__ mFrame2D init_mFrame2D(mVector2f position, float rotation, mVector2f scale);
  M__Frame_SCOPE__ mFrame3D init_mFrame3D(mVector3f position, mVector3f rotation, mVector3f scale);

  M__Frame_SCOPE__ mFrame2D* new_mFrame2D(mVector2f position, float rotation, mVector2f scale);
  M__Frame_SCOPE__ mFrame3D* new_mFrame3D(mVector3f position, mVector3f rotation, mVector3f scale);
  M__Frame_SCOPE__ void del_mFrame2D_Sub_Component(geComponent* component);
  M__Frame_SCOPE__ void del_mFrame3D_Sub_Component(geComponent* component);
  // M__Frame_SCOPE__ void del_mFrame2D(mFrame2D* frame);
  // M__Frame_SCOPE__ void del_mFrame3D(mFrame3D* frame);
  // M__Frame_SCOPE__ void del_mFrame2D_void(void* frame);
  // M__Frame_SCOPE__ void del_mFrame3D_void(void* frame);

  M__Frame_SCOPE__ void mGenerate_transform_2D(mFrame2D* frame);
  M__Frame_SCOPE__ void mGenerate_transform_3D(mFrame3D* frame);

  M__Frame_SCOPE__ mVector2f mAxis_X_2D(mFrame2D* frame);
  M__Frame_SCOPE__ mVector3f mAxis_X_3D(mFrame3D* frame);

  M__Frame_SCOPE__ mVector2f mAxis_Y_2D(mFrame2D* frame);
  M__Frame_SCOPE__ mVector3f mAxis_Y_3D(mFrame3D* frame);

  M__Frame_SCOPE__ mVector3f mAxis_Z_3D(mFrame3D* frame);

#endif

// ===========
// Definitions
// ===========

#ifndef M_NO_DEFAULTS

  // ======
  // Consts
  // ======

  M__Frame_SCOPE__ const mFrame2D mFrame2D_I = { .transform = mMatrix3f_I,

                                                 .position = mVector2f_ZERO,
                                                 .rotation = 0,
                                                 .scale = mVector2f_ONE      };
  M__Frame_SCOPE__ const mFrame3D mFrame3D_I = { .transform = mMatrix4f_I,

                                                 .position = mVector3f_ZERO,
                                                 .quaternion = mQuaternion_I,
                                                 .scale = mVector3f_ONE       };

  // ===
  //
  // ===

  M__Frame_SCOPE__ mFrame2D init_mFrame2D(mVector2f position, float rotation, mVector2f scale) {
    mFrame2D frame;
    frame.position = position;
    frame.rotation = rotation;
    frame.scale = scale;

    mGenerate_transform_2D(&frame);

    return frame;
  };
  M__Frame_SCOPE__ mFrame3D init_mFrame3D(mVector3f position, mVector3f rotation, mVector3f scale) {
    mFrame3D frame;

    frame.position = position;
    frame.quaternion = mQuaternion_I;
    mRotate_YXZ_Q(rotation, &frame.quaternion);
    frame.scale = scale;

    mGenerate_transform_3D(&frame);

    return frame;
  };

  M__Frame_SCOPE__ mFrame2D* new_mFrame2D(mVector2f position, float rotation, mVector2f scale) {

    mFrame2D* frame = malloc(sizeof(mFrame2D));

    *frame = init_mFrame2D(position, rotation, scale);

    frame->_super = geCreate_Component();
    geSet_Sub_Component(frame, NULL, del_mFrame2D_Sub_Component, frame->_super);

    return frame;

  };
  M__Frame_SCOPE__ mFrame3D* new_mFrame3D(mVector3f position, mVector3f rotation, mVector3f scale) {

    mFrame3D* frame = malloc(sizeof(mFrame3D));

    *frame = init_mFrame3D(position, rotation, scale);

    frame->_super = geCreate_Component();
    geSet_Sub_Component(frame, NULL, del_mFrame3D_Sub_Component, frame->_super);

    return frame;

  };

  // M__Frame_SCOPE__ void del_mFrame2D(mFrame2D* frame) {
  //   geDestroy_Component(frame->_super);
  //   free(frame);
  // }
  // M__Frame_SCOPE__ void del_mFrame3D(mFrame3D* frame) {
  //   geDestroy_Component(frame->_super);
  //   free(frame);
  // }

  M__Frame_SCOPE__ void del_mFrame2D_Sub_Component(geComponent* component) {
    mFrame2D* frame = component->_sub;
    free(frame);
  }
  M__Frame_SCOPE__ void del_mFrame3D_Sub_Component(geComponent* component) {
    mFrame3D* frame = component->_sub;
    free(frame);
  }

  // M__Frame_SCOPE__ void del_mFrame2D_void(void* frame) {
  //   del_mFrame2D(frame);
  // }
  // M__Frame_SCOPE__ void del_mFrame3D_void(void* frame) {
  //   del_mFrame3D(frame);
  // }

  // ===

  M__Frame_SCOPE__ void mGenerate_transform_2D(mFrame2D* frame) { //? MACRO INLINE IS BETTER with non ptr ? have second with ptr for when using a manager?
    // *frame = init_mFrame2D(frame->position, frame->rotation, frame->scale);

    frame->transform.i[0][2] = frame->position.i[0];
    frame->transform.i[1][2] = frame->position.i[1];

    frame->transform.i[0][0] =  cos(frame->rotation);
    frame->transform.i[0][1] = -sin(frame->rotation);
    frame->transform.i[1][0] =  sin(frame->rotation);
    frame->transform.i[1][1] =  cos(frame->rotation);

    frame->transform.i[0][0] *= frame->scale.i[0];
    frame->transform.i[0][1] *= frame->scale.i[1];
    frame->transform.i[1][0] *= frame->scale.i[0];
    frame->transform.i[1][1] *= frame->scale.i[1];

    frame->transform.i[2][0] = frame->transform.i[2][1] = 0;
    frame->transform.i[2][2] = 1;
  }
  M__Frame_SCOPE__ void mGenerate_transform_3D(mFrame3D* frame) { //? MACRO INLINE IS BETTER with non ptr ? have second with ptr for when using a manager?
    // Translation
    frame->transform.i[0][3] = frame->position.i[0];
    frame->transform.i[1][3] = frame->position.i[1];
    frame->transform.i[2][3] = frame->position.i[2];

    // Rotation
    mQuaternion_to_Matrix4f_RONLY(frame->quaternion, &frame->transform);

    // Scale
    frame->transform.i[0][0] *= frame->scale.i[0];
    frame->transform.i[0][1] *= frame->scale.i[1];
    frame->transform.i[0][2] *= frame->scale.i[2];
    frame->transform.i[1][0] *= frame->scale.i[0];
    frame->transform.i[1][1] *= frame->scale.i[1];
    frame->transform.i[1][2] *= frame->scale.i[2];
    frame->transform.i[2][0] *= frame->scale.i[0];
    frame->transform.i[2][1] *= frame->scale.i[1];
    frame->transform.i[2][2] *= frame->scale.i[2];

    frame->transform.i[3][0] = 0;
    frame->transform.i[3][1] = 0;
    frame->transform.i[3][2] = 0;
    frame->transform.i[3][3] = 1;
  }

  // ====
  // Axis
  // ====

  M__Frame_SCOPE__ mVector2f mAxis_X_2D(mFrame2D* frame) {
    mVector2f result;
    result.i[0] = frame->transform.i[0][0];
    result.i[1] = frame->transform.i[1][0];
  }
  M__Frame_SCOPE__ mVector3f mAxis_X_3D(mFrame3D* frame) {
    mVector3f result;
    result.i[0] = frame->transform.i[0][0];
    result.i[1] = frame->transform.i[1][0];
    result.i[2] = frame->transform.i[2][0];

    return result;
  }

  M__Frame_SCOPE__ mVector2f mAxis_Y_2D(mFrame2D* frame) {
    mVector2f result;
    result.i[0] = frame->transform.i[0][1];
    result.i[1] = frame->transform.i[1][1];

    return result;
  }
  M__Frame_SCOPE__ mVector3f mAxis_Y_3D(mFrame3D* frame) {
    mVector3f result;
    result.i[0] = frame->transform.i[0][1];//! wrong way around?
    result.i[1] = frame->transform.i[1][1];
    result.i[2] = frame->transform.i[2][1];

    return result;
  }

  M__Frame_SCOPE__ mVector3f mAxis_Z_3D(mFrame3D* frame) {
    mVector3f result;
    result.i[0] = frame->transform.i[0][2];//! wrong way around?
    result.i[1] = frame->transform.i[1][2];
    result.i[2] = frame->transform.i[2][2];

    return result;
  }

#endif

#endif
