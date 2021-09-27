#if defined(M_AS_HEADER)
  #define M__Matrix_SCOPE__ extern
#elif defined(M_AS_SOURCE)
  #define M__Matrix_SCOPE__
#else
  #define M__Matrix_SCOPE__ static
#endif

// ######
// HEADER
// ######

#ifndef M_Matrix_H
#define M_Matrix_H

#include <stdint.h>

#include "mVector.h"

// ==============
// DECLARE Macros
// ==============

#define m_CT(A, B) A ## B
#define m_C(A, B) m_CT(A, B)

#define M__TYPES_HEADER_mMatrixN__(TYPE, N, POSTFIX) \
  struct mMatrix ## POSTFIX ; \
  typedef struct mMatrix ## POSTFIX mMatrix ## POSTFIX ; \
  struct mMatrix ## POSTFIX { \
    TYPE i[N][N]; \
  };

#define M__DECLARE_OP_mMatrixN__(TYPE, N, POSTFIX, SCOPE, TYPE2, NAME, OP, FUNC_NAME) \
  SCOPE mMatrix ## POSTFIX m_C( m_C( m ## FUNC_NAME, _ ## NAME ) , _M ## POSTFIX) ( \
    TYPE2 a, \
    mMatrix ## POSTFIX b \
  );
#define M__FUNCS_HEADER_mMatrixN__(TYPE, N, POSTFIX, SCOPE) \
  SCOPE mMatrix ## POSTFIX mAdd_M ## POSTFIX (mMatrix ## POSTFIX a, mMatrix ## POSTFIX b); \
  SCOPE mMatrix ## POSTFIX mMul_M ## POSTFIX (mMatrix ## POSTFIX a, mMatrix ## POSTFIX b); \
  SCOPE mVector ## POSTFIX m_C( mMul_M ## POSTFIX , _V ## POSTFIX ) (mMatrix ## POSTFIX mat , mVector ## POSTFIX vec ); \
  \
  M__DECLARE_OP_mMatrixN__(TYPE, N, POSTFIX, SCOPE, float, f, +, Add) \
  M__DECLARE_OP_mMatrixN__(TYPE, N, POSTFIX, SCOPE, double, d, +, Add) \
  M__DECLARE_OP_mMatrixN__(TYPE, N, POSTFIX, SCOPE, int, i, +, Add) \
  M__DECLARE_OP_mMatrixN__(TYPE, N, POSTFIX, SCOPE, unsigned int, ui, +, Add) \
                                                                              \
  M__DECLARE_OP_mMatrixN__(TYPE, N, POSTFIX, SCOPE, float, f, -, Sub) \
  M__DECLARE_OP_mMatrixN__(TYPE, N, POSTFIX, SCOPE, double, d, -, Sub) \
  M__DECLARE_OP_mMatrixN__(TYPE, N, POSTFIX, SCOPE, int, i, -, Sub) \
  M__DECLARE_OP_mMatrixN__(TYPE, N, POSTFIX, SCOPE, unsigned int, ui, -, Sub) \
                                                                              \
  M__DECLARE_OP_mMatrixN__(TYPE, N, POSTFIX, SCOPE, float, f, *, Mul) \
  M__DECLARE_OP_mMatrixN__(TYPE, N, POSTFIX, SCOPE, double, d, *, Mul) \
  M__DECLARE_OP_mMatrixN__(TYPE, N, POSTFIX, SCOPE, int, i, *, Mul) \
  M__DECLARE_OP_mMatrixN__(TYPE, N, POSTFIX, SCOPE, unsigned int, ui, *, Mul) \
  \
  SCOPE mVector ## POSTFIX mGet_Col_M ## POSTFIX ( uint64_t c, mMatrix ## POSTFIX matrix ); \
  SCOPE mVector ## POSTFIX mGet_Row_M ## POSTFIX ( uint64_t r, mMatrix ## POSTFIX matrix );

