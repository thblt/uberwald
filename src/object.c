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
  o->data.list.car = car;
  o->data.list.cdr = cdr;
  return o;
}

// * Vectors

IMPL_TYPE_BASE(vector, ubw_vector, VECTOR)
ubw_obj * ubw_vector_init(ubw_obj *o) {
  o->type = VECTOR;
  return o;
}

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

// * Chars

IMPL_TYPE_BASE(char, ubw_char, CHAR)
ubw_obj * ubw_char_init(ubw_obj *o, ubw_char c) {
  o->type = CHAR;
  o->data.character = c;
  return o;
}

IMPL_TYPE_BASE(string, ubw_string, STRING)
ubw_obj * ubw_string_init(ubw_obj *o, ubw_string s) {
  o->type = STRING;
  o->data.string = s;
  return o;
}

IMPL_TYPE_BASE(symbol, ubw_symbid, SYMBOL)
ubw_obj * ubw_symbol_init(ubw_obj *o, ubw_symbid v) {
  o->type = SYMBOL;
  o->data.symbol = v;
  return o;
}

IMPL_TYPE_BASE(keyword, ubw_symbod, KEYWORD)
ubw_obj * ubw_keyword_init(ubw_obj *o, ubw_symbid v) {
  o->type = KEYWORD;
  o->data.keyword = v;
  return o;
}

IMPL_TYPE_BASE(cfunc, ubw_cfunc, CFUNC)
ubw_obj * ubw_cfunc_init(ubw_obj *o, ubw_cfunc f) {
  o->type = CFUNC;
  o->data.cfunc = f;
  return o;
}
