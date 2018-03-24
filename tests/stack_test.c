#include "ubwtest.h"

START_TEST (length)
{
  ubw_stack s;
  ubw_stack_init(&s, 256, NULL);

  ubw_obj o;
  ubw_int_init(&o, 527);

  for (int i=1; i<257; i++) {
    ubw_stack_push(&s, &o);
    ck_assert_int_eq(i,
                     ubw_stack_length(&s));

    ck_assert_int_eq(i,
                     s.h);
  }

  for (int i=255; i>=0; i--) {
    ubw_stack_pop(&s);
    ck_assert_int_eq(i,
                     ubw_stack_length(&s));

    ck_assert_int_eq(i,
                     s.h);
  }

  free(s.d);
}
END_TEST

START_TEST (peek_and_pop_sanity)
{
  ubw_stack s0, s1, s2;
  ubw_stack_init(&s0, 256, NULL);
  ubw_stack_init(&s1, 256, NULL);
  ubw_stack_init(&s2, 256, NULL);

  // Just in case things get crazy.
  ck_assert_ptr_ne(s0.d, s1.d);

  ubw_obj o;

  for (int i=0; i<256; i++) {
    ubw_int_init(&o, i);

    ubw_stack_push(&s0, &o);
    ubw_stack_push(&s1, &o);
    ubw_stack_push(&s2, &o);

    ck_assert_int_eq(i+1, s0.h);
    ck_assert_int_eq(1, s1.h);
    ck_assert_int_eq(1, s2.h);

    ck_assert_ptr_eq(ubw_stack_peek(&s0),
                     s0.d[i]);

    ck_assert_ptr_eq(ubw_stack_fpeek(&s0),
                     s0.d[i]);

    ck_assert_ptr_eq(ubw_stack_pop(&s1),
                     *s1.d);

    ck_assert_ptr_eq(
                     ubw_stack_fpop(&s2),
                     *s2.d);
  }

  free (s0.d);
  free (s1.d);
  free (s2.d);
}
END_TEST

START_TEST (integrity)
{
  ubw_stack s;
  ubw_stack_init(&s, 512, NULL);

  ubw_obj o;

  for (int i=0; i<256; i++) {
    ubw_int_init(&o, i);
    ubw_stack_push(&s, &o);
    ck_assert_int_eq(
                     //ubw_int_unbox(ubw_stack_peek(&s)),
                     ubw_int_unbox(s.d[i]),
                     i);
      }

  free (s.d);
}
END_TEST

START_TEST (ordering)
{
  ubw_stack s;
  ubw_stack_init(&s, 16, NULL);

  ubw_obj o0, o1, o2, o3, o4;

  ubw_int_init(&o0, 11);
  ubw_int_init(&o1, 22);
  ubw_int_init(&o2, 33);
  ubw_int_init(&o3, 44);
  ubw_int_init(&o4, 55);

  ubw_stack_push(&s, &o0);
  ck_assert_int_eq (11, ubw_int_unbox(ubw_stack_peek(&s)));
  ubw_stack_push(&s, &o1);
  ubw_stack_push(&s, &o2);
  ubw_stack_push(&s, &o3);
  ubw_stack_push(&s, &o4);

  ck_assert_int_eq (55, ubw_int_unbox(ubw_stack_peek(&s)));
  ck_assert_int_eq (55, ubw_int_unbox(ubw_stack_peek(&s)));
  ck_assert_int_eq (55, ubw_int_unbox(ubw_stack_peek(&s)));
  ck_assert_int_eq (55, ubw_int_unbox(ubw_stack_pop(&s)));
  ck_assert_int_eq (44, ubw_int_unbox(ubw_stack_pop(&s)));
  ubw_stack_push(&s, &o4);
  ck_assert_int_eq (55, ubw_int_unbox(ubw_stack_pop(&s)));
  ck_assert_int_eq (33, ubw_int_unbox(ubw_stack_pop(&s)));
  ck_assert_int_eq (22, ubw_int_unbox(ubw_stack_pop(&s)));
  ck_assert_int_eq (11, ubw_int_unbox(ubw_stack_pop(&s)));

  free(s.d);
}
END_TEST

START_TEST (underflow)
{
  ubw_stack s;
  ubw_stack_init(&s, 16, NULL);

  ubw_obj o;
  ubw_int_init(&o, 527);

  ubw_stack_push(&s, &o);

  ck_assert_ptr_ne(NULL, ubw_stack_pop(&s));
  ck_assert_ptr_eq(NULL, ubw_stack_peek(&s));

  free(s.d);
}

END_TEST

START_TEST (overflow)
{
  ubw_stack s;
  ubw_stack_init(&s, 4, NULL);

  ubw_obj o;
  ubw_int_init(&o, 311);

  ck_assert_ptr_ne(NULL, ubw_stack_push(&s, &o));
  ck_assert_ptr_ne(NULL, ubw_stack_push(&s, &o));
  ck_assert_ptr_ne(NULL, ubw_stack_push(&s, &o));
  ck_assert_ptr_ne(NULL, ubw_stack_push(&s, &o));
  // Overflow here
  ck_assert_ptr_eq(NULL, ubw_stack_push(&s, &o));

  free(s.d);
}
END_TEST

Suite * stack_c_suite() {
  Suite *s = suite_create("stack.c");
  TCase *tc;

  tc = ubw_tcase(s, "Core");
  tcase_add_test(tc, length);
  tcase_add_test(tc, peek_and_pop_sanity);
  tcase_add_test(tc, integrity);
  tcase_add_test(tc, ordering);
  tcase_add_test(tc, underflow);
  tcase_add_test(tc, overflow);


  return s;
}
