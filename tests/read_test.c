/**
 * @ingroup tests
 *
 * @file
 * @brief Test suite for read.c
 */

#include "ubwtest.h"

ubw_rt runtime;
ubw_reader reader;

void setup() {
  ubw_reader_init(&runtime, &reader);
}

START_TEST (tkn_lists)
{
  const char* lisp = "((    ))\n())";

  ubw_token t;

  ck_assert_int_eq(reader.pos, 0);
  ck_assert_int_eq(reader.col, 0);
  ck_assert_int_eq(reader.line, 1);

  next_token(&reader, &t, lisp);
  ck_assert_int_eq(t.type, TK_BOL);
  ck_assert_int_eq(reader.pos, 1);
  ck_assert_int_eq(reader.col, 1);
  ck_assert_int_eq(reader.line, 1);

  next_token(&reader, &t, lisp);
  ck_assert_int_eq(t.type, TK_BOL);
  ck_assert_int_eq(reader.pos, 2);
  ck_assert_int_eq(reader.col, 2);
  ck_assert_int_eq(reader.line, 1);

  next_token(&reader, &t, lisp);
  ck_assert_int_eq(t.type, TK_EOL);
  ck_assert_int_eq(reader.pos, 7);
  ck_assert_int_eq(reader.col, 7);
  ck_assert_int_eq(reader.line, 1);

  next_token(&reader, &t, lisp);
  ck_assert_int_eq(t.type, TK_EOL);
  ck_assert_int_eq(reader.pos, 8);
  ck_assert_int_eq(reader.col, 8);
  ck_assert_int_eq(reader.line, 1);

  // Line break

  next_token(&reader, &t, lisp);
  ck_assert_int_eq(t.type, TK_BOL);
  ck_assert_int_eq(reader.pos, 10);
  ck_assert_int_eq(reader.col, 1);
  ck_assert_int_eq(reader.line, 2);

  next_token(&reader, &t, lisp);
  ck_assert_int_eq(t.type, TK_EOL);
  ck_assert_int_eq(reader.pos, 11);
  ck_assert_int_eq(reader.col, 2);
  ck_assert_int_eq(reader.line, 2);

  next_token(&reader, &t, lisp);
  ck_assert_int_eq(t.type, TK_EOL);
  ck_assert_int_eq(reader.pos, 12);
  ck_assert_int_eq(reader.col, 3);
  ck_assert_int_eq(reader.line, 2);

  next_token(&reader, &t, lisp);
  ck_assert_int_eq(t.type, TK_END);
}
END_TEST

START_TEST (tkn_nospace)
{

  const char *lisp = "(abc)";

  ubw_token t;

  ck_assert_int_eq(reader.pos, 0);
  ck_assert_int_eq(reader.col, 0);

  next_token(&reader, &t, lisp);
  ck_assert_int_eq(t.type, TK_BOL);
  ck_assert_int_eq(reader.pos, 1);
  ck_assert_int_eq(reader.col, 1);

  next_token(&reader, &t, lisp);
  ck_assert_int_eq(t.type, TK_OTHER);
  ck_assert_int_eq(t.length, 3);
  ck_assert_int_eq(reader.pos, 4);
  ck_assert_int_eq(reader.col, 4);

  next_token(&reader, &t, lisp);
  ck_assert_int_eq(t.type, TK_EOL);
  ck_assert_int_eq(reader.pos, 5);
  ck_assert_int_eq(reader.col, 5);
  ck_assert_int_eq(reader.line, 1);
}
END_TEST

START_TEST (tkn_symbols_and_numbers)
{
  const char *lisp = "( abc def 123 12.39     457 )";
  ubw_token t;

  ck_assert_int_eq(reader.pos, 0);
  ck_assert_int_eq(reader.col, 0);
  ck_assert_int_eq(reader.line, 1);

  next_token(&reader, &t, lisp); // (
  ck_assert_int_eq(t.type, TK_BOL);
  ck_assert_int_eq(reader.pos, 1);

  next_token(&reader, &t, lisp); // abc
  ck_assert_int_eq(t.type, TK_OTHER);
  ck_assert_int_eq(t.length, 3);
  ck_assert_int_eq(reader.pos, 5);
  ck_assert_int_eq(reader.col, 5);
  ck_assert_int_eq(reader.line, 1);

  next_token(&reader, &t, lisp); // def
  ck_assert_int_eq(t.type, TK_OTHER);
  ck_assert_int_eq(t.length, 3);
  ck_assert_int_eq(reader.pos, 9);
  ck_assert_int_eq(reader.col, 9);
  ck_assert_int_eq(reader.line, 1);

  next_token(&reader, &t, lisp); // 123
  ck_assert_int_eq(t.type, TK_OTHER);
  ck_assert_int_eq(t.length, 3);
  ck_assert_int_eq(reader.pos, 13);
  ck_assert_int_eq(reader.col, 13);
  ck_assert_int_eq(reader.line, 1);

  next_token(&reader, &t, lisp); // 12.39
  ck_assert_int_eq(t.type, TK_OTHER);
  ck_assert_int_eq(t.length, 5);
  ck_assert_int_eq(reader.pos, 19);
  ck_assert_int_eq(reader.col, 19);
  ck_assert_int_eq(reader.line, 1);

  next_token(&reader, &t, lisp); // 457
  ck_assert_int_eq(t.type, TK_OTHER);
  ck_assert_int_eq(t.length, 3);
  ck_assert_int_eq(reader.pos, 27);
  ck_assert_int_eq(reader.col, 27);
  ck_assert_int_eq(reader.line, 1);

}
END_TEST

START_TEST (rd_base)
{
  ck_assert_int_eq(runtime.h.es->type, LIST);
  ck_assert_ptr_eq(runtime.h.es->data.list.cdr, NULL);
  ck_assert_int_eq(runtime.h.es->data.list.car->type, SYMBOL);

}
END_TEST

Suite * read_c_suite() {
  Suite *s = suite_create("read.c");
  TCase *tc;

  tc = ubw_tcase(s, "Tokenizer");
  tcase_add_test(tc, tkn_lists);
  tcase_add_test(tc, tkn_nospace);
  tcase_add_test(tc, tkn_symbols_and_numbers);

  tc = ubw_tcase(s, "Reader");
  tcase_add_test(tc, rd_base);

  return s;
}
