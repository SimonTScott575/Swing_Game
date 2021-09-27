#include "../mFrame.h"

#include <stdio.h>

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

int main() {

  mFrame2D a = init_mFrame2D(mVector2f_ZERO, 0, mVector2f_ONE);

  printf("\n!!! TEST NOT COMPLETE !!!\n");

  // // Add
  // printf("\nAdd Test\n");
  // mMatrix2f test_add_result = mAdd_M2f(test_matrix, test_matrix_2);
  // float test_add_expected[2][2] = { {0+7, 1+8}, {3.14f+1.23f, 2.71f+2.34f} };
  // printf("%d Contents test\n", matrices2x2_equal(test_add_result.i, test_add_expected));

  printf("\nPROGRAM ENDING SUCCESSFULLY\n");

  return 0;
}
