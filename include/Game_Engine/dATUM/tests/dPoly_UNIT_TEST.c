#include "../dPoly.h"

#include <stdio.h>

typedef int test_type;
typedef float test_type2;
D_HEADER_dPoly(
  test_type _test_type; test_type2 _test_type2; ,
  testPoly
)

int main() {

  dPoly test_poly;
  int a = 1;
  testPoly test_poly2;

  test_poly._int = a;
  printf("%d value test\n", test_poly._int != a);

  test_poly2._test_type2 = 3.14f;
  printf("%d value_test\n", test_poly2._test_type2 != 3.14f);

  return 0;
}
