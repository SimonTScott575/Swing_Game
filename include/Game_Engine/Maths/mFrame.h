// ######
// HEADER
// ######

#ifndef M_Frame_H
#define M_Frame_H

#include <stdio.h> //DEBUG
#include <stdlib.h>

#include <math.h>

// #include <Game_Engine/ECS/geComponent.h>

#include "mVector.h"
#include "mMatrix.h"
#include "mQuaternion.h"

#ifndef M_SCOPE
  #if defined(M_AS_HEADER)
    #define M_SCOPE extern
  #elif defined(M_AS_SOURCE)
    #define M_SCOPE
  #else
    #define M_SCOPE static
  #endif
#endif


typedef struct mFrame2D mFrame2D;
typedef struct mFrame3D mFrame3D;

struct mFrame2D {
  mMatrix3f transform;

  mVector2f position;
  float rotation;
  mVector2f scale;
};
struct mFrame3D {
  mMatrix4f transform;

  mVector3f position;
  mQuaternion quaternion;
  mVector3f scale;
};

M_SCOPE const mFrame2D mFrame2D_I;
M_SCOPE const mFrame3D mFrame3D_I;

M_SCOPE mFrame2D mFrame2D_init(mVector2f position, float rotation, mVector2f scale);
M_SCOPE mFrame3D mFrame3D_init(mVector3f position, mVector3f rotation, mVector3f scale);

M_SCOPE mFrame2D* mFrame2D_new(mVector2f position, float rotation, mVector2f scale);
M_SCOPE mFrame3D* mFrame3D_new(mVector3f position, mVector3f rotation, mVector3f scale);
M_SCOPE void mFrame2D_del(mFrame2D* frame);
M_SCOPE void mFrame3D_del(mFrame3D* frame);

M_SCOPE void mGenerate_transform_2D(mFrame2D* frame);
M_SCOPE void mGenerate_transform_3D(mFrame3D* frame);

M_SCOPE mVector2f mTransform_2D(mVector2f v, mMatrix3f transform);
M_SCOPE mVector2f mTransform_TR_2D(mVector2f v, mFrame2D frame);
M_SCOPE mVector2f mTransform_RS_2D(mVector2f v, mFrame2D frame);
M_SCOPE mVector2f mTransform_R_2D(mVector2f v, mFrame2D frame);
M_SCOPE mVector2f mInv_Transform_2D(mVector2f v, mFrame2D frame);

M_SCOPE mVector2f mAxis_X_2D(mFrame2D* frame);
M_SCOPE mVector3f mAxis_X_3D(mFrame3D* frame);

M_SCOPE mVector2f mAxis_Y_2D(mFrame2D* frame);
M_SCOPE mVector3f mAxis_Y_3D(mFrame3D* frame);

M_SCOPE mVector3f mAxis_Z_3D(mFrame3D* frame);

// ======
// Consts
// ======

M_SCOPE const mFrame2D mFrame2D_I = { .transform = mMatrix3f_I,

                                               .position = mVector2f_ZERO,
                                               .rotation = 0,
                                               .scale = mVector2f_ONE      };
M_SCOPE const mFrame3D mFrame3D_I = { .transform = mMatrix4f_I,

                                               .position = mVector3f_ZERO,
                                               .quaternion = mQuaternion_I,
                                               .scale = mVector3f_ONE       };

// ===
//
// ===

M_SCOPE
mFrame2D mFrame2D_init(mVector2f position, float rotation, mVector2f scale) {
  mFrame2D frame;
  frame.position = position;
  frame.rotation = rotation;
  frame.scale = scale;

  mGenerate_transform_2D(&frame);

  return frame;
};
M_SCOPE
mFrame3D mFrame3D_init(mVector3f position, mVector3f rotation, mVector3f scale) {
  mFrame3D frame;

  frame.position = position;
  frame.quaternion = mQuaternion_I;
  mRotate_YXZ_Q(rotation, &frame.quaternion);
  frame.scale = scale;

  mGenerate_transform_3D(&frame);

  return frame;
};

M_SCOPE
mFrame2D* mFrame2D_new(mVector2f position, float rotation, mVector2f scale) {

  mFrame2D* frame = malloc(sizeof(mFrame2D));

  *frame = mFrame2D_init(position, rotation, scale);

  return frame;

};
M_SCOPE
mFrame3D* mFrame3D_new(mVector3f position, mVector3f rotation, mVector3f scale) {

  mFrame3D* frame = malloc(sizeof(mFrame3D));

  *frame = mFrame3D_init(position, rotation, scale);

  return frame;

};

M_SCOPE
void mFrame2D_del(mFrame2D* frame) {
  free(frame);
}
M_SCOPE
void mFrame3D_del(mFrame3D* frame) {
  free(frame);
}

// ===

