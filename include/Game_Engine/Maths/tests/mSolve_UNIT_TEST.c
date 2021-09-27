#include "../mSolve.h"

#include <stdio.h>

#define TEST_N 3

int main() {

  float test_matrix[TEST_N*TEST_N] = { 0, 0, 1 ,
                                       4.7, 0, 1 ,
                                       0, 6, 0 };
  float test_vector[TEST_N] = {1,2,3};
  float test_result[TEST_N];

  printf("%d\n", mSolve_GAUSSIAN_ELIMINATION(test_matrix, test_vector, TEST_N,TEST_N, test_result));

  for (int i = 0; i < TEST_N; i++) {
    printf("%f\n", test_result[i]);
  }

  printf("\nPROGRAM ENDING_SUCCESSFULLY\n");

  return 0;
}
