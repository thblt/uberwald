/**
 * @file
 * @ingroup tests
 * @brief Test suite for stbl.c
 */

#include <limits.h>

#include "ubwtest.h"
#include "stbl.h"

ubw_stbl stbl;
char * symbols[] = {
  "hellish",
  "juvenile",
  "barbarous",
  "irritating",
  "drab",
  "gleaming",
  "donkey",
  "moor",
  "whisper",
  "tank",
  "fluttering",
  "brawny",
  "reign",
  "heady",
  "tacky",
  "property" };

int lengths[16];

void stbl_c_setup() {
  ubw_stbl_init(&stbl, 16, NULL, NULL);

  for (int i=0; i<16; i++) {
    lengths[i] = strlen(symbols[i]);
  }
}

void stbl_c_teardown() {
  free(stbl.flt);
}

/**
 * @brief Check that the actual hash type matches the configured hash length
 */
START_TEST (symbhash_size)
{
  ck_assert_int_eq(sizeof(ubw_symbhash)*CHAR_BIT, UBW_STBL_HASH_SIZE);
}
END_TEST

START_TEST (hash_fnv1_32)
{
  // @Todo
}
END_TEST

/**
 * @brief Intern a few symbols, verify they receive sequential IDs, intern them again, verify we receive the same IDs
 */
START_TEST (intern_forward)
{
  ck_assert_int_eq(1, ubw_stbl_intern(&stbl, symbols[0], symbols[0] + lengths[0]));
  ck_assert_int_eq(2, ubw_stbl_intern(&stbl, symbols[1], symbols[1] + lengths[1]));
  ck_assert_int_eq(3, ubw_stbl_intern(&stbl, symbols[2], symbols[2] + lengths[2]));
  ck_assert_int_eq(4, ubw_stbl_intern(&stbl, symbols[3], symbols[3] + lengths[3]));
  ck_assert_int_eq(5, ubw_stbl_intern(&stbl, symbols[4], symbols[4] + lengths[4]));
  ck_assert_int_eq(6, ubw_stbl_intern(&stbl, symbols[5], symbols[5] + lengths[5]));
  ck_assert_int_eq(7, ubw_stbl_intern(&stbl, symbols[6], symbols[6] + lengths[6]));
  ck_assert_int_eq(8, ubw_stbl_intern(&stbl, symbols[7], symbols[7] + lengths[7]));
  ck_assert_int_eq(9, ubw_stbl_intern(&stbl, symbols[8], symbols[8] + lengths[8]));
  ck_assert_int_eq(10, ubw_stbl_intern(&stbl, symbols[9], symbols[9] + lengths[9]));
  ck_assert_int_eq(11, ubw_stbl_intern(&stbl, symbols[10], symbols[10] + lengths[10]));
  ck_assert_int_eq(12, ubw_stbl_intern(&stbl, symbols[11], symbols[11] + lengths[11]));
  ck_assert_int_eq(13, ubw_stbl_intern(&stbl, symbols[12], symbols[12] + lengths[12]));
  ck_assert_int_eq(14, ubw_stbl_intern(&stbl, symbols[13], symbols[13] + lengths[13]));
  ck_assert_int_eq(15, ubw_stbl_intern(&stbl, symbols[14], symbols[14] + lengths[14]));
  ck_assert_int_eq(16, ubw_stbl_intern(&stbl, symbols[15], symbols[15] + lengths[15]));

  // And lookup

  ck_assert_int_eq(1, ubw_stbl_intern(&stbl, symbols[0], symbols[0] + lengths[0]));
  ck_assert_int_eq(2, ubw_stbl_intern(&stbl, symbols[1], symbols[1] + lengths[1]));
  ck_assert_int_eq(3, ubw_stbl_intern(&stbl, symbols[2], symbols[2] + lengths[2]));
  ck_assert_int_eq(4, ubw_stbl_intern(&stbl, symbols[3], symbols[3] + lengths[3]));
  ck_assert_int_eq(5, ubw_stbl_intern(&stbl, symbols[4], symbols[4] + lengths[4]));
  ck_assert_int_eq(6, ubw_stbl_intern(&stbl, symbols[5], symbols[5] + lengths[5]));
  ck_assert_int_eq(7, ubw_stbl_intern(&stbl, symbols[6], symbols[6] + lengths[6]));
  ck_assert_int_eq(8, ubw_stbl_intern(&stbl, symbols[7], symbols[7] + lengths[7]));
  ck_assert_int_eq(9, ubw_stbl_intern(&stbl, symbols[8], symbols[8] + lengths[8]));
  ck_assert_int_eq(10, ubw_stbl_intern(&stbl, symbols[9], symbols[9] + lengths[9]));
  ck_assert_int_eq(11, ubw_stbl_intern(&stbl, symbols[10], symbols[10] + lengths[10]));
  ck_assert_int_eq(12, ubw_stbl_intern(&stbl, symbols[11], symbols[11] + lengths[11]));
  ck_assert_int_eq(13, ubw_stbl_intern(&stbl, symbols[12], symbols[12] + lengths[12]));
  ck_assert_int_eq(14, ubw_stbl_intern(&stbl, symbols[13], symbols[13] + lengths[13]));
  ck_assert_int_eq(15, ubw_stbl_intern(&stbl, symbols[14], symbols[14] + lengths[14]));
  ck_assert_int_eq(16, ubw_stbl_intern(&stbl, symbols[15], symbols[15] + lengths[15]));
}
END_TEST

