#pragma once

#include "ltypes.h"

#define DECL_STACK(name, type)                  \
  typedef struct {                              \
    type * stack;                               \
    int index;                               \
    int capacity;                                   \
    int underflow;                              \
    int overflow;                               \
  } name ## _t;                                 \
                                                \
  name ## _t * name ## _init(int size);         \

DECL_STACK (lo_stk, LispObject)
