#include "object.h"

bool ubw_obj2bool(ubw_obj * o) {
  return !(LIST == o->type
           && NULL == o->list.car
           && NULL == o->list.cdr);;
}

// * Lists
ubw_obj * ubw_list_init(ubw_obj *o, ubw_obj *car, ubw_obj *cdr) {
  o->type = LIST;
  o->list.car = car;
  o->list.cdr = cdr;
  return o;
}

// * Vectors
ubw_obj * ubw_vector_init(ubw_obj *o) {
  o->type = VECTOR;
  return o;
}

// * Integers
ubw_obj * ubw_int_init(ubw_obj *o, ubw_int v) {
  o->type = INTEGER;
  o->integer = v;
  return o;
}

// * Floats
ubw_obj * ubw_float_init(ubw_obj *o, ubw_float v) {
  o->type = FLOAT;
  o->fpn = v;
  return o;
}

// * Chars
ubw_obj * ubw_char_init(ubw_obj *o, ubw_char c) {
  o->type = CHAR;
  o->character = c;
  return o;
}

ubw_obj * ubw_string_init(ubw_obj *o, ubw_string s) {
  o->type = STRING;
  o->string = s;
  return o;
}

ubw_obj * ubw_symbol_init(ubw_obj *o, ubw_symbid v) {
  o->type = SYMBOL;
  o->symbol = v;
  return o;
}

ubw_obj * ubw_keyword_init(ubw_obj *o, ubw_symbid v) {
  o->type = KEYWORD;
  o->keyword = v;
  return o;
}

ubw_obj * ubw_cfunc_init(ubw_obj *o, void* (*f)(), enum ubw_cfunc_argc argc) {
  o->type = CFUNC;
  o->cfunc.f = f;
  o->cfunc.argc = argc;
  return o;
}
