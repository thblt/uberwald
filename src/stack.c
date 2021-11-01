#include "stack.h"

ubw_stack* ubw_stack_init(ubw_stack *s, const int capacity, ubw_obj **ptr) {
  s->head = s->beg = (NULL == ptr) ? malloc(capacity*sizeof(ubw_obj*)) : ptr;
  s->end = &s->beg[capacity];

  return s;
}

ubw_obj * ubw_stack_peek(const ubw_stack *s) {
  if (s->beg != s->head) { // Not empty
    return *(s->head-1);
  } else {
    return NULL;
  }
}

ubw_obj * ubw_stack_fpeek(const ubw_stack *s) {
  assert(0 < ubw_stack_length(s));
  return *(s->head - 1);
}

ubw_obj * ubw_stack_pop(ubw_stack *s) {
  if (s->beg != s->head) {
    return *--s->head;
  } else {
    return NULL;
  }
}

ubw_obj * ubw_stack_fpop(ubw_stack *s) {
  assert(0 < ubw_stack_length(s));
  return *--s->head;
}

ubw_obj * ubw_stack_push(ubw_stack *s, ubw_obj *o) {
  if (s->head < s->end) {
    *s->head = o;
    s->head++;
    return o;
  } else {
    return NULL;
  }
}

ubw_obj * ubw_stack_fpush(ubw_stack *s, ubw_obj *o) {
  assert(s->head < s->end);
  *s->head = o;
  s->head++;
  return o;
}
