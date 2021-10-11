// ######
// HEADER
// ######

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

#define M_HEADER_VECTOR(TYPE, N, POSTFIX) \
  typedef struct M_PASTE(mVector,POSTFIX) { TYPE i[N]; } M_PASTE(mVector,POSTFIX);

#define M_SOURCE_VECTOR(TYPE, N, POSTFIX) \
                                          \
  M_SCOPE \
  M_PASTE(mVector, POSTFIX) M_PASTE(mAdd_V, POSTFIX) ( \
    M_PASTE(mVector, POSTFIX) a, \
    M_PASTE(mVector, POSTFIX) b \
  ) { \
      \
    M_PASTE(mVector, POSTFIX) result; \
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
  M_PASTE(mVector, POSTFIX) M_PASTE(mSub_V, POSTFIX) ( \
    M_PASTE(mVector, POSTFIX) a, \
    M_PASTE(mVector, POSTFIX) b \
  ) { \
      \
    M_PASTE(mVector, POSTFIX) result; \
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
    M_PASTE(mVector, POSTFIX) a, \
    M_PASTE(mVector, POSTFIX) b \
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
    M_PASTE(mVector, POSTFIX) a \
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
  M_PASTE(mVector, POSTFIX) M_PASTE(mNormalized_V, POSTFIX) ( \
    M_PASTE(mVector, POSTFIX) a \
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
    M_PASTE(mVector, POSTFIX)* a \
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
  M_PASTE(mVector, POSTFIX) M_PASTE(mMul_f_V, POSTFIX) ( \
    float a, \
    M_PASTE(mVector, POSTFIX) b \
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

M_SCOPE
float mCross_V2f(mVector2f a, mVector2f b) {
  return a.i[0]*b.i[1] - a.i[1]*b.i[0];
}

static const mVector2f mVector2f_ZERO = {.i={0,0}};
static const mVector3f mVector3f_ZERO = {.i={0,0,0}};
static const mVector4f mVector4f_ZERO = {.i={0,0,0,0}};

static const mVector2f mVector2f_ONE = {.i={1,1}};
static const mVector3f mVector3f_ONE = {.i={1,1,1}};
static const mVector4f mVector4f_ONE = {.i={1,1,1,1}};

static const mVector2f mVector2f_X = {.i={1,0}};
static const mVector2f mVector2f_Y = {.i={0,1}};

static const mVector3f mVector3f_X = {.i={1,0,0}};
static const mVector3f mVector3f_Y = {.i={0,1,0}};
static const mVector3f mVector3f_Z = {.i={0,0,1}};

static const mVector4f mVector4f_X = {.i={1,0,0,0}};
static const mVector4f mVector4f_Y = {.i={0,1,0,0}};
static const mVector4f mVector4f_Z = {.i={0,0,1,0}};
static const mVector4f mVector4f_W = {.i={0,0,0,1}};


#endif

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++














// // ==============
// // DECLARE Macros
// // ==============
//
// #define m_CT(A, B) A ## B
// #define m_C(A, B) m_CT(A, B)
//
// // ==============
// // DECLARE Macros
// // ==============
//
// #define M__TYPES_HEADER_VECTOR__(TYPE, N, POSTFIX) \
//   struct mVector ## POSTFIX ; \
//   typedef struct mVector ## POSTFIX mVector ## POSTFIX ; \
//   struct mVector ## POSTFIX { \
//     TYPE i[N]; \
//   };
//
// #define M__DECLARE_OP__(TYPE, N, POSTFIX, SCOPE, TYPE2, NAME, OP, FUNC_NAME) \
//   SCOPE mVector ## POSTFIX m_C( m_C( m ## FUNC_NAME , _ ## NAME ) , _V ## POSTFIX) (TYPE2 a, mVector ## POSTFIX b);
// #define M__FUNCS_HEADER_VECTOR__(TYPE, N, POSTFIX, SCOPE) \
//   SCOPE mVector ## POSTFIX mAdd_V ## POSTFIX ( mVector ## POSTFIX a, mVector ## POSTFIX b ); \
//   SCOPE mVector ## POSTFIX mSub_V ## POSTFIX ( mVector ## POSTFIX a, mVector ## POSTFIX b ); \
//                                                                                              \
//   M__DECLARE_OP__(TYPE, N, POSTFIX, SCOPE, float, f, *, Mul) \
//   M__DECLARE_OP__(TYPE, N, POSTFIX, SCOPE, double, d, *, Mul) \
//   M__DECLARE_OP__(TYPE, N, POSTFIX, SCOPE, int, i, *, Mul) \
//   M__DECLARE_OP__(TYPE, N, POSTFIX, SCOPE, unsigned int, ui, *, Mul) \
//                                                                      \
//   M__DECLARE_OP__(TYPE, N, POSTFIX, SCOPE, float, f, +, Add) \
//   M__DECLARE_OP__(TYPE, N, POSTFIX, SCOPE, double, d, +, Add) \
//   M__DECLARE_OP__(TYPE, N, POSTFIX, SCOPE, int, i, +, Add) \
//   M__DECLARE_OP__(TYPE, N, POSTFIX, SCOPE, unsigned int, ui, +, Add) \
//                                                                      \
//   M__DECLARE_OP__(TYPE, N, POSTFIX, SCOPE, float, f, -, Sub) \
//   M__DECLARE_OP__(TYPE, N, POSTFIX, SCOPE, double, d, -, Sub) \
//   M__DECLARE_OP__(TYPE, N, POSTFIX, SCOPE, int, i, -, Sub) \
//   M__DECLARE_OP__(TYPE, N, POSTFIX, SCOPE, unsigned int, ui, -, Sub) \
//                                                                      \
//   SCOPE TYPE mNorm_V ## POSTFIX ( mVector ## POSTFIX v ); \
//   SCOPE bool mNormalize_V ## POSTFIX ( mVector ## POSTFIX * v ); \
//   SCOPE TYPE mDot_V ## POSTFIX ( mVector ## POSTFIX a, mVector ## POSTFIX b);
//
// #define D__DECLARE_CONSTS1__(TYPE_NAME, SCOPE) \
//   SCOPE const mVector2 ## TYPE_NAME m_C(mVector2 ## TYPE_NAME, _ZERO); \
//   SCOPE const mVector2 ## TYPE_NAME m_C(mVector2 ## TYPE_NAME, _ONE); \
//                                                                       \
//   SCOPE const mVector3 ## TYPE_NAME m_C(mVector3 ## TYPE_NAME, _ZERO); \
//   SCOPE const mVector3 ## TYPE_NAME m_C(mVector3 ## TYPE_NAME, _ONE); \
//                                                                       \
//   SCOPE const mVector4 ## TYPE_NAME m_C(mVector4 ## TYPE_NAME, _ZERO); \
//   SCOPE const mVector4 ## TYPE_NAME m_C(mVector4 ## TYPE_NAME, _ONE);
//
// #define D__DECLARE_CONSTS2__(TYPE_NAME, SCOPE) \
//   SCOPE const mVector2 ## TYPE_NAME m_C(mVector2 ## TYPE_NAME, _X); \
//   SCOPE const mVector2 ## TYPE_NAME m_C(mVector2 ## TYPE_NAME, _Y); \
//                                                                     \
//   SCOPE const mVector3 ## TYPE_NAME m_C(mVector3 ## TYPE_NAME, _X); \
//   SCOPE const mVector3 ## TYPE_NAME m_C(mVector3 ## TYPE_NAME, _Y); \
//   SCOPE const mVector3 ## TYPE_NAME m_C(mVector3 ## TYPE_NAME, _Z); \
//                                                                     \
//   SCOPE const mVector4 ## TYPE_NAME m_C(mVector4 ## TYPE_NAME, _X); \
//   SCOPE const mVector4 ## TYPE_NAME m_C(mVector4 ## TYPE_NAME, _Y); \
//   SCOPE const mVector4 ## TYPE_NAME m_C(mVector4 ## TYPE_NAME, _Z); \
//   SCOPE const mVector4 ## TYPE_NAME m_C(mVector4 ## TYPE_NAME, _W);
//
// #define M_HEADER_VECTOR(TYPE, N, POSTFIX) \
//   M__TYPES_HEADER_VECTOR__(TYPE, N, POSTFIX) \
//   M__FUNCS_HEADER_VECTOR__(TYPE, N, POSTFIX, )
// /*** LEGACY ***/
// #define M_HEADER_mVector M_HEADER_VECTOR
// /**************/
//
// // ============
// // Declarations
// // ============
//
// #ifndef M_NO_DEFAULTS
//
//   M__TYPES_HEADER_VECTOR__(float, 2, 2f)
//   M__TYPES_HEADER_VECTOR__(float, 3, 3f)
//   M__TYPES_HEADER_VECTOR__(float, 4, 4f)
//
//   M__FUNCS_HEADER_VECTOR__(float, 2, 2f, M_SCOPE)
//   M__FUNCS_HEADER_VECTOR__(float, 3, 3f, M_SCOPE)
//   M__FUNCS_HEADER_VECTOR__(float, 4, 4f, M_SCOPE)
//
//   M_SCOPE mVector3f mCross_V3f(mVector3f a, mVector3f b);
//
//   D__DECLARE_CONSTS1__(f, M_SCOPE)
//   D__DECLARE_CONSTS2__(f, M_SCOPE)
//
// #endif
//
// // =============
// // DEFINE Macros
// // =============
//
// #define M__SOURCE_VECTOR__(TYPE, N, POSTFIX, SCOPE) \
//   SCOPE mVector ## POSTFIX mAdd_V ## POSTFIX ( mVector ## POSTFIX a, mVector ## POSTFIX b ) { \
//     mVector ## POSTFIX result; \
//     for (int i = 0; i < N; i++) { \
//       result.i[i] = a.i[i] + b.i[i]; \
//     } \
//       \
//     return result; \
//   } \
//   SCOPE mVector ## POSTFIX mSub_V ## POSTFIX ( mVector ## POSTFIX a, mVector ## POSTFIX b ) { \
//     mVector ## POSTFIX result; \
//     for (int i = 0; i < N; i++) { \
//       result.i[i] = a.i[i] - b.i[i]; \
//     } \
//       \
//     return result; \
//   } \
//     \
//
//   SCOPE mVector ## POSTFIX mAdd_
//
//   SCOPE mVector ## POSTFIX m_C( m_C( m ## FUNC_NAME , _ ## NAME ) , _V ## POSTFIX) (TYPE2 a, mVector ## POSTFIX b) { \
//     mVector ## POSTFIX result; \
//     for (int i = 0; i < N; i++) { \
//       result.i[i] = a OP b.i[i]; \
//     } \
//       \
//     return result; \
//   }
//
//   M__SOURCE_OP__(TYPE, N, POSTFIX, SCOPE, float, f, *, Mul) \
//   M__SOURCE_OP__(TYPE, N, POSTFIX, SCOPE, double, d, *, Mul) \
//   M__SOURCE_OP__(TYPE, N, POSTFIX, SCOPE, int, i, *, Mul) \
//   M__SOURCE_OP__(TYPE, N, POSTFIX, SCOPE, unsigned int, ui, *, Mul) \
//                                                                     \
//   M__SOURCE_OP__(TYPE, N, POSTFIX, SCOPE, float, f, +, Add) \
//   M__SOURCE_OP__(TYPE, N, POSTFIX, SCOPE, double, d, +, Add) \
//   M__SOURCE_OP__(TYPE, N, POSTFIX, SCOPE, int, i, +, Add) \
//   M__SOURCE_OP__(TYPE, N, POSTFIX, SCOPE, unsigned int, ui, +, Add) \
//                                                                     \
//   M__SOURCE_OP__(TYPE, N, POSTFIX, SCOPE, float, f, -, Sub) \
//   M__SOURCE_OP__(TYPE, N, POSTFIX, SCOPE, double, d, -, Sub) \
//   M__SOURCE_OP__(TYPE, N, POSTFIX, SCOPE, int, i, -, Sub) \
//   M__SOURCE_OP__(TYPE, N, POSTFIX, SCOPE, unsigned int, ui, -, Sub) \
//                                                                     \
//   SCOPE TYPE mNorm_V ## POSTFIX ( mVector ## POSTFIX v ) { \
//     TYPE result = 0; \
//     for (int i = 0; i < N; i++) { \
//       result += v.i[i]*v.i[i]; \
//     } \
//       \
//     return sqrt(fabs(result)); \
//   } \
//   SCOPE mVector ## POSTFIX mNormalized_V ## POSTFIX ( mVector ## POSTFIX v ) { \
//     v = mMul_f_V ##POSTFIX ( 1/mNorm_V ## POSTFIX (v) , v ); \
//     return v; \
//   } \
//   SCOPE bool mNormalize_V ## POSTFIX ( mVector ## POSTFIX * v ) { \
//                                                                   \
//     TYPE norm = mNorm_V ## POSTFIX ( *v ); \
//                                            \
//     bool is_large_norm = norm > 0.001; \
//                                        \
//     if ( is_large_norm ) { \
//                            \
//       *v = mMul_f_V ## POSTFIX ( 1/norm , *v ); \
//                                     \
//     } \
//       \
//     return is_large_norm; \
//   } \
//     \
//   SCOPE TYPE mDot_V ## POSTFIX ( mVector ## POSTFIX a, mVector ## POSTFIX b) { \
//     TYPE result = 0; \
//     for (int i = 0; i < N; i++) { \
//       result += a.i[i] * b.i[i]; \
//     } \
//       \
//     return result;  \
//   }
// #define M_SOURCE_VECTOR(TYPE, N, POSTFIX) \
//   M__SOURCE_VECTOR__(TYPE, N, POSTFIX, )
// #define M_STATIC_VECTOR(TYPE, N, POSTFIX) \
//   M__SOURCE_VECTOR__(TYPE, N, POSTFIX, static)
// /*** LEGACY ***/
// #define M_SOURCE_mVector M_SOURCE_VECTOR
// #define M_STATIC_mVector M_STATIC_VECTOR
// /**************/
//
// // ===========
// // Definitions
// // ===========
//
// #ifndef M_NO_DEFAULTS
//
//   M__SOURCE_VECTOR__(float, 2, 2f, M_SCOPE)
//   M__SOURCE_VECTOR__(float, 3, 3f, M_SCOPE)
//   M__SOURCE_VECTOR__(float, 4, 4f, M_SCOPE)
//
//   M_SCOPE float mCross_V2f(mVector2f a, mVector2f b) { //TODO: should not be static if defined not_header_only or something
//     float result = a.i[0]*b.i[1] - a.i[1]*b.i[0];
//
//     return result;
//   }
//   M_SCOPE mVector3f mCross_V3f(mVector3f a, mVector3f b) { //TODO: should not be static if defined not_header_only or something
//     mVector3f result = {
//       .i = {
//         a.i[1] * b.i[2] - a.i[2] * b.i[1],
//         a.i[2] * b.i[0] - a.i[0] * b.i[2],
//         a.i[0] * b.i[1] - a.i[1] * b.i[0]
//       }
//     };
//
//     return result;
//   }
//
//   #define D__SOURCE_CONSTS1__(TYPE_NAME, SCOPE) \
//     SCOPE const mVector2 ## TYPE_NAME m_C(mVector2 ## TYPE_NAME, _ZERO) = { .i = {0} }; \
//     SCOPE const mVector2 ## TYPE_NAME m_C(mVector2 ## TYPE_NAME, _ONE) = { .i = {1, 1} }; \
//                                                                                        \
//     SCOPE const mVector3 ## TYPE_NAME m_C(mVector3 ## TYPE_NAME, _ZERO) = { .i = {0} }; \
//     SCOPE const mVector3 ## TYPE_NAME m_C(mVector3 ## TYPE_NAME, _ONE) = { .i = {1, 1, 1} }; \
//                                                                                        \
//     SCOPE const mVector4 ## TYPE_NAME m_C(mVector4 ## TYPE_NAME, _ZERO) = { .i = {0} }; \
//     SCOPE const mVector4 ## TYPE_NAME m_C(mVector4 ## TYPE_NAME, _ONE) = { .i = {1, 1, 1, 1} };
//
//   #define D__SOURCE_CONSTS2__(TYPE_NAME, SCOPE) \
//     SCOPE const mVector2 ## TYPE_NAME m_C(mVector2 ## TYPE_NAME, _X) = { .i = {1,0} }; \
//     SCOPE const mVector2 ## TYPE_NAME m_C(mVector2 ## TYPE_NAME, _Y) = { .i = {0,1} }; \
//                                                                                        \
//     SCOPE const mVector3 ## TYPE_NAME m_C(mVector3 ## TYPE_NAME, _X) = { .i = {1,0,0} }; \
//     SCOPE const mVector3 ## TYPE_NAME m_C(mVector3 ## TYPE_NAME, _Y) = { .i = {0,1,0} }; \
//     SCOPE const mVector3 ## TYPE_NAME m_C(mVector3 ## TYPE_NAME, _Z) = { .i = {0,0,1} }; \
//                                                                                          \
//     SCOPE const mVector4 ## TYPE_NAME m_C(mVector4 ## TYPE_NAME, _X) = { .i = {1,0,0,0} }; \
//     SCOPE const mVector4 ## TYPE_NAME m_C(mVector4 ## TYPE_NAME, _Y) = { .i = {0,1,0,0} }; \
//     SCOPE const mVector4 ## TYPE_NAME m_C(mVector4 ## TYPE_NAME, _Z) = { .i = {0,0,1,0} }; \
//     SCOPE const mVector4 ## TYPE_NAME m_C(mVector4 ## TYPE_NAME, _W) = { .i = {0,0,0,1} };
//
//   D__SOURCE_CONSTS1__(f, M_SCOPE)
//   D__SOURCE_CONSTS2__(f, M_SCOPE)
//
// #endif
//
// // ========
// // Clean up
// // ========
//
// #undef D__SOURCE_CONSTS1__
// #undef D__SOURCE_CONSTS2__
// #undef D__DECLARE_CONSTS1__
// #undef D__DECLARE_CONSTS2__
//
// #endif
