#include "../dSort.h"

#include <stdio.h>

bool LTE_i(void* a, void* b) {
  return *(int*) a <= *(int*) b;
}
void assign_i(void* a, void* b) {
  int * result = a;
  *result = *(int*) b;
}
void* incr_i(void* array, uint64_t n) {
  return (int*) array + n;
}

int main() {

  int a[] = { 7, 3, 5, 7, 1, 2, 23, 9 }; //{5,4,3,2,1,0,-1,-2}; // { 7, 3, 5, 7, 1, 2, 23, 9 };; //
  int b[8];
  dSort_INSERTION(a, b, 8, LTE_i, assign_i, incr_i);
  for (int i = 0; i < 8; i++) {
    printf("%d\n", b[i]);
  }

  printf("\nPROGRAM ENDING SUCCESSFULLY\n");

  return 0;
}
