#include "check.h"

#include "../src/ltypes.h"

START_TEST (integers)
{
  ck_assert_int_eq (ubw_getinteger(ubw_newinteger(3)), 3);
}
END_TEST
