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

typedef struct {
  ubw_obj *name;
} ubw_symbol;

enum ubw_objtype {
  LIST,
  VECTOR,

  INTEGER,
  FLOAT,
  STRING,

  SYMBOL,
  KEYWORD,

  CFUNC, // Native function
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

  ubw_symbol symbol;
  ubw_symbol keyword;

  ubw_cfunc cfunc;
};

struct ubw_obj {
  enum ubw_objtype type;
  union ubw_objdata data;
};

// * Lists
/** @brief Determine whether o is a list. */
ubw_bool ubw_list_p (ubw_obj *o);
/** @brief Initialize a new list. */
void ubw_list_init (ubw_obj *o, ubw_obj *car, ubw_obj *cdr);
ubw_obj * ubw_list_car (ubw_obj *list);
ubw_obj * ubw_list_cdr (ubw_obj *list);
#define ubw_list_new(store, car, cdr) ubw_list_init(ubw_store_new(store), car, cdr)

// * Vectors
ubw_bool ubw_vector_p (ubw_obj *o);
void ubw_vector_init (ubw_obj *o, ubw_vector v);
ubw_vector * ubw_vector_unbox (ubw_obj *vec);
ubw_obj * ubw_vector_nth (ubw_obj *vec, int nth);

// * "Booleans"
ubw_bool ubw_obj2bool(ubw_obj * o);

// * Integers
ubw_obj *ubw_int_p (ubw_obj *o);
void ubw_int_init (ubw_obj *o, ubw_int v);
int ubw_int_unbox (ubw_obj *vec);
#define ubw_int_new(store, val) ubw_int_init(ubw_store_new(store), v)
