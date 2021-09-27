#ifndef M_Solve_H
#define M_Solve_H

#include <stdlib.h>
#include <stdint.h>

//d
#include <stdio.h>

static int mSolve_GAUSSIAN_ELIMINATION(const float* matrix, const float* vector, uint64_t m, uint64_t n, float* result) { //!!! MUST be n x n for now

  float* matrix_temp = malloc(m*n*sizeof(float));
  float* vector_temp = malloc(m*sizeof(float));

  const float** r_matrix = malloc(m*sizeof(float*));
  float** r_matrix_temp = malloc(m*sizeof(float*));
  for (uint64_t i = 0; i < m; i++) {
    r_matrix[i] = matrix + i*n;
    r_matrix_temp[i] = matrix_temp + i*n;
    vector_temp[i] = vector[i];
  }

  // Gaussian elimination
  for (uint64_t i = 0; i < m; i++) {
    // search for highest and swap
    uint64_t index_highest = i;
    for (uint64_t p = i+1; p < m; p++) {
      if (r_matrix[p][i] > r_matrix[index_highest][i]) {
        index_highest = p;
      }
    }
    const float* top_row_swap = r_matrix[i];
    r_matrix[i] = r_matrix[index_highest];
    r_matrix[index_highest] = top_row_swap;
    top_row_swap = r_matrix_temp[i];
    r_matrix_temp[i] = r_matrix_temp[index_highest];
    r_matrix_temp[index_highest] = (float*) top_row_swap; //? not undefined to cast away const when set earlier to non-const ?
    float top_vector_entry = vector_temp[i];
    vector_temp[i] = vector_temp[index_highest];
    vector_temp[index_highest] = top_vector_entry;

    // make row echelon form
    for (uint64_t j = i+1; j < m; j++) {

      for (uint64_t k = i; k < n; k++) {
        r_matrix_temp[j][k] = r_matrix[j][k] - r_matrix[i][k] * r_matrix[j][i]/r_matrix[i][i];
      }
      vector_temp[j] = vector_temp[j] - vector_temp[i] * r_matrix[j][i]/r_matrix[i][i];

    }
  }
  // copy in first row of rearranged matrix
  for (uint64_t j = 0; j < n; j++) {
    r_matrix_temp[0][j] = r_matrix[0][j];
  }

  // solve for result
  for (uint64_t i = m-1 ;; i--) {

    result[i] = vector_temp[i];
    for (uint64_t j = i+1; j < n; j++) {
      result[i] -= r_matrix_temp[i][j] * result[j];
    }
    result[i] /= r_matrix_temp[i][i];

    if (i == 0) {
      break;
    }
  }

  free(r_matrix);
  free(r_matrix_temp);
  free(matrix_temp);
  free(vector_temp);

  return 1;

}


#endif

/*

static int mSolve_GAUSSIAN_ELIMINATION(const float* matrix, const float* vector, uint64_t m, uint64_t n, float* result) { //!!! MUST be n x n for now

  const float** r_matrix = malloc(m*sizeof(float*));
  for (uint64_t i = 0; i < m; i++) {
    r_matrix[i] = matrix + i*n;
  }

  float* matrix_temp = malloc(m*n*sizeof(float));
  float* vector_temp = malloc(n*sizeof(float));
  for (uint64_t j = 0; j < n; j++) {
    matrix_temp[0*n + j] = matrix[0*n + j];
  }
  vector_temp[0] = vector[0];

  for (uint64_t i = 0; i < m; i++) {
    // search for highest


    // make row echelon form
    for (uint64_t j = i+1; j < m; j++) {

      for (uint64_t k = i; k < n; k++) {
        matrix_temp[j*n + k] = matrix[j*n + k] - matrix[i*n + k] * matrix[(i+1)*n + i]/matrix[i*n + i];
      }
      vector_temp[j] = vector[j] - vector[i] * matrix[(i+1)*n + i]/matrix[i*n + i];

    }
  }

  for (uint64_t i = m-1 ;; i--) {

    result[i] = vector_temp[i];
    for (uint64_t j = i+1; j < n; j++) {
      result[i] -= matrix_temp[i*n + j] * result[j];
    }
    result[i] /= matrix_temp[i*n + i];

    if (i == 0) {
      break;
    }
  }

  free(r_matrix);
  free(matrix_temp);
  free(vector_temp);

  return 1;

}

static int mSolve_GAUSSIAN_ELIMINATION(const float* matrix, const float* vector, uint64_t m, uint64_t n, float* result) { //!!! MUST be n x n for now

  float* matrix_temp = malloc(m*n*sizeof(float));
  float* vector_temp = malloc(n*sizeof(float));
  for (uint64_t j = 0; j < n; j++) {
    matrix_temp[0*n + j] = matrix[0*n + j];
  }
  vector_temp[0] = vector[0];

  for (uint64_t i = 0; i < m; i++) {
    // search for highest


    // make row echelon form
    for (uint64_t j = i+1; j < m; j++) {

      for (uint64_t k = i; k < n; k++) {
        matrix_temp[j*n + k] = matrix[j*n + k] - matrix[i*n + k] * matrix[(i+1)*n + i]/matrix[i*n + i];
      }
      vector_temp[j] = vector[j] - vector[i] * matrix[(i+1)*n + i]/matrix[i*n + i];

    }
  }

  for (uint64_t i = m-1 ;; i--) {

    result[i] = vector_temp[i];
    for (uint64_t j = i+1; j < n; j++) {
      result[i] -= matrix_temp[i*n + j] * result[j];
    }
    result[i] /= matrix_temp[i*n + i];

    if (i == 0) {
      break;
    }
  }

  free(matrix_temp);
  free(vector_temp);

  return 1;

}

*/
