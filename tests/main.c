/** @file
 * @brief Main caller of the test suite
 *
 * @defgroup tests Tests
 * @brief Test suite for the whole Überwald project.
 */

#include <stdlib.h>

#include "ubwtest.h"

Suite* object_c_suite();
Suite* stack_c_suite();
Suite* read_c_suite();
Suite* stbl_c_suite();

int main(void)
 {
    int number_failed;
    SRunner *sr;

    sr = srunner_create(object_c_suite());
    srunner_add_suite(sr, stack_c_suite());
    srunner_add_suite(sr, stbl_c_suite());
    srunner_add_suite(sr, read_c_suite());

    srunner_run_all(sr, CK_VERBOSE);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
 }
