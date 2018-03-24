#include "ubwtest.h"

/** @brief Return true iff o matches one and only one of the type predicates */
bool sane_p(ubw_obj *o) {
  int c = 0;
  if (ubw_list_p(o)) c++;
  if (ubw_vector_p(o)) c++;

  if (ubw_int_p(o)) c++;
  if (ubw_float_p(o)) c++;
  if (ubw_char_p(o)) c++;
  if (ubw_string_p(o)) c++;

  if (ubw_symbol_p(o)) c++;
  if (ubw_keyword_p(o)) c++;

  if (ubw_cfunc_p(o)) c++;

  return (1 == c);
}

START_TEST (core_predicates)
{
  ubw_obj o;

  // List
  ubw_list_init(&o, NULL, NULL);
  ck_assert(ubw_list_p(&o));
  ck_assert(sane_p(&o));

  // Vector
  ubw_vector_init(&o);
  ck_assert(ubw_vector_p(&o));
  ck_assert(sane_p(&o));

  // Int
  ubw_int_init(&o, 0);
  ck_assert(ubw_int_p(&o));
  ck_assert(sane_p(&o));

  // Float
  ubw_float_init(&o, 0.1);
  ck_assert(ubw_float_p(&o));
  ck_assert(sane_p(&o));

  // Char
  ubw_char_init(&o, 'a');
  ck_assert(ubw_char_p(&o));
  ck_assert(sane_p(&o));

  // String
  ubw_string s;
  ubw_string_init(&o, s);
  ck_assert(ubw_string_p(&o));
  ck_assert(sane_p(&o));

  // Symbol
  ubw_symbol_init(&o, 0);
  ck_assert(ubw_symbol_p(&o));
  ck_assert(sane_p(&o));

  // Keyword
  ubw_keyword_init(&o, 0);
  ck_assert(ubw_keyword_p(&o));
  ck_assert(sane_p(&o));

  // CFunc
  ubw_cfunc cf;
  ubw_cfunc_init(&o, cf);
  ck_assert(ubw_cfunc_p(&o));
  ck_assert(sane_p(&o));
}
END_TEST

START_TEST (int_sanity)
{
  for (int i=0; i < (1024 * 1024); i++)
    ck_assert_int_eq (ubw_int_unbox(ubw_int_new(NULL, i)), i);
}
END_TEST

START_TEST (list_sanity)
{
  ubw_obj l, car, cdr;
  ubw_int_init(&car, 12);
  ubw_symbol_init(&cdr, 1);

  ubw_list_init(&l, &car, &cdr);

  ck_assert_ptr_eq(&car, ubw_list_car(&l));
  ck_assert_ptr_eq(&cdr, ubw_list_cdr(&l));

}
END_TEST

Suite * object_c_suite() {
  Suite *s = suite_create("object.c");
  TCase *tc;

  tc = ubw_tcase(s, "Core");
  tcase_add_test(tc, core_predicates);

  tc = ubw_tcase(s, "Integers");
  tcase_add_test(tc, int_sanity);

  tc = ubw_tcase(s, "Lists");
  tcase_add_test(tc, list_sanity);


  return s;
}
