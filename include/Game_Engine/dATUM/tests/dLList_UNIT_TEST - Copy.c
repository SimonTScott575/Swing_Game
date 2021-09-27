#include "../dLList.h"

#include <stdio.h>

#define TEST_LIST_LENGTH 3

int test_contents_LLi(dLListi* llist, int* contents) {
  dLListi_Node* current = llist->start;
  int i = 0;
  while (current != NULL) {
    if (current->element != contents[i]) {
      return 1;
    }
    i++;
    current = current->next;
    if (current == llist->start) {
      break;
    }
  }

  return 0;
}
int test_length_LLi(dLListi* llist, int expected_length) {
  if (llist->start == NULL) {
    if (expected_length != 0) {
      return 1;
    }
    return 0;
  }

  dLListi_Node* current = llist->start;
  int count = 1;
  while (current->next != NULL && current->next != llist->start) {
    current = current->next;
    count += 1;
  }
  if (count != expected_length) {
    return 1;
  }

  return 0;
}
int test_proper_LLi(dLListi* llist) {
  if (llist->start != llist->end && (llist->start == NULL || llist->end == NULL)) {
    return 1;
  }
  if (llist->start == NULL) {
    return 0;
  }

  dLListi_Node* current = llist->start;
  while (current->next != NULL && current->next != llist->start) {
    if (current->prev != NULL && current->next != NULL) {
      if (current->next->prev != current->prev->next || current->next->prev != current) {
        return 1;
      }
    }
    current = current->next;
  }

  return 0;
}

struct test_struct {
  float a;
};
D_HEADER_dLList(struct test_struct , TS);
D_SOURCE_dLList(struct test_struct , TS);

