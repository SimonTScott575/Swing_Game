#include "../dPtr.h"

#include <stdio.h>
#include <stdlib.h>

typedef int test_type;
typedef float test_type2;
D_DEFINE_dPtr(test_type* _test_type; test_type2* _test_type2; ,
              testPtr)

int main() {

  dPtr test_ptr;
  int a = 101;
  testPtr test_ptr2;
  test_type2 b = 3.14f;

  test_ptr._int = &a;
  printf("%d value test\n", *test_ptr._int != a);
  printf("%d address test\n", test_ptr._int != &a);

  test_ptr2._test_type2 = &b;
  printf("%d value test\n", *test_ptr2._test_type2 != b);
  printf("%d address test\n", test_ptr2._test_type2 != &b);

  printf("\nPROGRAM ENDING SUCCESSFULLY\n");

  return 0;
}
