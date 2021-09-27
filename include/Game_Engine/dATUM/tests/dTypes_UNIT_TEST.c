#include "../dTypes.h"

#include <stdio.h>

typedef int test_type;
D_HEADER_dType(float,
               testType _test_type; float _test_type2; ,
               testType)

int main() {

  struct testTypes testTypes = {
    ._test_type = 101,
    ._test_type2 = 3.14f
  };

  printf("%d const values test\n", dTypes._uint != 0 || dTypes._double != 11); // || dTypes._dPtr != 16);
  printf("%d user define test\n", testTypes._test_type != 101 || testTypes._test_type2 != 3.14f);

  printf("\nPROGRAM ENDING SUCCESSFULLY\n");

  return 0;
}
