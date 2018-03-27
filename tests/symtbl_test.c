#include <limits.h>

#include "ubwtest.h"

ubw_rt runtime;

START_TEST (symbid_size)
{
  ck_assert_int_eq(sizeof(ubw_symbid)*CHAR_BIT, UBW_SYMTBL_SYMBID_SIZE);
}
END_TEST

Suite * symtbl_c_suite() {
  Suite *s = suite_create("symtbl.c");
  TCase *tc;

  tc = ubw_tcase(s, "Build configuration");
  tcase_add_test(tc, symbid_size);

  return s;
}