#define M__DECLARE_CONSTS_mMatrixN__(TYPE_NAME, SCOPE) \
  SCOPE const mMatrix2 ## TYPE_NAME m_C( mMatrix2 ## TYPE_NAME , _I ); \
  SCOPE const mMatrix3 ## TYPE_NAME m_C( mMatrix3 ## TYPE_NAME , _I ); \
  SCOPE const mMatrix4 ## TYPE_NAME m_C( mMatrix4 ## TYPE_NAME , _I );

#define M_HEADER_mMatrixN(TYPE, N, POSTFIX) \
  M__TYPES_HEADER_mMatrixN__(TYPE, N, POSTFIX) \
  M__FUNCS_HEADER_mMatrixN__(TYPE, N, POSTFIX, )

// ============
// Declarations
// ============

#ifndef M_NO_DEFAULTS

  M__TYPES_HEADER_mMatrixN__(float, 2, 2f)
  M__TYPES_HEADER_mMatrixN__(float, 3, 3f)
  M__TYPES_HEADER_mMatrixN__(float, 4, 4f)

  M__FUNCS_HEADER_mMatrixN__(float, 2, 2f, M__Matrix_SCOPE__)
  M__FUNCS_HEADER_mMatrixN__(float, 3, 3f, M__Matrix_SCOPE__)
  M__FUNCS_HEADER_mMatrixN__(float, 4, 4f, M__Matrix_SCOPE__)

  M__DECLARE_CONSTS_mMatrixN__(f, M__Matrix_SCOPE__)

#endif

// =============
// DEFINE Macros
// =============

#define M__SOURCE_OP_mMatrixN__(TYPE, N, POSTFIX, SCOPE, TYPE2, NAME, OP, FUNC_NAME) \
  SCOPE mMatrix ## POSTFIX m_C( m_C( m ## FUNC_NAME, _ ## NAME ) , _M ## POSTFIX) ( \
    TYPE2 a, \
    mMatrix ## POSTFIX b \
  ) { \
      \
    for (int i = 0; i < N; i++) { \
      for (int j = 0; j < N; j++) { \
        b.i[i][j] = b.i[i][j] OP a; \
      } \
    } \
      \
    return b; \
  }

