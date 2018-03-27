#include "ubwtest.h"

ubw_stack s5, s16, s5f, s16f;
ubw_obj o, o0, o1, o2, o3, o4, o5;

void stack_c_setup() {
  ubw_stack_init(&s5, 5, NULL);
  ubw_stack_init(&s16, 16, NULL);
}

void stack_c_teardown() {
  free (s5.beg);
  free (s16.beg);
}

/**
 * @brief Basic sanity tests of the ubw_stack_init function.
 */
START_TEST (init)
{
  ck_assert_ptr_eq(s16.head, s16.beg);
  ck_assert(s16.end > s16.beg);
  ck_assert_ptr_eq(s16.end, &s16.beg[15]);
}
END_TEST

/**
 * @brief Check that push and pop correctly increment and decrement
 * head, respectively.
 *
 * \note Overflow and underflow management are tested separately.
 */
START_TEST (push_pop_pointer_interaction)
{
  ubw_stack_push(&s5, &o);
  ck_assert_ptr_eq(s5.head, &s5.beg[1]);

  ubw_stack_push(&s5, &o4);
  ck_assert_ptr_eq(s5.head, &s5.beg[2]);

  ubw_stack_push(&s5, &o1);
  ck_assert_ptr_eq(s5.head, &s5.beg[3]);

  ubw_stack_push(&s5, &o2);
  ck_assert_ptr_eq(s5.head, &s5.beg[4]);

  ubw_stack_push(&s5, &o3);
  ck_assert_ptr_eq(s5.head, &s5.beg[5]);

  ubw_stack_pop(&s5);
  ck_assert_ptr_eq(s5.head, &s5.beg[4]);

  ubw_stack_pop(&s5);
  ck_assert_ptr_eq(s5.head, &s5.beg[3]);

  ubw_stack_pop(&s5);
  ck_assert_ptr_eq(s5.head, &s5.beg[2]);

  ubw_stack_pop(&s5);
  ck_assert_ptr_eq(s5.head, &s5.beg[1]);

  ubw_stack_pop(&s5);
  ck_assert_ptr_eq(s5.head, s5.beg);
}
END_TEST

/**
 * @brief Check that fpush and fpop correctly increment and decrement
 * head, respectively.
 *
 * \note Overflow and underflow management are tested separately.
 */
START_TEST (fpush_fpop_pointer_interaction)
{
  ubw_stack_fpush(&s5, &o);
  ck_assert_ptr_eq(s5.head, &s5.beg[1]);

  ubw_stack_fpush(&s5, &o4);
  ck_assert_ptr_eq(s5.head, &s5.beg[2]);

  ubw_stack_fpush(&s5, &o1);
  ck_assert_ptr_eq(s5.head, &s5.beg[3]);

  ubw_stack_fpush(&s5, &o2);
  ck_assert_ptr_eq(s5.head, &s5.beg[4]);

  ubw_stack_fpush(&s5, &o3);
  ck_assert_ptr_eq(s5.head, &s5.beg[5]);

  ubw_stack_fpop(&s5);
  ck_assert_ptr_eq(s5.head, &s5.beg[4]);

  ubw_stack_fpop(&s5);
  ck_assert_ptr_eq(s5.head, &s5.beg[3]);

  ubw_stack_fpop(&s5);
  ck_assert_ptr_eq(s5.head, &s5.beg[2]);

  ubw_stack_fpop(&s5);
  ck_assert_ptr_eq(s5.head, &s5.beg[1]);

  ubw_stack_fpop(&s5);
  ck_assert_ptr_eq(s5.head, s5.beg);

  free(s5.beg);
}
END_TEST

/**
 * @brief Check that when the stack is full, head==end.
 */
START_TEST (pointer_alignment)
{
  ubw_stack_push(&s5, &o);
  ubw_stack_push(&s5, &o4);
  ubw_stack_push(&s5, &o1);
  ubw_stack_push(&s5, &o2);

  ck_assert_ptr_eq(s5.head, s5.end);
  ubw_stack_push(&s5, &o3);
  ck_assert(s5.head > s5.end);

  free(s5.beg);
}
END_TEST

/**
 * Check that push correctly returns a pointer to the object it received
 */
