#include "../dArr.h"

#include <stdio.h>

int not_equal_to_array(dArri* Arr, int* array, uint64_t length) {
  for (int i = 0; i < length; i++) {
    if (Arr->i[i] != array[i]) {
      return 1;
    }
  }
  return 0;
}

typedef double Test_Type;
D_HEADER_dArr(Test_Type, TT)
D_SOURCE_dArr(Test_Type, TT)

int main() {

  int test_contents[] = {0,1,2,3,4,5,6,7,8};
  dArri* test_arr = new_dArri(9, test_contents);

  printf("Array new with NULL\n");
  dArri* arr_with_null = new_dArri(5, NULL);
  int contents_of_arr_with_null[] = {0,1,2,3,4};
  for (int i = 0; i < 5; i++) {
    arr_with_null->i[i] = contents_of_arr_with_null[i];
  }

  printf("%d Length\n", 5 != arr_with_null->length);
  printf("%d Contents\n", not_equal_to_array(arr_with_null, contents_of_arr_with_null, 5));
  printf("\n");

  printf("Array new with not NULL\n");
  int array_init_values[5] = {6,7,8,9,10};
  dArri* arr_no_null = new_dArri(5, array_init_values);

  printf("%d Length\n", 5 != arr_with_null->length);
  printf("%d Contents\n", not_equal_to_array(arr_no_null, array_init_values, 5));

  // ----------
  // Set_length
  // ----------

  printf("\t%d Set_length 6 return\n", dSet_length_Ai(6, test_arr));
  printf("%d Length\n", 6 != test_arr->length);
  printf("%d Contents\n", not_equal_to_array(test_arr, test_contents, 6));

  printf("\t%d Set_length 15 return\n", dSet_length_Ai(15, test_arr));
  printf("%d Length\n", 15 != test_arr->length);

  //? Fill, copy into from array and/or dArr ? Set ?


  printf("\nDEBUG : PROGRAM ENDING SUCCESSFULLY\n");

  return 0;
}
