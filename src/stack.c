#include <stdlib.h>

#include "stack.h"

#define IMPL_STACK(name,type)                       \
  name ## _t * name ## _init(int capacity) {        \
    name ## _t * ret = malloc(sizeof(name ## _t));  \
    ret->stack = malloc(capacity * sizeof(type));   \
    ret->capacity = capacity;                       \
    ret->index = 0;                                 \
    return ret;                                     \
  }                                                 \
                                                    \
  int name ## _length(name ## _t * s) {             \
    return s->index;                                \
  }                                                 \
                                                    \
  type * name ## _peek(name ## _t * s) {            \
    return & s->stack[s->index-1];                  \
  }                                                 \
                                                    \
  type * name ## _safe_peek(name ## _t * s) {       \
    if (name ## _length(s)) {                       \
      return name ## _peek(s);                      \
    } else {                                        \
      s->underflow++;                               \
      return (type *) 0x00;                         \
    }                                               \
  }                                                 \
                                                    \
  type * name ## _pop(name ## _t * s) {             \
    s->index--;                                     \
    return name ## _peek(s);                        \
  }                                                 \
                                                    \
  type * name ## _safe_pop(name ## _t * s) {        \
    if (name ## _length(s)) {                       \
      return name ## _pop(s);                       \
    } else {                                        \
      return 0x00;                                  \
      s->underflow++;                               \
    }                                               \
  }                                                 \
                                                    \
  void name ## _push (name ## _t * s, type * o) {   \
    s->stack[s->index] = * o;                       \
    s->index += 1;                                  \
  }                                                 \

IMPL_STACK(lo_stk, LispObject)
