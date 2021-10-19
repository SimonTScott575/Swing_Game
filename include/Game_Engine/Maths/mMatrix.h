#ifndef M_MATRIX_H
#define M_MATRIX_H

#include <stdint.h>

#include "m_common.h"
#include "mVector.h"

#ifndef M_SCOPE
  #if defined(M_AS_HEADER)
    #define M_SCOPE extern
  #elif defined(M_AS_SOURCE)
    #define M_SCOPE
  #else
    #define M_SCOPE static
  #endif
#endif

#define mMatrix(M,N,TYPE) M_PASTE5( mMatrix__,M,__,N, M_PASTE3(__,TYPE,__) )

#define M_HEADER_MATRIX(TYPE, N, POSTFIX) \
  typedef struct mMatrix(N,N,TYPE) { TYPE i[N][N]; } mMatrix(N,N,TYPE);

#define M_SOURCE_MATRIX(TYPE, N, POSTFIX) \
                                          \
  M_SCOPE \
  mMatrix(N,N,TYPE) M_PASTE(mAdd_M, POSTFIX) ( \
    mMatrix(N,N,TYPE) a, \
    mMatrix(N,N,TYPE) b \
  ) { \
      \
    mMatrix(N,N,TYPE) result; \
    for (int i = 0; i < N; i++) { \
    for (int j = 0; j < N; j++) { \
      result.i[i][j] = a.i[i][j] + b.i[i][j]; \
    } \
    } \
      \
    return result; \
                   \
  } \
    \
  M_SCOPE \
  mMatrix(N,N,TYPE) M_PASTE(mSub_M, POSTFIX) ( \
    mMatrix(N,N,TYPE) a, \
    mMatrix(N,N,TYPE) b \
  ) { \
      \
    mMatrix(N,N,TYPE) result; \
    for (int i = 0; i < N; i++) { \
    for (int j = 0; j < N; j++) { \
      result.i[i][j] = a.i[i][j] - b.i[i][j]; \
    } \
    } \
      \
    return result; \
                   \
  } \
    \
  M_SCOPE \
  mMatrix(N,N,TYPE) M_PASTE(mMul_M, POSTFIX) ( \
    mMatrix(N,N,TYPE) a, \
    mMatrix(N,N,TYPE) b \
  ) { \
      \
    mMatrix(N,N,TYPE) result; \
    for (int i = 0; i < N; i++) { \
      for (int j = 0; j < N; j++) { \
                                    \
        result.i[i][j] = 0; \
        for (int k = 0; k < N; k++) { \
          result.i[i][j] += a.i[i][k]*b.i[k][j]; \
        } \
          \
      } \
    } \
      \
    return result; \
                   \
  } \
    \
  M_SCOPE \
  mVector(N,TYPE) M_PASTE3(mMul_M, POSTFIX, M_PASTE(_V,POSTFIX)) ( \
    mMatrix(N,N,TYPE) a, \
    mVector(N,TYPE) b \
  ) { \
      \
    mVector(N,TYPE) result; \
    for (int i = 0; i < N; i++) { \
      result.i[i] = 0; \
      for (int j = 0; j < N; j++) { \
        result.i[i] += a.i[i][j]*b.i[j]; \
      } \
    } \
      \
    return result; \
                   \
  } \
    \
  M_SCOPE \
  mMatrix(N,N,TYPE) M_PASTE( mMul_f , M_PASTE(_M,POSTFIX) ) ( \
    float a, \
    mMatrix(N,N,TYPE) b \
  ) { \
      \
    for (int i = 0; i < N; i++) { \
    for (int j = 0; j < N; j++) { \
        b.i[i][j] *= a; \
    } \
    } \
      \
    return b; \
              \
  } \
    \
  M_SCOPE \
  mVector(N,TYPE) M_PASTE(mGet_Col_M, POSTFIX) ( \
    int n, \
    mMatrix(N,N,TYPE) m \
  ) { \
      \
    mVector(N,TYPE) result; \
    for (int i = 0; i < N; i++) { \
      result.i[i] = m.i[i][n]; \
    } \
      \
    return result; \
                   \
  } \
  \
  M_SCOPE \
  mVector(N,TYPE) M_PASTE(mGet_Row_M, POSTFIX) ( \
    int n, \
    mMatrix(N,N,TYPE) m \
  ) { \
      \
    mVector(N,TYPE) result; \
    for (int i = 0; i < N; i++) { \
      result.i[i] = m.i[n][i]; \
    } \
      \
    return result; \
                   \
  }

M_HEADER_MATRIX(float, 2, 2f);
M_HEADER_MATRIX(float, 3, 3f);
M_HEADER_MATRIX(float, 4, 4f);

M_SOURCE_MATRIX(float, 2, 2f);
M_SOURCE_MATRIX(float, 3, 3f);
M_SOURCE_MATRIX(float, 4, 4f);

#define mMatrix2(float) mMatrix(2,2,float)
#define mMatrix3(float) mMatrix(3,3,float)
#define mMatrix4(float) mMatrix(4,4,float)

/*** LEGACY ***/
#define mMatrix2f mMatrix(2,2,float)
#define mMatrix3f mMatrix(3,3,float)
#define mMatrix4f mMatrix(4,4,float)
/**************/

static const mMatrix2f mMatrix2f_I = {
  .i = { {1, 0},
         {0, 1} }
};
static const mMatrix3f mMatrix3f_I = {
  .i = { {1, 0, 0},
         {0, 1, 0},
         {0, 0, 1} }
};
static const mMatrix4f mMatrix4f_I = {
  .i = { {1, 0, 0, 0},
         {0, 1, 0, 0},
         {0, 0, 1, 0},
         {0, 0, 0, 1} }
};

#endif
