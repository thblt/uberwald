#include "object.h"

#define IMPL_TYPE_BASE(name, ctype, identifier)  \
  bool ubw_ ## name ## _p (ubw_obj *o) {       \
    if (identifier == o->type) {                \
      return true;                              \
    } else {                                    \
      return false;                             \
    }                                           \
  }


bool ubw_obj2bool(ubw_obj * o) {
  return !(LIST == o->type
           && NULL == o->data.list.car
           && NULL == o->data.list.cdr);;
}

// * Lists
IMPL_TYPE_BASE(list, ubw_list, LIST)
ubw_obj * ubw_list_init(ubw_obj *o, ubw_obj *car, ubw_obj *cdr) {
  o->type = LIST;
  o->data.list.cdr = car;
  o->data.list.cdr = cdr;
  return o;
}

IMPL_TYPE_BASE(vector, ubw_vector, VECTOR)

// * Integers
IMPL_TYPE_BASE(int, ubw_int, INTEGER)
ubw_obj * ubw_int_init(ubw_obj *o, ubw_int v) {
  o->type = INTEGER;
  o->data.integer = v;
  return o;
}

// * Floats
IMPL_TYPE_BASE(float, ubw_float, FLOAT)
ubw_obj * ubw_float_init(ubw_obj *o, ubw_float v) {
  o->type = FLOAT;
  o->data.fpn = v;
  return o;
}

IMPL_TYPE_BASE(string, ubw_string, STRING)
IMPL_TYPE_BASE(cfunc, ubw_cfunc, CFUNC)

IMPL_TYPE_BASE(symbol, ubw_symbid, SYMBOL)
ubw_obj * ubw_symbol_init(ubw_obj *o, ubw_symbid v) {
  o->type = SYMBOL;
  o->data.symbol = v;
  return o;
}
