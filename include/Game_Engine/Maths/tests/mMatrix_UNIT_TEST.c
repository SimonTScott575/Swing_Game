#include "../mMatrix.h"

#include <stdio.h>
#include <stdint.h>

int arrays_equal(float* a, float* b, int n) {
  for (int i = 0; i < n; i++) {
    if (a[i] != b[i]) {
      return 1;
    }
  }

  return 0;
}
int matrices2x2_equal(float a[][2], float b[][2]) {
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      if (a[i][j] != b[i][j]) {
        return 1;
      }
    }
  }

  return 0;
}

M_HEADER_mVector(uint8_t, 5, ui8);
M_SOURCE_mVector(uint8_t, 5, ui8);
M_HEADER_mMatrixN(uint8_t, 5, ui8);
M_SOURCE_mMatrixN(uint8_t, 5, ui8);

int main() {

  mMatrix2f test_matrix = { .i = { {0,1},
                                   {3.14f, 2.71f} } };
  mMatrix2f test_matrix_2 = { .i = { {7,8},
                                     {1.23f, 2.34f} } };

  // Add
  printf("\nAdd Test\n");
  mMatrix2f test_add_result = mAdd_M2f(test_matrix, test_matrix_2);
  float test_add_expected[2][2] = { {0+7, 1+8}, {3.14f+1.23f, 2.71f+2.34f} };
  printf("%d Contents test\n", matrices2x2_equal(test_add_result.i, test_add_expected));

  // Mul
  printf("\nMul Test\n");
  mMatrix2f test_mul_result = mMul_M2f(test_matrix, test_matrix_2);
  float test_mul_expected[2][2] = { {0*7 + 1*1.23f, 0*8 + 1*2.34f}, {3.14f*7 + 2.71f*1.23f, 3.14f*8 + 2.71f*2.34f} };
  printf("%d Contents test\n", matrices2x2_equal(test_mul_result.i, test_mul_expected));

  // Add f
  printf("\nAdd f Test\n");
  mMatrix2f test_add_f_result = mAdd_f_M2f(1001, test_matrix);
  float test_add_f_expected[2][2] = { {0+1001, 1+1001}, {3.14f+1001, 2.71f+1001} };
  printf("%d Contents test\n", matrices2x2_equal(test_add_f_result.i, test_add_f_expected));

  // Mul f
  printf("\nMul f Test\n");
  mMatrix2f test_mul_f_result = mMul_f_M2f(1001, test_matrix);
  float test_mul_f_expected[2][2] = { {0*1001, 1*1001}, {3.14f*1001, 2.71f*1001} };
  printf("%d Contents test\n", matrices2x2_equal(test_mul_f_result.i, test_mul_f_expected));

  // Get col
  printf("\nGet col TEST\n");
  mVector2f test_col_result = mGet_Col_M2f(0, test_matrix);
  float test_col_expected[] = { 0, 3.14f };
  printf("%d Contents\n", arrays_equal(test_col_result.i, test_col_expected, 2));

  // Get row
  printf("\nGet row TEST\n");
  mVector2f test_row_result = mGet_Row_M2f(1, test_matrix);
  float test_row_expected[] = { 3.14f, 2.71f };
  printf("%d Contents\n", arrays_equal(test_row_result.i, test_row_expected, 2));

  // User defined
  printf("\nUser defined\n");
  mMatrixui8 user_m = { .i = { {1,2,3,4,255}, {6,7,8,9,10}, {6,7,8,9,10}, {6,7,8,9,10}, {6,7,8,9,10} } };
  printf("%d test\n", (uint8_t) (user_m.i[4][4] + 1) != 11 );

  printf("\nPROGRAM ENDING SUCCESSFULLY\n");

  return 0;
}