M_SCOPE
void mGenerate_transform_2D(mFrame2D* frame) { //? MACRO INLINE IS BETTER with non ptr ? have second with ptr for when using a manager?
  // *frame = mFrame2D_init(frame->position, frame->rotation, frame->scale);

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
M_SCOPE
void mGenerate_transform_3D(mFrame3D* frame) { //? MACRO INLINE IS BETTER with non ptr ? have second with ptr for when using a manager?
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

M_SCOPE
mVector2f mTransform_2D(mVector2f v, mMatrix3f transform) {
  mVector3f v3 = mMul_M3f_V3f(transform, (mVector3f){{v.i[0],v.i[1],1}});
  v = (mVector2f){{v3.i[0],v3.i[1]}};
  return v;
}
M_SCOPE
mVector2f mTransform_TR_2D(mVector2f v, mFrame2D frame) {
  frame.scale = mVector2f_ONE;
  mGenerate_transform_2D(&frame);
  mVector3f v3 = mMul_M3f_V3f(frame.transform,(mVector3f){{v.i[0],v.i[1],1}});
  return (mVector2f){{v3.i[0],v3.i[1]}};
}
M_SCOPE
mVector2f mTransform_RS_2D(mVector2f v, mFrame2D frame) {
  frame.position.i[0] = frame.position.i[1] = 0;
  mGenerate_transform_2D(&frame);
  mVector3f v3 = mMul_M3f_V3f(frame.transform,(mVector3f){{v.i[0],v.i[1],1}});
  return (mVector2f){{v3.i[0],v3.i[1]}};
}
M_SCOPE
mVector2f mTransform_R_2D(mVector2f v, mFrame2D frame) {
  frame.scale = mVector2f_ONE;
  frame.position = mVector2f_ZERO;
  mGenerate_transform_2D(&frame);
  mVector3f v3 = mMul_M3f_V3f(frame.transform,(mVector3f){{v.i[0],v.i[1],1}});
  return (mVector2f){{v3.i[0],v3.i[1]}};
}

M_SCOPE
mVector2f mInv_Transform_2D(mVector2f v, mFrame2D frame) {
  if (frame.scale.i[0] < 0.001 || frame.scale.i[1] < 0.001) {
    printf("\nDEBUG : ATTEMPT DIV 0\n");
    return v;
  }
  mVector2f scale = (mVector2f){{1/frame.scale.i[0],1/frame.scale.i[1]}};
  float r = -frame.rotation;
  mVector2f p = mMul_f_V2f(-1,frame.position);

  float s = sin(r);
  float c = cos(r);

  mMatrix3f SRT = {.i={
    { scale.i[0]*c,  -scale.i[0]*s, scale.i[0]*( c*p.i[0] - s*p.i[1] )},
    { scale.i[1]*s,   scale.i[1]*c, scale.i[1]*( s*p.i[0] + c*p.i[1] )},
    {0,0,1}
  }};

  mVector3f v3 = mMul_M3f_V3f(SRT,(mVector3f){{v.i[0],v.i[1],1}});
  return (mVector2f){{v3.i[0],v3.i[1]}};
}

// ====
// Axis
// ====

M_SCOPE
mVector2f mAxis_X_2D(mFrame2D* frame) {
  mVector2f result;
  result.i[0] = frame->transform.i[0][0];
  result.i[1] = frame->transform.i[1][0];

  return result;
}
M_SCOPE
mVector3f mAxis_X_3D(mFrame3D* frame) {
  mVector3f result;
  result.i[0] = frame->transform.i[0][0];
  result.i[1] = frame->transform.i[1][0];
  result.i[2] = frame->transform.i[2][0];

  return result;
}

M_SCOPE
mVector2f mAxis_Y_2D(mFrame2D* frame) {
  mVector2f result;
  result.i[0] = frame->transform.i[0][1];
  result.i[1] = frame->transform.i[1][1];

  return result;
}
M_SCOPE
mVector3f mAxis_Y_3D(mFrame3D* frame) {
  mVector3f result;
  result.i[0] = frame->transform.i[0][1];//! wrong way around?
  result.i[1] = frame->transform.i[1][1];
  result.i[2] = frame->transform.i[2][1];

  return result;
}

M_SCOPE
mVector3f mAxis_Z_3D(mFrame3D* frame) {
  mVector3f result;
  result.i[0] = frame->transform.i[0][2];//! wrong way around?
  result.i[1] = frame->transform.i[1][2];
  result.i[2] = frame->transform.i[2][2];

  return result;
}

/*** LEGACY ***/
#define new_mFrame2D mFrame2D_new
#define new_mFrame3D mFrame3D_new
#define del_mFrame2D mFrame2D_del
#define del_mFrame3D mFrame3D_del
#define init_mFrame2D mFrame2D_init
#define init_mFrame3D mFrame3D_init
/**************/

#endif