#define M__SOURCE_mMatrixN__(TYPE, N, POSTFIX, SCOPE) \
  SCOPE mMatrix ## POSTFIX mAdd_M ## POSTFIX (mMatrix ## POSTFIX a, mMatrix ## POSTFIX b) { \
    mMatrix ## POSTFIX result; \
    for (uint64_t i = 0 ; i < N; i++) { \
      for (uint64_t j = 0; j < N; j++) { \
        result.i[i][j] = a.i[i][j] + b.i[i][j]; \
      } \
    } \
    return result; \
  } \
    \
  SCOPE mMatrix ## POSTFIX mMul_M ## POSTFIX (mMatrix ## POSTFIX a, mMatrix ## POSTFIX b) { \
    mMatrix ## POSTFIX result; \
    for (uint64_t i = 0; i < N; i++) { \
      for (uint64_t j = 0; j < N; j++) { \
                                         \
        result.i[i][j] = 0; \
        for (uint64_t k = 0; k < N; k++) { \
          result.i[i][j] += a.i[i][k] * b.i[k][j]; \
        } \
          \
      } \
    } \
      \
    return result; \
  } \
    \
  SCOPE mVector ## POSTFIX m_C( mMul_M ## POSTFIX , _V ## POSTFIX ) (mMatrix ## POSTFIX mat , mVector ## POSTFIX vec ) { \
    mVector ## POSTFIX result; \
    for (uint64_t i = 0; i < N; i++) { \
      result.i[i] = 0; \
      for (uint64_t j = 0; j < N; j++) { \
        result.i[i] += mat.i[i][j] * vec.i[j]; \
      } \
    } \
      \
    return result; \
  } \
    \
  M__SOURCE_OP_mMatrixN__(TYPE, N, POSTFIX, SCOPE, float, f, +, Add) \
  M__SOURCE_OP_mMatrixN__(TYPE, N, POSTFIX, SCOPE, double, d, +, Add) \
  M__SOURCE_OP_mMatrixN__(TYPE, N, POSTFIX, SCOPE, int, i, +, Add) \
  M__SOURCE_OP_mMatrixN__(TYPE, N, POSTFIX, SCOPE, unsigned int, ui, +, Add) \
                                                                             \
  M__SOURCE_OP_mMatrixN__(TYPE, N, POSTFIX, SCOPE, float, f, -, Sub) \
  M__SOURCE_OP_mMatrixN__(TYPE, N, POSTFIX, SCOPE, double, d, -, Sub) \
  M__SOURCE_OP_mMatrixN__(TYPE, N, POSTFIX, SCOPE, int, i, -, Sub) \
  M__SOURCE_OP_mMatrixN__(TYPE, N, POSTFIX, SCOPE, unsigned int, ui, -, Sub) \
                                                                             \
  M__SOURCE_OP_mMatrixN__(TYPE, N, POSTFIX, SCOPE, float, f, *, Mul) \
  M__SOURCE_OP_mMatrixN__(TYPE, N, POSTFIX, SCOPE, double, d, *, Mul) \
  M__SOURCE_OP_mMatrixN__(TYPE, N, POSTFIX, SCOPE, int, i, *, Mul) \
  M__SOURCE_OP_mMatrixN__(TYPE, N, POSTFIX, SCOPE, unsigned int, ui, *, Mul) \
                                                                             \
  SCOPE mVector ## POSTFIX mGet_Col_M ## POSTFIX ( uint64_t c, mMatrix ## POSTFIX matrix ) { \
    mVector ## POSTFIX result; \
    for (int i = 0; i < N; i++) { \
      result.i[i] = matrix.i[i][c]; \
    } \
      \
    return result; \
  } \
  SCOPE mVector ## POSTFIX mGet_Row_M ## POSTFIX ( uint64_t r, mMatrix ## POSTFIX matrix ) { \
    mVector ## POSTFIX result; \
    for (int i = 0; i < N; i++) { \
      result.i[i] = matrix.i[r][i]; \
    } \
      \
    return result; \
  }

#define M_SOURCE_mMatrixN(TYPE, N, POSTFIX) \
  M__SOURCE_mMatrixN__(TYPE, N, POSTFIX, )
#define M_STATIC_mMatrixN(TYPE, N, POSTFIX) \
  M__SOURCE_mMatrixN__(TYPE, N, POSTFIX, static)

// ===========
// Definitions
// ===========

#ifndef M_NO_DEFAULTS

  M__SOURCE_mMatrixN__(float, 2, 2f, M__Matrix_SCOPE__)
  M__SOURCE_mMatrixN__(float, 3, 3f, M__Matrix_SCOPE__)
  M__SOURCE_mMatrixN__(float, 4, 4f, M__Matrix_SCOPE__)

  #define M__DEFINE_CONSTS_mMatrixN__(TYPE_NAME, SCOPE) \
    SCOPE const mMatrix2 ## TYPE_NAME m_C( mMatrix2 ## TYPE_NAME , _I ) = { \
      .i = { {1, 0}, \
             {0, 1} } \
    }; \
    SCOPE const mMatrix3 ## TYPE_NAME m_C( mMatrix3 ## TYPE_NAME , _I ) = { \
      .i = { {1, 0, 0}, \
             {0, 1, 0}, \
             {0, 0, 1} } \
    }; \
    SCOPE const mMatrix4 ## TYPE_NAME m_C( mMatrix4 ## TYPE_NAME , _I ) = { \
      .i = { {1, 0, 0, 0}, \
             {0, 1, 0, 0}, \
             {0, 0, 1, 0}, \
             {0, 0, 0, 1} } \
    };

  M__DEFINE_CONSTS_mMatrixN__(f, M__Matrix_SCOPE__)

#endif

// ########
// Clean up
// ########

#undef M__DEFINE_CONSTS_mMatrixN__

#endif
