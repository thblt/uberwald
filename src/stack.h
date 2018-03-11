#pragma once

#include "common.h"
#include "object.h"

#define DECL_STACK(name, type)                        \
  typedef struct {                                    \
    type * stack;                                     \
    int index;                                        \
    int capacity;                                     \
    int underflow;                                    \
    int overflow;                                     \
  } name ## _t;                                       \
                                                      \
  void name ## _init(name ## _t * s, int capacity);   \
  name ## _t * name ## _new(int size);                \
  type * name ## _peek(name ## _t * s);               \
  type * name ## _safe_peek(name ## _t * s);          \
  type * name ## _pop(name ## _t * s);                \
  type * name ## _safe_pop(name ## _t * s);           \
  type * name ## _push(name ## _t * s, type * o);       \
  type * name ## _safe_push(name ## _t * s, type * o);  \
                                                      \
  inline int name ## _length(name ## _t * s) {        \
    return s->index;                                  \
  }                                                   \
                                                      \
  inline int name ## _capacity(name ## _t * s) {      \
    return s->capacity;                               \
  }                                                   \



DECL_STACK (lostk, ubw_obj)
