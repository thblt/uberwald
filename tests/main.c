#include <stdlib.h>

#include "check.h"

START_TEST (test0)
{
  ck_assert_int_eq(3,14);
  ck_assert_int_eq(12,3);
  }
END_TEST

Suite * test_suite(void)
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("test0");

    /* Core test case */
    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test0);
    suite_add_tcase(s, tc_core);

    return s;
}


int main(void)
 {
    int number_failed;
    Suite *s;
    SRunner *sr;

    s = test_suite();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
 }
