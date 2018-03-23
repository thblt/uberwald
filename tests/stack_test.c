#include "ubwtest.h"

START_TEST (length_los)
{
  ubw_los s;
  ubw_los_init(&s, 256, NULL);

  ubw_obj o;
  ubw_int_init(&o, 527);

  for (int i=1; i<257; i++) {
    ubw_los_push(&s, &o);
    ck_assert_int_eq(i,
                     ubw_los_length(&s));

    ck_assert_int_eq(i,
                     s.h);
  }

  for (int i=255; i>=0; i--) {
    ubw_los_pop(&s);
    ck_assert_int_eq(i,
                     ubw_los_length(&s));

    ck_assert_int_eq(i,
                     s.h);
  }

  free(s.d);
}
END_TEST

START_TEST (sanity_los_peek_and_pop)
{
  ubw_los s0, s1, s2;
  ubw_los_init(&s0, 256, NULL);
  ubw_los_init(&s1, 256, NULL);
  ubw_los_init(&s2, 256, NULL);

  // Just in case things get crazy.
  ck_assert_ptr_ne(s0.d, s1.d);

  ubw_obj o;

  for (int i=0; i<256; i++) {
    ubw_int_init(&o, i);

    ubw_los_push(&s0, &o);
    ubw_los_push(&s1, &o);
    ubw_los_push(&s2, &o);

    ck_assert_int_eq(i+1, s0.h);
    ck_assert_int_eq(1, s1.h);
    ck_assert_int_eq(1, s2.h);

    ck_assert_ptr_eq(ubw_los_peek(&s0),
                     &(s0.d[i]));

    ck_assert_ptr_eq(ubw_los_fpeek(&s0),
                     &s0.d[i]);

    ck_assert_ptr_eq(ubw_los_pop(&s1),
                     s1.d);

    ck_assert_ptr_eq(
                     ubw_los_fpop(&s2),
                     s2.d);
  }

  free (s0.d);
  free (s1.d);
  free (s2.d);
}
END_TEST

START_TEST (integrity_los)
{
  ubw_los s;
  ubw_los_init(&s, 512, NULL);

  ubw_obj o;

  for (int i=0; i<256; i++) {
    ubw_int_init(&o, i);
    ubw_los_push(&s, &o);
    ck_assert_int_eq(
                     //ubw_int_unbox(ubw_los_peek(&s)),
                     ubw_int_unbox(&s.d[i]),
                     i);
      }

  free (s.d);
}
END_TEST

START_TEST (ordering_los)
{
  ubw_los s;
  ubw_los_init(&s, 16, NULL);

  ubw_obj o0, o1, o2, o3, o4;

  ubw_int_init(&o0, 11);
  ubw_int_init(&o1, 22);
  ubw_int_init(&o2, 33);
  ubw_int_init(&o3, 44);
  ubw_int_init(&o4, 55);

  ubw_los_push(&s, &o0);
  ck_assert_int_eq (11, ubw_int_unbox(ubw_los_peek(&s)));
  ubw_los_push(&s, &o1);
  ubw_los_push(&s, &o2);
  ubw_los_push(&s, &o3);
  ubw_los_push(&s, &o4);

  ck_assert_int_eq (55, ubw_int_unbox(ubw_los_peek(&s)));
  ck_assert_int_eq (55, ubw_int_unbox(ubw_los_peek(&s)));
  ck_assert_int_eq (55, ubw_int_unbox(ubw_los_peek(&s)));
  ck_assert_int_eq (55, ubw_int_unbox(ubw_los_pop(&s)));
  ck_assert_int_eq (44, ubw_int_unbox(ubw_los_pop(&s)));
  ubw_los_push(&s, &o4);
  ck_assert_int_eq (55, ubw_int_unbox(ubw_los_pop(&s)));
  ck_assert_int_eq (33, ubw_int_unbox(ubw_los_pop(&s)));
  ck_assert_int_eq (22, ubw_int_unbox(ubw_los_pop(&s)));
  ck_assert_int_eq (11, ubw_int_unbox(ubw_los_pop(&s)));

  free(s.d);
}
END_TEST

START_TEST (underflow_los)
{
  ubw_los s;
  ubw_los_init(&s, 16, NULL);

  ubw_obj o;
  ubw_int_init(&o, 527);

  ubw_los_push(&s, &o);

  ck_assert_ptr_ne(NULL, ubw_los_pop(&s));
  ck_assert_ptr_eq(NULL, ubw_los_peek(&s));

  free(s.d);
}

END_TEST

START_TEST (overflow_los)
{
  ubw_los s;
  ubw_los_init(&s, 4, NULL);

  ubw_obj o;
  ubw_int_init(&o, 311);

  ck_assert_ptr_ne(NULL, ubw_los_push(&s, &o));
  ck_assert_ptr_ne(NULL, ubw_los_push(&s, &o));
  ck_assert_ptr_ne(NULL, ubw_los_push(&s, &o));
  ck_assert_ptr_ne(NULL, ubw_los_push(&s, &o));
  // Overflow here
  ck_assert_ptr_eq(NULL, ubw_los_push(&s, &o));

  free(s.d);
}
END_TEST

Suite * stack_c_suite() {
  Suite *s = suite_create("stack.c");
  TCase *tc;

  tc = ubw_tcase(s, "LispObject");
  tcase_add_test(tc, length_los);
  tcase_add_test(tc, sanity_los_peek_and_pop);
  tcase_add_test(tc, overflow_los);
  tcase_add_test(tc, underflow_los);
  tcase_add_test(tc, ordering_los);
  tcase_add_test(tc, integrity_los);

  return s;
}
