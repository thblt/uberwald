#include <stdlib.h>

#include "store.h"
#include "object.h"

ubw_store * ubw_store_create(int heap_sz, int symt_sz) {
  ubw_store *ret = malloc(sizeof(ubw_obj*));
  ubw_store_init(ret, heap_sz, symt_sz);
  return ret;
}

void ubw_store_init(ubw_store *s, int heap_sz, int symt_sz) {
  s->heap_c = 0;
  s->heap_sz = heap_sz;
  s->symt_c = 0;
  s->symt_sz = symt_sz;

  if (0 < heap_sz)
    s->heap = malloc(heap_sz*sizeof(ubw_obj));
  else
    s->heap = NULL;

  if (0 < symt_sz)
    s->symt = malloc(symt_sz*sizeof(ubw_symb));
  else
    s->symt = NULL;
}

struct ubw_obj * ubw_store_new(ubw_store *store) {
  // @FIXME This is a test implementation.
  return malloc(sizeof(ubw_obj));
}

struct ubw_obj * ubw_store_malloc(ubw_store *store, int n) {
  // @FIXME This is a test implementation.
  return malloc(n * sizeof(ubw_obj));
}
