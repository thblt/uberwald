#pragma once

#include <check.h>

#include "../src/uberwald.h"

#define ubw_suite() suite_create(__FILE__)

/** @brief Create a case and immediately add it to suite. */
inline TCase * ubw_tcase(Suite *s, const char* name) {
  TCase *tc = tcase_create(name);
  suite_add_tcase(s, tc);
  return tc;
}

#define START_CASE(name)
