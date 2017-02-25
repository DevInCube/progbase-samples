#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include <check.h>
#include "module.h"

START_TEST (min_emptyList_errnoErrorListEmpty)
{
	List * list = List_new();
	(void)Module_min(list);
	ck_assert_int_eq(errno, MODULE_ERR_LIST_EMPTY);
}
END_TEST

START_TEST (min_oneValue_returnsThatOneValue)
{
	const int testValue = 3;
	List * list = List_new();
	List_add(list, (int *)&testValue);
	ck_assert_int_eq(Module_min(list), testValue);
}
END_TEST

START_TEST (min_someValues_returnsMinimum)
{
	int values[] = {5, -13, 0};
	const int testValue = values[1];
	List * list = List_new();
	for (int i = 0; i < 3; i++) {
		List_add(list, &values[i]);
	}
	ck_assert_int_eq(Module_min(list), testValue);
}
END_TEST




Suite *test_suite() {
  Suite *s = suite_create("Module");
  TCase *tc_sample;

  tc_sample = tcase_create("TestCase");
  tcase_add_test(tc_sample, min_emptyList_errnoErrorListEmpty);
  tcase_add_test(tc_sample, min_oneValue_returnsThatOneValue);
  tcase_add_test(tc_sample, min_someValues_returnsMinimum);

  suite_add_tcase(s, tc_sample);

  return s;
}

int main() {
  Suite *s = test_suite();
  SRunner *sr = srunner_create(s);
  srunner_set_fork_status(sr, CK_NOFORK);

  srunner_run_all(sr, CK_VERBOSE);

  int num_tests_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return num_tests_failed;
}