START_TEST (push_retval)
{
  ubw_obj *ret;

  ret = ubw_stack_push(&s5, &o0);
  ck_assert_ptr_eq(&o0, ret);
  ret = ubw_stack_push(&s5, &o1);
  ck_assert_ptr_eq(&o1, ret);
  ret = ubw_stack_push(&s5, &o2);
  ck_assert_ptr_eq(&o2, ret);
  ret = ubw_stack_push(&s5, &o3);
  ck_assert_ptr_eq(&o3, ret);
}
END_TEST

/**
 * Check that fpush correctly returns a pointer to the object it received
 */
START_TEST (fpush_retval)
{
  ubw_obj *ret;

  ret = ubw_stack_fpush(&s5, &o0);
  ck_assert_ptr_eq(&o0, ret);
  ret = ubw_stack_fpush(&s5, &o1);
  ck_assert_ptr_eq(&o1, ret);
  ret = ubw_stack_fpush(&s5, &o2);
  ck_assert_ptr_eq(&o2, ret);
  ret = ubw_stack_fpush(&s5, &o3);
  ck_assert_ptr_eq(&o3, ret);
}
END_TEST

/**
 * Check that each push increases the return value of length by one,
 * each pop decreases it by one.
 *
 * \note Overflow and underflow management are tested separately.
 */
START_TEST (push_pop_length_interaction)
{
  ck_assert_int_eq(ubw_stack_length(&s5), 0);

  ubw_stack_push(&s5, &o);
  ck_assert_int_eq(ubw_stack_length(&s5), 1);

  ubw_stack_push(&s5, &o);
  ck_assert_int_eq(ubw_stack_length(&s5), 2);

  ubw_stack_push(&s5, &o);
  ck_assert_int_eq(ubw_stack_length(&s5), 3);

  ubw_stack_push(&s5, &o);
  ck_assert_int_eq(ubw_stack_length(&s5), 4);

  ubw_stack_push(&s5, &o);
  ck_assert_int_eq(ubw_stack_length(&s5), 5);

  // Overflow!
  ubw_stack_push(&s5, &o);

  int length = ubw_stack_length(&s5);
  ck_assert_int_eq(length, 5);

  ubw_stack_pop(&s5);
  ck_assert_int_eq(ubw_stack_length(&s5), 4);

  ubw_stack_pop(&s5);
  ck_assert_int_eq(ubw_stack_length(&s5), 3);

  ubw_stack_pop(&s5);
  ck_assert_int_eq(ubw_stack_length(&s5), 2);

  ubw_stack_pop(&s5);
  ck_assert_int_eq(ubw_stack_length(&s5), 1);

  ubw_stack_pop(&s5);
  ck_assert_int_eq(ubw_stack_length(&s5), 0);
}
END_TEST

/**
 * Check that each fpush increases the return value of length by one,
 * each fpop decreases it by one.
 *
 * \note Overflow and underflow management are tested separately.
 */
START_TEST (fpush_fpop_length_interaction)
{
  ck_assert_int_eq(ubw_stack_length(&s5), 0);

  ubw_stack_fpush(&s5, &o);
  ck_assert_int_eq(ubw_stack_length(&s5), 1);

  ubw_stack_fpush(&s5, &o);
  ck_assert_int_eq(ubw_stack_length(&s5), 2);

  ubw_stack_fpush(&s5, &o);
  ck_assert_int_eq(ubw_stack_length(&s5), 3);

  // Now pop
  ubw_stack_fpop(&s5);
  ck_assert_int_eq(ubw_stack_length(&s5), 2);

  ubw_stack_fpop(&s5);
  ck_assert_int_eq(ubw_stack_length(&s5), 1);

  ubw_stack_fpop(&s5);
  ck_assert_int_eq(ubw_stack_length(&s5), 0);
}
END_TEST

/**
 * Check that peek has no effect on length
 */
START_TEST (peek_length_interaction)
{
  ubw_stack_fpush(&s5, &o);
  ubw_stack_fpush(&s5, &o);
  ubw_stack_fpush(&s5, &o);
  ck_assert_int_eq(ubw_stack_length(&s5), 3);
  ubw_stack_peek(&s5);
  ck_assert_int_eq(ubw_stack_length(&s5), 3);
  ubw_stack_peek(&s5);
  ck_assert_int_eq(ubw_stack_length(&s5), 3);
}
END_TEST