/**
 * @brief This is exactly the same as intern_forward(), in reverse order.
 *
 * This actually makes sense: the hash function may hide a bug if
 * symbols are interned in some natural hash order.  This guarantees
 * the order will be broken as some point.
 */
START_TEST (intern_backward)
{
  ck_assert_int_eq(1, ubw_stbl_intern(&stbl, symbols[15], symbols[15] + lengths[15]));
  ck_assert_int_eq(2, ubw_stbl_intern(&stbl, symbols[14], symbols[14] + lengths[14]));
  ck_assert_int_eq(3, ubw_stbl_intern(&stbl, symbols[13], symbols[13] + lengths[13]));
  ck_assert_int_eq(4, ubw_stbl_intern(&stbl, symbols[12], symbols[12] + lengths[12]));
  ck_assert_int_eq(5, ubw_stbl_intern(&stbl, symbols[11], symbols[11] + lengths[11]));
  ck_assert_int_eq(6, ubw_stbl_intern(&stbl, symbols[10], symbols[10] + lengths[10]));
  ck_assert_int_eq(7, ubw_stbl_intern(&stbl, symbols[9], symbols[9] + lengths[9]));
  ck_assert_int_eq(8, ubw_stbl_intern(&stbl, symbols[8], symbols[8] + lengths[8]));
  ck_assert_int_eq(9, ubw_stbl_intern(&stbl, symbols[7], symbols[7] + lengths[7]));
  ck_assert_int_eq(10, ubw_stbl_intern(&stbl, symbols[6], symbols[6] + lengths[6]));
  ck_assert_int_eq(11, ubw_stbl_intern(&stbl, symbols[5], symbols[5] + lengths[5]));
  ck_assert_int_eq(12, ubw_stbl_intern(&stbl, symbols[4], symbols[4] + lengths[4]));
  ck_assert_int_eq(13, ubw_stbl_intern(&stbl, symbols[3], symbols[3] + lengths[3]));
  ck_assert_int_eq(14, ubw_stbl_intern(&stbl, symbols[2], symbols[2] + lengths[2]));
  ck_assert_int_eq(15, ubw_stbl_intern(&stbl, symbols[1], symbols[1] + lengths[1]));
  ck_assert_int_eq(16, ubw_stbl_intern(&stbl, symbols[0], symbols[0] + lengths[0]));

  // And lookup


  ck_assert_int_eq(1, ubw_stbl_intern(&stbl, symbols[15], symbols[15] + lengths[15]));
  ck_assert_int_eq(2, ubw_stbl_intern(&stbl, symbols[14], symbols[14] + lengths[14]));
  ck_assert_int_eq(3, ubw_stbl_intern(&stbl, symbols[13], symbols[13] + lengths[13]));
  ck_assert_int_eq(4, ubw_stbl_intern(&stbl, symbols[12], symbols[12] + lengths[12]));
  ck_assert_int_eq(5, ubw_stbl_intern(&stbl, symbols[11], symbols[11] + lengths[11]));
  ck_assert_int_eq(6, ubw_stbl_intern(&stbl, symbols[10], symbols[10] + lengths[10]));
  ck_assert_int_eq(7, ubw_stbl_intern(&stbl, symbols[9], symbols[9] + lengths[9]));
  ck_assert_int_eq(8, ubw_stbl_intern(&stbl, symbols[8], symbols[8] + lengths[8]));
  ck_assert_int_eq(9, ubw_stbl_intern(&stbl, symbols[7], symbols[7] + lengths[7]));
  ck_assert_int_eq(10, ubw_stbl_intern(&stbl, symbols[6], symbols[6] + lengths[6]));
  ck_assert_int_eq(11, ubw_stbl_intern(&stbl, symbols[5], symbols[5] + lengths[5]));
  ck_assert_int_eq(12, ubw_stbl_intern(&stbl, symbols[4], symbols[4] + lengths[4]));
  ck_assert_int_eq(13, ubw_stbl_intern(&stbl, symbols[3], symbols[3] + lengths[3]));
  ck_assert_int_eq(14, ubw_stbl_intern(&stbl, symbols[2], symbols[2] + lengths[2]));
  ck_assert_int_eq(15, ubw_stbl_intern(&stbl, symbols[1], symbols[1] + lengths[1]));
  ck_assert_int_eq(16, ubw_stbl_intern(&stbl, symbols[0], symbols[0] + lengths[0]));
}
END_TEST

