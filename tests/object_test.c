#include "check.h"

#include "../src/object.h"
#include "../src/store.h"

START_TEST (los_pred_sanity)
{
  ubw_obj obj[10];

  ubw_list_init(&obj[0], NULL, NULL);
  // ubw_vector_init(&obj[1], NULL);
  // @FIXME Test not complete: vector, char, string, keyword missing.

  ubw_int_init(&obj[2], 1);
  ubw_float_init(&obj[3], 1.5);
  // ubw_char_init(&obj[4], 'a');
  // ubw_string_init(&obj[5], NULL);

  ubw_symbol_init(&obj[6], 0);
  // ubw_keyword_init(&obj[7], 0);

  ubw_int_init(&obj[8], 0);
  obj[8].type = _DELETED;

  // ======================

  ck_assert(ubw_list_p(&obj[0]));
  // ck_assert(ubw_vector_p(&obj[1]));

  ck_assert(ubw_int_p(&obj[2]));
  ck_assert(ubw_float_p(&obj[3]));
  // ck_assert(ubw_char_p(&obj[4]));
  // ck_assert(ubw_string_p(&obj[5]));

  ck_assert(ubw_symbol_p(&obj[6]));
  // ck_assert(ubw_keyword_p(&obj[7]));

  // ck_assert(ubw_cfunc_p(&obj[8]));



}

END_TEST

START_TEST (int_sanity)
{
  for (int i=0; i < (1024 * 1024); i++)
    ck_assert_int_eq (ubw_int_unbox(ubw_int_new(NULL, i)), i);
}
END_TEST

void test_object_c(Suite *s) {
  TCase *tc = tcase_create("object.c");

  tcase_add_test(tc, los_pred_sanity);
  tcase_add_test(tc, int_sanity);

  suite_add_tcase(s, tc);
}