/**
 * Check that fpeek has no effect on length
 */
START_TEST (fpeek_length_interaction)
{
  ubw_stack_fpush(&s5, &o);
  ubw_stack_fpush(&s5, &o);
  ubw_stack_fpush(&s5, &o);
  ck_assert_int_eq(ubw_stack_length(&s5), 3);
  ubw_stack_fpeek(&s5);
  ck_assert_int_eq(ubw_stack_length(&s5), 3);
  ubw_stack_fpeek(&s5);
  ck_assert_int_eq(ubw_stack_length(&s5), 3);
}
END_TEST

/**
 * @brief Check that pop correctly returns a pointer to the last pushed value, without changing it.
 *
 * This only tests push and pop, but two tests are dedicated to
 * verifying that push == fpush and pop == fpop in normal situations.
 */
START_TEST (push_pop_interaction)
{
  // First, in alternate steps: push, pop, push, pop...
  ubw_stack_push(&s5, &o0);
  ck_assert_ptr_eq(&o0, ubw_stack_pop(&s5));
  ubw_stack_push(&s5, &o1);
  ck_assert_ptr_eq(&o1, ubw_stack_pop(&s5));
  ubw_stack_push(&s5, &o2);
  ck_assert_ptr_eq(&o2, ubw_stack_pop(&s5));
  ubw_stack_push(&s5, &o3);
  ck_assert_ptr_eq(&o3, ubw_stack_pop(&s5));
  ubw_stack_push(&s5, &o4);
  ck_assert_ptr_eq(&o4, ubw_stack_pop(&s5));

  // Then up and down
  ubw_stack_push(&s5, &o0);
  ubw_stack_push(&s5, &o1);
  ubw_stack_push(&s5, &o2);
  ubw_stack_push(&s5, &o3);
  ubw_stack_push(&s5, &o4);
  ck_assert_ptr_eq(&o4, ubw_stack_pop(&s5));
  ck_assert_ptr_eq(&o3, ubw_stack_pop(&s5));
  ck_assert_ptr_eq(&o2, ubw_stack_pop(&s5));
  ck_assert_ptr_eq(&o1, ubw_stack_pop(&s5));
  ck_assert_ptr_eq(&o0, ubw_stack_pop(&s5));
}
END_TEST

/**
 * @brief Check that push and fpush bring a stack in exactly the same
 * state, in normal (=non overflowing) situations.
 */
START_TEST (push_fpush_equivalence)
{
  ubw_obj **head, *obj, *ret1, *ret2;

  // First, push, then fpush.
  ret1 = ubw_stack_push(&s5, &o0);
  head = s5.head;
  obj = *s5.beg;
  ck_assert_ptr_eq(&o0, obj);

  ubw_stack_pop(&s5); // Reset

  ret2 = ubw_stack_fpush(&s5, &o0);

  ck_assert_ptr_eq(ret1, ret2);
  ck_assert_ptr_eq(s5.head, head);
  ck_assert_ptr_eq(*s5.beg, obj);

  // Then, fpush first.
  ret1 = ubw_stack_fpush(&s5, &o0);
  head = s5.head;
  obj = *s5.beg;
  ck_assert_ptr_eq(&o0, obj);

  ubw_stack_pop(&s5); // Reset

  ret2 = ubw_stack_push(&s5, &o0);

  ck_assert_ptr_eq(ret1, ret2);
  ck_assert_ptr_eq(s5.head, head);
  ck_assert_ptr_eq(*s5.beg, obj);
}
END_TEST

/**
 * @brief Check that pop and fpop return exactly the same value in
 * normal situations.
 */
START_TEST (pop_fpop_equivalence)
{
  ubw_obj **head, *ret1, *ret2;

  // First, pop, then fpop.
  ubw_stack_push(&s5, &o0); // Initial state
  ret1 = ubw_stack_pop(&s5);
  head = s5.head;
  ubw_stack_push(&s5, &o0); // Reset
  ret2 = ubw_stack_fpop(&s5); // fpop
  ck_assert_ptr_eq(ret1, ret2);
  ck_assert_ptr_eq(s5.head, head);

  // Then fpop first.
  ubw_stack_push(&s5, &o0); // Initial state
  ret1 = ubw_stack_fpop(&s5);
  head = s5.head;
  ubw_stack_push(&s5, &o0); // Reset
  ret2 = ubw_stack_pop(&s5); // fpop
  ck_assert_ptr_eq(ret1, ret2);
  ck_assert_ptr_eq(s5.head, head);
}
END_TEST

