#include <stdlib.h>

#include "ltypes.h"

#define IMPL_TYPE(name, ctype, identifier)                 \
  LispObject * ubw_ ## name ## _p (LispObject * o) {              \
    if (identifier == o->type) {                                  \
      return ubw_newbool(T);                                      \
    } else {                                                      \
      return ubw_newbool(NIL);                                    \
    }                                                             \
  }                                                               \
                                                                  \
  void ubw_init ## name (LispObject * o, ctype v) {               \
    o->type = identifier;                                         \
    o->obj.name = v;                                              \
  }                                                               \
                                                                  \
  LispObject * ubw_new ## name (ctype v) {                        \
    LispObject * ret = malloc(sizeof(LispObject));                \
    ubw_init ## name(ret, v);                                     \
    return ret;                                                   \
  }                                                               \
                                                                  \
  ctype ubw_get ## name (LispObject * o) {                        \
    if (identifier == o->type) {                                  \
      return o->obj.name;                                        \
    } else {                                                      \
      /* @FIXME */                                                \
    }\
  }                                             \

DEFN_1(list_car,,o) {
  return o->obj.list.car;
}

DEFN_1(list_cdr,,o) {
  return o->obj.list.cdr;
}

// Bool *must* come first, because predicates functions return a Lisp boolean.
IMPL_TYPE(bool, bool_t, BOOLEAN)


IMPL_TYPE(integer, integer_t, INTEGER)
IMPL_TYPE(fpn, fpn_t, FPN)
