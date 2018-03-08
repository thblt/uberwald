#include <stdlib.h>

#include "stack.h"

#define IMPL_STACK(name,type)                           \
  void name ## _init(name ## _t * s, int capacity) {    \
    s->stack = malloc(capacity * sizeof(type));         \
    s->capacity = capacity;                             \
    s->index = 0;                                       \
    s->overflow = 0;                                    \
    s->underflow = 0;                                   \
  }                                                     \
                                                        \
  name ## _t * name ## _new(int capacity) {             \
    name ## _t * ret = malloc(sizeof(name ## _t));      \
    name ## _init(ret, capacity);                       \
    return ret;                                         \
  }                                                     \
                                                        \
  int name ## _length(name ## _t * s) {                 \
    return s->index;                                    \
  }                                                     \
                                                        \
  type * name ## _peek(name ## _t * s) {                \
    return & s->stack[s->index-1];                      \
  }                                                     \
                                                        \
  type * name ## _safe_peek(name ## _t * s) {           \
    if (name ## _length(s)) {                           \
      return name ## _peek(s);                          \
    } else {                                            \
      s->underflow++;                                   \
      return (type *) 0x00;                             \
    }                                                   \
  }                                                     \
                                                        \
  type * name ## _pop(name ## _t * s) {                 \
    type * ret = name ## _peek(s);                      \
    s->index--;                                         \
    return ret;                                         \
  }                                                     \
                                                        \
  type * name ## _safe_pop(name ## _t * s) {            \
    if (name ## _length(s)) {                           \
      return name ## _pop(s);                           \
    } else {                                            \
      return 0x00;                                      \
      s->underflow++;                                   \
    }                                                   \
  }                                                     \
                                                        \
  void name ## _push (name ## _t * s, type * o) {       \
    s->stack[s->index] = * o;                           \
    s->index++;                                         \
  }                                                     \
  void name ## _safe_push (name ## _t * s, type * o) {  \
    if (s->index < s->capacity) {                       \
      s->stack[s->index] = * o;                         \
      s->index++;                                       \
    } else {                                            \
      s->overflow++;                                    \
    }                                                   \
  }                                                     \


IMPL_STACK(lostk, LispObject)
