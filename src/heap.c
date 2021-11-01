#include <stdlib.h>
#include <stdio.h>

#include "heap.h"

ubw_heap * ubw_heap_init(ubw_heap *h, int sz, ubw_obj *dptr) {

  h->h = (NULL == dptr) ? malloc(sizeof(ubw_obj)*sz) : dptr;
  h->es = NULL;

  h->map[0].s = dptr;
  h->map[0].e = &dptr[sz];

  for (int i = 1; i<UBW_HEAP_MAX_FRAGMENTATION; i++)
    h->map[i].s = NULL;

  return h;
}

struct ubw_obj * ubw_new(ubw_heap *heap) {
  // @FIXME This is a test implementation.
  ubw_obj *ret = malloc(sizeof(ubw_obj));
  return ret;
}

struct ubw_obj * ubw_malloc(ubw_heap *heap, int n) {
  // @FIXME
  return malloc(n * sizeof(ubw_obj));
}

ubw_obj * ubw_es_alloc(ubw_heap *h, int sz) {
  if (NULL != h->es) return NULL;

  h->es = malloc(sizeof(ubw_obj) * sz);

  return h->es;
}
