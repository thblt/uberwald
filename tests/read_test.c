#include "ubwtest.h"

Suite * read_c_suite() {
  Suite *s = suite_create("read.c");
  TCase *tc;

  tc = ubw_tcase(s, "Tokenizer");

  return s;

}
