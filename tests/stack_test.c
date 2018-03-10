#include <check.h>

#include "../src/stack.h"

START_TEST (stack_order)
{
  lostk_t s;
  lostk_init(&s, 16);

  ubw_obj *lia = ubw_int_new(1),
    *lib = ubw_int_new(2),
    *lic = ubw_int_new(3),
    *lid = ubw_int_new(4),
    *lie = ubw_int_new(5);

  lostk_push(&s, lia);
  lostk_push(&s, lib);
  lostk_push(&s, lic);
  lostk_push(&s, lid);
  lostk_push(&s, lie);

  ck_assert_int_eq (5, ubw_int_unbox(lostk_peek(&s)));
  ck_assert_int_eq (5, ubw_int_unbox(lostk_peek(&s)));
  ck_assert_int_eq (5, ubw_int_unbox(lostk_peek(&s)));
  ck_assert_int_eq (5, ubw_int_unbox(lostk_pop(&s)));
  ck_assert_int_eq (4, ubw_int_unbox(lostk_pop(&s)));
  lostk_push(&s, lia);
  ck_assert_int_eq (1, ubw_int_unbox(lostk_pop(&s)));
  ck_assert_int_eq (3, ubw_int_unbox(lostk_pop(&s)));
  ck_assert_int_eq (2, ubw_int_unbox(lostk_pop(&s)));
  ck_assert_int_eq (1, ubw_int_unbox(lostk_pop(&s)));
}
END_TEST

START_TEST (stack_underflow)
{
  lostk_t s;
  lostk_init(&s, 16);

  ck_assert_int_eq(s.underflow, 0);
  lostk_safe_peek(&s);
  ck_assert_int_eq(s.underflow, 1);
  lostk_safe_peek(&s);
  ck_assert_int_eq(s.underflow, 2);
}
END_TEST

START_TEST (stack_overflow)
{
  lostk_t s;
  lostk_init(&s, 4);

  lostk_safe_push(&s, ubw_int_new(0));
  ck_assert_int_eq(s.overflow, 0);
  lostk_safe_push(&s, ubw_int_new(0));
  ck_assert_int_eq(s.overflow, 0);
  lostk_safe_push(&s, ubw_int_new(0));
  ck_assert_int_eq(s.overflow, 0);
  lostk_safe_push(&s, ubw_int_new(0));
  ck_assert_int_eq(s.overflow, 0);
  lostk_safe_push(&s, ubw_int_new(0));
  ck_assert_int_eq(s.overflow, 1);
  lostk_safe_push(&s, ubw_int_new(0));
  ck_assert_int_eq(s.overflow, 2);
}
END_TEST

Suite * stack_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("stack.c");

  /* Core test case */
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, stack_order);
  tcase_add_test(tc_core, stack_underflow);
  tcase_add_test(tc_core, stack_overflow);
  suite_add_tcase(s, tc_core);

  return s;
}
