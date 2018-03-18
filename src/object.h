/** @file
    @brief The primitive Lisp structures, along with a few utility
    functions for inspecting them.
*/

#pragma once

#include <stdlib.h>

#include "common.h"

typedef struct ubw_obj ubw_obj;

typedef struct {
  ubw_obj *car;
  ubw_obj *cdr;
} ubw_list;

// * Vectors
typedef struct {
  int capacity;
  int size;
  int increment;
  ubw_obj *data;
} ubw_vector;

// * String
typedef struct {
  int length;
  ubw_char *data;
} ubw_string;

/** Tagging for ubw_obj */
enum ubw_objtype {
  LIST,   //!< List
  VECTOR, //!< Vector

  INTEGER, //!< Integer
  FLOAT, //!< Float
  CHAR, //!< Character
  STRING, //!< String

  SYMBOL, //!< Regular symbol
  KEYWORD, //!< Keyword

  CFUNC, //!< Native function

  _DELETED //!< Deleted object marker
};

typedef struct {
  enum  {
    A0,
    A0V,
    A1,
    A1V,
    A2,
    A2V,
    A3,
    A3V,
    A4,
    A4V,
    A5,
    A5V,
    A6,
    A6V,
    A7,
    A7V,
    A8,
    A8V,
    A9,
    A9V,
  } argc;
  ubw_obj *(*func)();
} ubw_cfunc;

union ubw_objdata {
  ubw_list list;
  ubw_vector vector;

  ubw_int integer;
  ubw_float fpn;
  ubw_char character;
  ubw_string string;

  ubw_symbid symbol;
  ubw_symbid keyword;

  ubw_cfunc cfunc;
};

struct ubw_obj {
  enum ubw_objtype type;
  union ubw_objdata data;
};

// * Lists
/** @brief Determine whether o is a list. */
bool ubw_list_p (ubw_obj *o);
/** @brief Initialize a new list. */
ubw_obj * ubw_list_init (ubw_obj *o, ubw_obj *car, ubw_obj *cdr);
#define ubw_list_new(store, car, cdr) ubw_list_init(ubw_store_new(store), car, cdr)

inline ubw_obj * ubw_list_car (ubw_obj *list) {
  return list->data.list.car;
}

inline ubw_obj * ubw_list_cdr (ubw_obj *list) {
  return list->data.list.cdr;
}

// * Vectors
bool ubw_vector_p (ubw_obj *o);
void ubw_vector_init (ubw_obj *o, ubw_vector v);
ubw_vector * ubw_vector_unbox (ubw_obj *o);
ubw_obj * ubw_vector_nth (ubw_obj *vec, int nth);

// * "Booleans"
bool ubw_obj2bool(ubw_obj * o);

// * Integers
bool ubw_int_p (ubw_obj *o);
ubw_obj * ubw_int_init (ubw_obj *o, ubw_int v);
#define ubw_int_new(store, val) ubw_int_init(ubw_store_new(store), val)
inline ubw_int ubw_int_unbox (ubw_obj *o) {
  return o->data.integer;
}


// * Floats
bool ubw_float_p (ubw_obj *o);
ubw_obj * ubw_float_init (ubw_obj *o, ubw_float v);
#define ubw_float_new(store, val) ubw_float_init(ubw_store_new(store), v)
inline ubw_float ubw_float_unbox (ubw_obj *o) {
  return o->data.fpn;
}

bool ubw_symbol_p (ubw_obj *o);
ubw_obj * ubw_symbol_init (ubw_obj *o, ubw_symbid v);
ubw_symbid * ubw_symbol_unbox (ubw_obj *o);
#define ubw_symbol_new(store, val) ubw_symbol_init(ubw_store_new(store), v)