int main() {

  int test_list_intended_contents[TEST_LIST_LENGTH] = { 1, 2, 3 };
  dLListi* test_list = new_dLListi(TEST_LIST_LENGTH, test_list_intended_contents);
  dLListi_Node* test_list_Node;

  printf("%d Contents\n", test_contents_LLi(test_list, test_list_intended_contents));
  printf("%d Proper\n", test_proper_LLi(test_list));
  printf("%d Length\n", test_length_LLi(test_list, TEST_LIST_LENGTH));
  printf("\n");

  // -----------
  // Circularise
  // -----------

  printf("Circularise Test\n");
  dCircularise_LLi(test_list);

  printf("%d Contents\n", test_contents_LLi(test_list, test_list_intended_contents));
  printf("%d Proper\n", test_proper_LLi(test_list));
  printf("%d Length\n", test_length_LLi(test_list, TEST_LIST_LENGTH));
  printf("%d Endpoints\n", test_list->start->prev != test_list->end || test_list->start != test_list->end->next);
  printf("\n");

  // ---------
  // Linearise
  // ---------

  printf("Linearise Test\n");
  dLinearise_LLi(test_list);

  printf("%d Contents\n", test_contents_LLi(test_list, test_list_intended_contents));
  printf("%d Proper\n", test_proper_LLi(test_list));
  printf("%d Length\n", test_length_LLi(test_list, TEST_LIST_LENGTH));
  printf("%d Endpoints\n", test_list->start->prev != NULL || NULL != test_list->end->next);
  printf("\n");

  // --------------
  // Append/Prepend
  // --------------

  printf("Append Test\n");
  dAppend_LLi(300, test_list);
  int append_expected_contents[TEST_LIST_LENGTH+1] = {1,2,3,300};

  printf("%d Contents\n", test_contents_LLi(test_list, append_expected_contents));
  printf("%d Proper\n", test_proper_LLi(test_list));
  printf("%d Length\n", test_length_LLi(test_list, TEST_LIST_LENGTH + 1));
  printf("\n");

  printf("Prepend Test\n");
  dPrepend_LLi(101, test_list);
  int prepend_expected_contents[TEST_LIST_LENGTH+2] = {101, 1,2,3,300};

  printf("%d Contents\n", test_contents_LLi(test_list, prepend_expected_contents));
  printf("%d Proper\n", test_proper_LLi(test_list));
  printf("%d Length\n", test_length_LLi(test_list, TEST_LIST_LENGTH + 2));
  printf("\n");

  // ------
  // Insert
  // ------

  printf("Insert_Before Test\n");
  dInsert_Before_LLi(999, test_list->start->next->next, test_list);
  int insert_before_expected_contents[TEST_LIST_LENGTH+3] = { 101, 1, 999, 2, 3, 300 };

  printf("%d Contents\n", test_contents_LLi(test_list, insert_before_expected_contents));
  printf("%d Proper\n", test_proper_LLi(test_list));
  printf("%d Length\n", test_length_LLi(test_list, TEST_LIST_LENGTH + 3));
  printf("\n");

  printf("Insert_Before Test 2\n");
  dInsert_Before_LLi(555, test_list->start, test_list);
  int insert_before_expected_contents_2[TEST_LIST_LENGTH+4] = { 555, 101, 1, 999, 2, 3, 300 };

  printf("%d Contents\n", test_contents_LLi(test_list, insert_before_expected_contents_2));
  printf("%d Proper\n", test_proper_LLi(test_list));
  printf("%d Length\n", test_length_LLi(test_list, TEST_LIST_LENGTH + 4));
  printf("\n");

  printf("Insert_Before Test 3\n");
  dInsert_Before_LLi(666, test_list->end, test_list);
  int insert_before_expected_contents_3[TEST_LIST_LENGTH+5] = { 555, 101, 1, 999, 2, 3, 666, 300 };

  printf("%d Contents\n", test_contents_LLi(test_list, insert_before_expected_contents_3));
  printf("%d Proper\n", test_proper_LLi(test_list));
  printf("%d Length\n", test_length_LLi(test_list, TEST_LIST_LENGTH + 5));
  printf("\n");

  printf("Insert_After Test\n");
  dInsert_After_LLi(777, test_list->start->next->next, test_list);
  int insert_after_expected_contents[TEST_LIST_LENGTH+6] = { 555, 101, 1, 777, 999, 2, 3, 666, 300 };

  printf("%d Contents\n", test_contents_LLi(test_list, insert_after_expected_contents));
  printf("%d Proper\n", test_proper_LLi(test_list));
  printf("%d Length\n", test_length_LLi(test_list, TEST_LIST_LENGTH + 6));
  printf("\n");

  printf("Insert_After Test 2\n");
  dInsert_After_LLi(888, test_list->start, test_list);
  int insert_after_expected_contents_2[TEST_LIST_LENGTH+7] = { 555, 888, 101, 1, 777, 999, 2, 3, 666, 300 };

  printf("%d Contents\n", test_contents_LLi(test_list, insert_after_expected_contents_2));
  printf("%d Proper\n", test_proper_LLi(test_list));
  printf("%d Length\n", test_length_LLi(test_list, TEST_LIST_LENGTH + 7));
  printf("\n");

  printf("Insert_After Test 3\n");
  dInsert_After_LLi(999, test_list->end, test_list);
  int insert_after_expected_contents_3[TEST_LIST_LENGTH+8] = { 555, 888, 101, 1, 777, 999, 2, 3, 666, 300, 999 };

  printf("%d Contents\n", test_contents_LLi(test_list, insert_after_expected_contents_3));
  printf("%d Proper\n", test_proper_LLi(test_list));
  printf("%d Length\n", test_length_LLi(test_list, TEST_LIST_LENGTH + 8));
  printf("\n");

  // ------
  // Remove
  // ------

  printf("Remove Test 1\n");
  dRemove_LLi(test_list->start->next->next, test_list);
  int remove_expected_contents_1[TEST_LIST_LENGTH+7] = { 555, 888, 1, 777, 999, 2, 3, 666, 300, 999 };

  printf("%d Contents\n", test_contents_LLi(test_list, remove_expected_contents_1));
  printf("%d Proper\n", test_proper_LLi(test_list));
  printf("%d Length\n", test_length_LLi(test_list, TEST_LIST_LENGTH + 7));
  printf("\n");

  printf("Remove Test 2\n");
  dRemove_LLi(test_list->start, test_list);
  int remove_expected_contents_2[TEST_LIST_LENGTH+6] = { 888, 1, 777, 999, 2, 3, 666, 300, 999 };

  printf("%d Contents\n", test_contents_LLi(test_list, remove_expected_contents_2));
  printf("%d Proper\n", test_proper_LLi(test_list));
  printf("%d Length\n", test_length_LLi(test_list, TEST_LIST_LENGTH + 6));
  printf("\n");

  printf("Remove Test 3\n");
  dRemove_LLi(test_list->end, test_list);
  int remove_expected_contents_3[TEST_LIST_LENGTH+5] = { 888, 1, 777, 999, 2, 3, 666, 300 };

  printf("%d Contents\n", test_contents_LLi(test_list, remove_expected_contents_3));
  printf("%d Proper\n", test_proper_LLi(test_list));
  printf("%d Length\n", test_length_LLi(test_list, TEST_LIST_LENGTH + 5));
  printf("\n");

  printf("Remove Test 4\n");
  dCircularise_LLi(test_list);
  dRemove_LLi(test_list->start, test_list);
  int remove_expected_contents_4[TEST_LIST_LENGTH+4] = { 1, 777, 999, 2, 3, 666, 300 };

  printf("%d Contents\n", test_contents_LLi(test_list, remove_expected_contents_4));
  printf("%d Proper\n", test_proper_LLi(test_list));
  printf("%d Length\n", test_length_LLi(test_list, TEST_LIST_LENGTH + 4));
  printf("\n");

  printf("Remove Test 5\n");
  dRemove_LLi(test_list->end, test_list);
  int remove_expected_contents_5[TEST_LIST_LENGTH+3] = { 1, 777, 999, 2, 3, 666 };

  printf("%d Contents\n", test_contents_LLi(test_list, remove_expected_contents_5));
  printf("%d Proper\n", test_proper_LLi(test_list));
  printf("%d Length\n", test_length_LLi(test_list, TEST_LIST_LENGTH + 3));
  printf("\n");

  dLinearise_LLi(test_list);

  // ---
  // del
  // ---

  printf("del Test 1\n");
  del_dLListi(test_list);
  printf("\n");

  printf("del Test 2\n");
  test_list = new_dLListi(TEST_LIST_LENGTH, test_list_intended_contents);
  dCircularise_LLi(test_list);
  del_dLListi(test_list);
  printf("\n");

  // -----------------
  // user defined test
  // -----------------

  printf("User defined Test\n");
  dLListTS* user_LL = new_dLListTS(0, NULL);
  struct test_struct test_ts = { .a = 3.14f };
  dAppend_LLTS(test_ts, user_LL);
  test_ts.a = 2.17f;
  dPrepend_LLTS(test_ts, user_LL);
  printf("%d\n", user_LL->start->element.a != 2.17f || user_LL->end->element.a != 3.14f);

  del_dLListTS(user_LL);

  printf("\nDEBUG : PROGRAM ENDING SUCCESSFULLY\n");

  return 0;
}
