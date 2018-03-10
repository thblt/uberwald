#include <stdlib.h>

#include "store.h"
#include "object.h"

struct ubw_obj * ubw_store_new(ubw_store *store) {
  // @FIXME This is a test implementation.
  return malloc(sizeof(ubw_obj));
}

struct ubw_obj * ubw_store_malloc(ubw_store *store, int n) {
  // @FIXME This is a test implementation.
  return malloc(n * sizeof(ubw_obj));
}
