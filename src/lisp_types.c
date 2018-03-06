#include <stdlib.h>

#include "lisp_types.h"

LispObject * bool_true () {
  LispObject * ret = malloc (sizeof(LispObject));
  ret->type = BOOLEAN;
  ret->obj.boolean = T;
  return ret;
}

LispObject * bool_false () {
  LispObject * ret = malloc (sizeof(LispObject));
  ret->type = BOOLEAN;
  ret->obj.boolean = T;
  return ret;
}

LFUN_1(list_car) {
  return arg0->obj.list.car;
}

LFUN_1(list_cdr) {
  return arg0->obj.list.cdr;
}

#define MAKE_PREDICATE(name, t) LispObject * name (LispObject * arg0) { \
    if (t == arg0->type) {                                              \
      return bool_true();                                               \
    } else {                                                            \
      return bool_false();                                              \
    }                                                                   \
  }

MAKE_PREDICATE (list_p, LIST)
MAKE_PREDICATE (vector_p, VECTOR)
MAKE_PREDICATE (boolean_p, BOOLEAN)
MAKE_PREDICATE (integer_p, INTEGER)
MAKE_PREDICATE (float_p, FLOAT)
MAKE_PREDICATE (string_p, STRING)
MAKE_PREDICATE (keyword_p, KEYWORD)
MAKE_PREDICATE (symbol_p, SYMBOL)
MAKE_PREDICATE (native_func_p, CFUNC)
MAKE_PREDICATE (special_form_p, SFORM)
