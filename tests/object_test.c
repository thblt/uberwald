#include "check.h"

#include "../src/object.h"

START_TEST (integers) {
  for (int i=0; i < (1024 * 1024); i++)
  ck_assert_int_eq (ubw_int_unbox(ubw_int_new(i)), i);
} END_TEST
