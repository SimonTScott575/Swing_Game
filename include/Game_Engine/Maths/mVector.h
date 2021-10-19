#ifndef M_VECTOR_H
#define M_VECTOR_H

#include <stdbool.h>
#include <math.h>

#include "m_common.h"

#ifndef M_SCOPE
  #if defined(M_AS_HEADER)
    #define M_SCOPE extern
  #elif defined(M_AS_SOURCE)
    #define M_SCOPE
  #else
    #define M_SCOPE static
  #endif
#endif

#define mVector(N,TYPE) M_PASTE3( mVector__,N, M_PASTE3(__,TYPE,__) )

#define M_HEADER_VECTOR(TYPE, N, POSTFIX) \
  typedef struct mVector(N,TYPE) { TYPE i[N]; } mVector(N,TYPE);

#define M_SOURCE_VECTOR(TYPE, N, POSTFIX) \
                                          \
  M_SCOPE \
  mVector(N,TYPE) M_PASTE(mAdd_V, POSTFIX) ( \
    mVector(N,TYPE) a, \
    mVector(N,TYPE) b \
  ) { \
      \
    mVector(N,TYPE) result; \
                                      \
    for (int i = 0; i < N; i++) { \
      result.i[i] = a.i[i] + b.i[i]; \
    } \
      \
    return result; \
                   \
  } \
    \
  M_SCOPE \
  mVector(N,TYPE) M_PASTE(mSub_V, POSTFIX) ( \
    mVector(N,TYPE) a, \
    mVector(N,TYPE) b \
  ) { \
      \
    mVector(N,TYPE) result; \
                                      \
    for (int i = 0; i < N; i++) { \
      result.i[i] = a.i[i] - b.i[i]; \
    } \
      \
    return result; \
                   \
  } \
    \
  M_SCOPE \
  TYPE M_PASTE(mDot_V, POSTFIX) ( \
    mVector(N,TYPE) a, \
    mVector(N,TYPE) b \
  ) { \
      \
    TYPE result = 0; \
    for (int i = 0; i < N; i++) { \
      result += a.i[i]*b.i[i]; \
    } \
      \
    return result; \
                   \
  } \
    \
  M_SCOPE \
  TYPE M_PASTE(mNorm_V, POSTFIX) ( \
    mVector(N,TYPE) a \
  ) { \
      \
    TYPE result = 0; \
                     \
    for (int i = 0; i < N; i++) { \
      result += a.i[i]*a.i[i]; \
    } \
      \
    return sqrtf(result); \
                   \
  } \
    \
  M_SCOPE \
  mVector(N,TYPE) M_PASTE(mNormalized_V, POSTFIX) ( \
    mVector(N,TYPE) a \
  ) { \
      \
    TYPE norm = M_PASTE(mNorm_V,POSTFIX)(a); \
    for (int i = 0; i < N; i++) { \
      a.i[i] /= norm; \
    } \
      \
    return a; \
              \
  } \
    \
  M_SCOPE \
  bool M_PASTE(mNormalize_V, POSTFIX) ( \
    mVector(N,TYPE)* a \
  ) { \
      \
    TYPE norm = M_PASTE(mNorm_V,POSTFIX)(*a); \
    if (norm < 0.001) { \
      return false; \
    } \
      \
    for (int i = 0; i < N; i++) { \
      a->i[i] /= norm; \
    } \
      \
    return true; \
                 \
  } \
    \
  M_SCOPE \
  mVector(N,TYPE) M_PASTE(mMul_f_V, POSTFIX) ( \
    float a, \
    mVector(N,TYPE) b \
  ) { \
      \
    for (int i = 0; i < N; i++) { \
      b.i[i] *= a; \
    } \
      \
    return b; \
              \
  }

M_HEADER_VECTOR(float, 2, 2f);
M_HEADER_VECTOR(float, 3, 3f);
M_HEADER_VECTOR(float, 4, 4f);

M_SOURCE_VECTOR(float, 2, 2f);
M_SOURCE_VECTOR(float, 3, 3f);
M_SOURCE_VECTOR(float, 4, 4f);

#define mVector2(TYPE) mVector(2,TYPE)
#define mVector3(TYPE) mVector(3,TYPE)
#define mVector4(TYPE) mVector(4,TYPE)

M_SCOPE
float mCross_V2f(mVector(2,float) a, mVector(2,float) b) {
  return a.i[0]*b.i[1] - a.i[1]*b.i[0];
}

static const mVector(2,float) mVector2f_ZERO = {.i={0,0}};
static const mVector(3,float) mVector3f_ZERO = {.i={0,0,0}};
static const mVector(4,float) mVector4f_ZERO = {.i={0,0,0,0}};

static const mVector(2,float) mVector2f_ONE = {.i={1,1}};
static const mVector(3,float) mVector3f_ONE = {.i={1,1,1}};
static const mVector(4,float) mVector4f_ONE = {.i={1,1,1,1}};

static const mVector(2,float) mVector2f_X = {.i={1,0}};
static const mVector(2,float) mVector2f_Y = {.i={0,1}};

static const mVector(3,float) mVector3f_X = {.i={1,0,0}};
static const mVector(3,float) mVector3f_Y = {.i={0,1,0}};
static const mVector(3,float) mVector3f_Z = {.i={0,0,1}};

static const mVector(4,float) mVector4f_X = {.i={1,0,0,0}};
static const mVector(4,float) mVector4f_Y = {.i={0,1,0,0}};
static const mVector(4,float) mVector4f_Z = {.i={0,0,1,0}};
static const mVector(4,float) mVector4f_W = {.i={0,0,0,1}};

/*** LEGACY ***/
#define mVector2f mVector2(float)
#define mVector3f mVector3(float)
#define mVector4f mVector4(float)
/**************/

#endif
