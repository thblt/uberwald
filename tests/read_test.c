#include "ubwtest.h"

START_TEST (tkn_lists)
{
  ubw_reader r;
  ubw_reader_init(&r, NULL, "((    ))\n())");
  ubw_token t;

  ck_assert_int_eq(r.pos, 0);
  ck_assert_int_eq(r.col, 0);
  ck_assert_int_eq(r.line, 1);

  next_token(&r, &t);
  ck_assert_int_eq(t.type, TK_BOL);
  ck_assert_int_eq(r.pos, 1);
  ck_assert_int_eq(r.col, 1);
  ck_assert_int_eq(r.line, 1);

  next_token(&r, &t);
  ck_assert_int_eq(t.type, TK_BOL);
  ck_assert_int_eq(r.pos, 2);
  ck_assert_int_eq(r.col, 2);
  ck_assert_int_eq(r.line, 1);

  next_token(&r, &t);
  ck_assert_int_eq(t.type, TK_EOL);
  ck_assert_int_eq(r.pos, 7);
  ck_assert_int_eq(r.col, 7);
  ck_assert_int_eq(r.line, 1);

  next_token(&r, &t);
  ck_assert_int_eq(t.type, TK_EOL);
  ck_assert_int_eq(r.pos, 8);
  ck_assert_int_eq(r.col, 8);
  ck_assert_int_eq(r.line, 1);

  // Line break

  next_token(&r, &t);
  ck_assert_int_eq(t.type, TK_BOL);
  ck_assert_int_eq(r.pos, 10);
  ck_assert_int_eq(r.col, 1);
  ck_assert_int_eq(r.line, 2);

  next_token(&r, &t);
  ck_assert_int_eq(t.type, TK_EOL);
  ck_assert_int_eq(r.pos, 11);
  ck_assert_int_eq(r.col, 2);
  ck_assert_int_eq(r.line, 2);

  next_token(&r, &t);
  ck_assert_int_eq(t.type, TK_EOL);
  ck_assert_int_eq(r.pos, 12);
  ck_assert_int_eq(r.col, 3);
  ck_assert_int_eq(r.line, 2);

  next_token(&r, &t);
  ck_assert_int_eq(t.type, TK_END);
}
END_TEST

START_TEST (tkn_nospace)
{
  ubw_reader r;
  ubw_reader_init(&r, NULL, "(abc)");
  ubw_token t;

  ck_assert_int_eq(r.pos, 0);
  ck_assert_int_eq(r.col, 0);

  next_token(&r, &t);
  ck_assert_int_eq(t.type, TK_BOL);
  ck_assert_int_eq(r.pos, 1);
  ck_assert_int_eq(r.col, 1);

  next_token(&r, &t);
  ck_assert_int_eq(t.type, TK_OTHER);
  ck_assert_int_eq(t.length, 3);
  ck_assert_int_eq(r.pos, 4);
  ck_assert_int_eq(r.col, 4);

  next_token(&r, &t);
  ck_assert_int_eq(t.type, TK_EOL);
  ck_assert_int_eq(r.pos, 5);
  ck_assert_int_eq(r.col, 5);
  ck_assert_int_eq(r.line, 1);
}
END_TEST

START_TEST (tkn_symbols_and_numbers)
{
  char *lisp = "( abc def 123 12.39     457 )";
  ubw_reader r;
  ubw_reader_init(&r, NULL, lisp);
  ubw_token t;

  ck_assert_int_eq(r.pos, 0);
  ck_assert_int_eq(r.col, 0);
  ck_assert_int_eq(r.line, 1);

  next_token(&r, &t); // (
  ck_assert_int_eq(t.type, TK_BOL);
  ck_assert_int_eq(r.pos, 1);

  next_token(&r, &t); // abc
  ck_assert_int_eq(t.type, TK_OTHER);
  ck_assert_int_eq(t.length, 3);
  ck_assert_int_eq(r.pos, 5);
  ck_assert_int_eq(r.col, 5);
  ck_assert_int_eq(r.line, 1);

  next_token(&r, &t); // def
  ck_assert_int_eq(t.type, TK_OTHER);
  ck_assert_int_eq(t.length, 3);
  ck_assert_int_eq(r.pos, 9);
  ck_assert_int_eq(r.col, 9);
  ck_assert_int_eq(r.line, 1);

  next_token(&r, &t); // 123
  ck_assert_int_eq(t.type, TK_OTHER);
  ck_assert_int_eq(t.length, 3);
  ck_assert_int_eq(r.pos, 13);
  ck_assert_int_eq(r.col, 13);
  ck_assert_int_eq(r.line, 1);

  next_token(&r, &t); // 12.39
  ck_assert_int_eq(t.type, TK_OTHER);
  ck_assert_int_eq(t.length, 5);
  ck_assert_int_eq(r.pos, 19);
  ck_assert_int_eq(r.col, 19);
  ck_assert_int_eq(r.line, 1);

  next_token(&r, &t); // 457
  ck_assert_int_eq(t.type, TK_OTHER);
  ck_assert_int_eq(t.length, 3);
  ck_assert_int_eq(r.pos, 27);
  ck_assert_int_eq(r.col, 27);
  ck_assert_int_eq(r.line, 1);

}
END_TEST

START_TEST (rd_base)
{
  ubw_reader r;
  ubw_reader_init(&r, NULL, "(abc)");

  ubw_read(&r);

  ck_assert_int_eq(r.root->type, LIST);
  ck_assert_ptr_eq(r.root->data.list.cdr, NULL);
  ck_assert_int_eq(r.root->data.list.car->type, SYMBOL);

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
