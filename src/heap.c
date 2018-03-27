#include <stdlib.h>
#include <stdio.h>

#include "heap.h"
#include "object.h"

ubw_heap * ubw_heap_init(ubw_heap *s, int sz, ubw_obj *dptr) {
  // @FIXME Implement
  return s;
}

struct ubw_obj * ubw_heap_new(ubw_heap *heap) {
  // @FIXME This is a test implementation.
  ubw_obj *ret = malloc(sizeof(ubw_obj));
  return ret;
}

struct ubw_obj * ubw_heap_alloc(ubw_heap *heap, int n) {
  // @FIXME
  return malloc(n * sizeof(ubw_obj));
}

ubw_obj * ubw_es_alloc(ubw_heap *h, int sz) {
  if (NULL != h->es) return NULL;

  h->es = malloc(sizeof(ubw_obj) * sz);

  return h->es;
}
