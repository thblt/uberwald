#include <stdlib.h>

#include "check.h"

void test_object_c(Suite*);
void test_stack_c(Suite*);

int main(void)
 {
    int number_failed;
    Suite *s;
    SRunner *sr;

    s = suite_create("Überwald");

    sr = srunner_create(s);

    test_object_c(s);
    test_stack_c(s);

    srunner_run_all(sr, CK_VERBOSE);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
 }
