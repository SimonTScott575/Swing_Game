#include "mSolve.h"

int mSolve_GAUSSIAN_ELIMINATION(float* matrix, uint64_t m, uint64_t n, float* result) { //!!! MUST be n x n for now
  float** rows = malloc(m*sizeof(float*));

  for (uint64_t i = 0; i < m; i++) {
    for (uint64_t j = i+1; j < m; j++) {

      for (uint64_t k = i; k < n; k++) {
        matrix[j*m + k] -= matrix[i*m + k] / matrix[i*m + i]
      }

    }
  }

  free(rows);
}