/**
 * @brief Intern some symbols, then look them up by ID.  Check we
 * receive correct values.
 */
START_TEST (reverse_lookup)
{
  ck_assert_int_eq(1, ubw_stbl_intern(&stbl, symbols[0], symbols[0] + lengths[0]));
  ck_assert_int_eq(2, ubw_stbl_intern(&stbl, symbols[1], symbols[1] + lengths[1]));
  ck_assert_int_eq(3, ubw_stbl_intern(&stbl, symbols[2], symbols[2] + lengths[2]));
  ck_assert_int_eq(4, ubw_stbl_intern(&stbl, symbols[3], symbols[3] + lengths[3]));
  ck_assert_int_eq(5, ubw_stbl_intern(&stbl, symbols[4], symbols[4] + lengths[4]));
  ck_assert_int_eq(6, ubw_stbl_intern(&stbl, symbols[5], symbols[5] + lengths[5]));
  ck_assert_int_eq(7, ubw_stbl_intern(&stbl, symbols[6], symbols[6] + lengths[6]));
  ck_assert_int_eq(8, ubw_stbl_intern(&stbl, symbols[7], symbols[7] + lengths[7]));

  ck_assert_str_eq(symbols[0], ubw_stbl_reverse(&stbl, 1));
  ck_assert_str_eq(symbols[1], ubw_stbl_reverse(&stbl, 2));
  ck_assert_str_eq(symbols[2], ubw_stbl_reverse(&stbl, 3));
  ck_assert_str_eq(symbols[3], ubw_stbl_reverse(&stbl, 4));
  ck_assert_str_eq(symbols[4], ubw_stbl_reverse(&stbl, 5));
  ck_assert_str_eq(symbols[5], ubw_stbl_reverse(&stbl, 6));
  ck_assert_str_eq(symbols[6], ubw_stbl_reverse(&stbl, 7));
  ck_assert_str_eq(symbols[7], ubw_stbl_reverse(&stbl, 8));
}
END_TEST

Suite * stbl_c_suite() {
  Suite *s = suite_create("stbl.c");
  TCase *tc;

  tc = ubw_tcase(s, "Build configuration");
  tcase_add_test(tc, symbhash_size);

  tc = ubw_tcase(s, "Hash functions");
  tcase_add_test(tc, hash_fnv1_32);

  tc = ubw_tcase(s, "Table use");
  tcase_add_checked_fixture(tc, stbl_c_setup, stbl_c_teardown);
  tcase_add_test(tc, intern_forward);
  tcase_add_test(tc, intern_backward);

  tcase_add_test(tc, reverse_lookup);

  return s;
}
