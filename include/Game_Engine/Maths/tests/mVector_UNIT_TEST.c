#include "../mVector.h"

#include <stdio.h>
#include <stdint.h>

int arrays_equal(const float* a, const float* b, int n) {
  for (int i = 0; i < n; i++) {
    if (a[i] != b[i]) {
      return 1;
    }
  }

  return 0;
}

M_HEADER_mVector(uint8_t, 5, ui8)
M_SOURCE_mVector(uint8_t, 5, ui8)

int main() {

  mVector3f test_vector = { .i = {1,2,3} };
  mVector3f test_vector_2 = { .i = { 3.14f, 2.71f, 101 } };

  // Add
  printf("\nAdd Test\n");
  mVector3f test_add_result = mAdd_V3f(test_vector, test_vector_2);
  float test_add_expected[] = {1+3.14f, 2+2.71f, 3+101};
  printf("%d Contents\n", arrays_equal(test_add_result.i, test_add_expected, 3));
  printf("\n");

  // Add f
  printf("\nAdd f Test\n");
  mVector3f test_add_f_result = mAdd_f_V3f(3.33f, test_vector_2);
  float test_add_f_expected[] = {3.33f+3.14f, 3.33f+2.71f, 3.33f+101};
  printf("%d Contents\n", arrays_equal(test_add_f_result.i, test_add_f_expected, 3));
  printf("\n");

  // Mul f
  printf("\nMul f Test\n");
  mVector3f test_mul_f_result = mMul_f_V3f(2.3f, test_vector_2);
  float test_mul_f_expected[] = { 2.3f*3.14f , 2.3f*2.71f, 2.3f*101 };
  printf("%d Contents\n", arrays_equal(test_mul_f_expected, test_mul_f_result.i, 3));
  printf("\n");

  // Dot
  printf("\nDot Test\n");
  float test_dot_result = mDot_V3f(test_vector, test_vector_2);
  float test_dot_expected = 1*3.14f + 2*2.71f + 3*101;
  printf("%d Dot test\n", test_dot_expected != test_dot_result);
  printf("\n");

  // Cross
  printf("\nCross Test\n");
  mVector3f test_cross_result = mCross_V3f(test_vector, test_vector_2);
  float test_cross_expected[] = { 2*101 - 2.71f*3, 3*3.14f - 1*101, 1*2.71f - 3.14f*2 };
  printf("%d Contents\n", arrays_equal(test_cross_result.i, test_cross_expected, 3));
  printf("\t%f %f Dot product results\n", mDot_V3f(test_vector, test_cross_result), // slight discrepency at 5 decimal places, possible floating point rounding error
                                          mDot_V3f(test_vector_2, test_cross_result));
  printf("\n");

  // Consts
  printf("\nConsts Test\n");
  float expected_V3f_Y[3] = {0,1,0};
  printf("%d Contents", arrays_equal(expected_V3f_Y, mVector3f_Y.i, 3));
  printf("\n");

  // User defined
  printf("\nUser defined\n");
  mVectorui8 user_v = { .i = {1,2,3,4,255} };
  printf("%d overflow test\n", (uint8_t) (user_v.i[4] + 1) != 0 );


  printf("\nPROGRAM ENDING SUCCESSFULLY\n");

  return 0;
}