/** @brief Check that peek is sane.
 *
 * Control that peek returns exactly the last pushed value and leaves
 * the stack in a completely unmodified state. */
START_TEST(peek_sanity)
{
  ubw_obj** head;

  ubw_stack_push(&s5, &o0);
  ubw_stack_push(&s5, &o1);
  head = s5.head;
  ck_assert_ptr_eq(head, s5.head);
  ck_assert_ptr_eq(&o1, ubw_stack_peek(&s5));
  ck_assert_ptr_eq(&o1, ubw_stack_peek(&s5));

}
END_TEST

/** @brief Check that peek is sane.
 *
 * Control that peek returns exactly the last pushed value and leaves
 * the stack in a completely unmodified state. */
START_TEST(fpeek_sanity)
{
  ubw_obj** head;

  ubw_stack_push(&s5, &o0);
  ubw_stack_push(&s5, &o1);
  head = s5.head;
  ck_assert_ptr_eq(&o1, ubw_stack_peek(&s5));
  ck_assert_ptr_eq(&o1, ubw_stack_peek(&s5));
  ck_assert_ptr_eq(head, s5.head);
}
END_TEST


/**
 * @brief Check whether push correctly triggers an overflow instead of going above capacity
 */
START_TEST (push_overflow)
{
  ubw_obj **head;

  ck_assert_ptr_eq(&o0, ubw_stack_push(&s5, &o0));
  ck_assert_ptr_eq(&o1, ubw_stack_push(&s5, &o1));
  ck_assert_ptr_eq(&o2, ubw_stack_push(&s5, &o2));
  ck_assert_ptr_eq(&o3, ubw_stack_push(&s5, &o3));
  ck_assert_ptr_eq(&o4, ubw_stack_push(&s5, &o4));
  head = s5.head;
  ck_assert_ptr_eq(NULL, ubw_stack_push(&s5, &o5));
  ck_assert_ptr_eq(head, s5.head);
}
END_TEST

/**
 * @brief Check whether pop correctly triggers an underflow instead of
 * going below capacity.
 */
START_TEST (pop_underflow)
{
  ubw_obj **head = s5.head;

  ck_assert_ptr_eq(NULL, ubw_stack_pop(&s5));
  ck_assert_ptr_eq(head, s5.head);
}
END_TEST

/**
 * @brief Check whether peek correctly triggers an underflow instead
 * of going below capacity.
 */
START_TEST (peek_underflow)
{
  ubw_obj **head = s5.head;

  ck_assert_ptr_eq(NULL, ubw_stack_peek(&s5));
  ck_assert_ptr_eq(head, s5.head);
}

END_TEST

Suite * stack_c_suite() {
  Suite *s = suite_create("stack.c");
  TCase *tc;

  tc = ubw_tcase(s, "Core");

  tcase_add_checked_fixture(tc, stack_c_setup, stack_c_teardown);
  tcase_add_test(tc, init);
  tcase_add_test(tc, push_pop_pointer_interaction);
  tcase_add_test(tc, fpush_fpop_pointer_interaction);
  tcase_add_test(tc, pointer_alignment);
  tcase_add_test(tc, push_pop_length_interaction);
  tcase_add_test(tc, fpush_fpop_length_interaction);
  tcase_add_test(tc, peek_length_interaction);
  tcase_add_test(tc, fpeek_length_interaction);

  tcase_add_test(tc, push_retval);
  tcase_add_test(tc, fpush_retval);

  tcase_add_test(tc, push_pop_interaction);
  tcase_add_test(tc, push_fpush_equivalence);
  tcase_add_test(tc, pop_fpop_equivalence);
  tcase_add_test(tc, peek_sanity);
  tcase_add_test(tc, fpeek_sanity);

  // Overflow
  tcase_add_test(tc, push_overflow);

  // Underflow
  tcase_add_test(tc, pop_underflow);
  tcase_add_test(tc, peek_underflow);

  return s;
}
