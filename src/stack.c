#include "stack.h"

ubw_stack* ubw_stack_init(ubw_stack *s, const int capacity, ubw_obj **dptr) {
  s->d = (NULL != dptr) ? dptr : malloc(capacity*sizeof(ubw_obj*));
  s->c = capacity;
  s->h = 0;

    return s;
}

ubw_obj * ubw_stack_peek(const ubw_stack *s) {
  if (0 < s->h) {
    return s->d[(s->h)-1];
  } else {
    return NULL;
  }
}

ubw_obj * ubw_stack_fpeek(const ubw_stack *s) {
  assert(0 < ubw_stack_length(s));
  return s->d[(s->h)-1];
}

ubw_obj * ubw_stack_pop(ubw_stack *s) {
  if (0 < s->h) {
    return s->d[--(s->h)];
  } else {
    return NULL;
  }
}

ubw_obj * ubw_stack_fpop(ubw_stack *s) {
  assert(0 < ubw_stack_length(s));
  return s->d[--(s->h)];
}

ubw_obj * ubw_stack_push(ubw_stack *s, ubw_obj *o) {
  if (s->h < s->c) {
    s->d[(s->h)++] = o;
    return s->d[s->h];
  } else {
    return NULL;
  }
}

ubw_obj * ubw_stack_fpush(ubw_stack *s, ubw_obj *o) {
  assert(s->h < s->c);
  s->d[s->h++] = o;
  return s->d[s->h];
}
