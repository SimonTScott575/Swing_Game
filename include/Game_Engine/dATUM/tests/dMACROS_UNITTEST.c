#include <stdio.h>

#include "../dMACROS.h"

#define A 1
#define B 2
#define C D_CONCAT_M(A, B)

#define X 8
#define Y 9
#define Z D_CONCAT_DEF(X, Y)

#define E qwerty

int main() {
  // =========
  // Stringify
  // =========

  printf("\n%s", D_STR_M(E));
  printf("\n%s", D_STR_DEF(E));

  char* qwop = "zxnm";
  printf("\n%s %s", D_STR_M(qwop), D_STR_DEF(qwop));

  // ===========
  // Concatenate
  // ===========

  int AB = 555;
  printf("\n%d", C); // !!! Without `int AB = 555` you should get compile time error !!!

  printf("\n%d", Z);

  int abc = 999;
  printf("\n%d %d", D_CONCAT_M(a, bc), D_CONCAT_DEF(a, bc)); // !!! Without `int abc = 999` you should get compile time error !!!

  return 0;
}
