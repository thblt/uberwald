// This file defines the primitive Lisp types used in Lispy.

#pragma once

#include <stdint.h>

#include "common.h"

// * Lists

struct list_t {
  struct obj_t * car;
  struct obj_t * cdr;
};

// * Vectors

struct vector_t {
  int capacity;
  int size;
  int increment;
  struct obj_t ** data;
};

// * Booleans

typedef enum { NIL=0, T=1 }  bool_t;

// * Integer

typedef int integer_t;

// * Floats

typedef double fpn_t;

// * Strings

// Strings are Unicode scalar values (as in Racket), so we need at least 21 bits integers.

typedef int_least32_t** string_t;
string_t cstr_lstr(char ** cstr);

struct nfunc_t {
  struct obj_t * (*func)(struct obj_t*);
};

struct sform_t {
  struct obj_t * (*func)(struct obj_t*);
};

union primitive_t {
  struct list_t list;
  struct vector_t vector;

  bool_t bool;
  integer_t integer;
  fpn_t fpn;
  string_t string;

  struct nfunc_t nfunc;
  struct sform_t sform;
};

enum type_t {
  LIST,
  VECTOR,

  BOOLEAN,
  INTEGER,
  FPN,
  STRING,

  KEYWORD,
  SYMBOL,

  CFUNC, // Native function
  SFORM, // Special form
};

struct obj_t {
  enum type_t type;
  union primitive_t obj;
};

typedef struct obj_t LispObject;

#define DECL_INITIALIZER(name, ctype) \
  void ubw_init ## name(LispObject * o, ctype v); \
  LispObject * ubw_new ## name(ctype v); \
  ctype ubw_get ## name (LispObject * o);

DEFN_1 (list_p, "list?",o);
DEFN_1 (list_car, "car",o);
DEFN_1 (list_cdr, "cdr",o);

DEFN_1 (vector_p, "vector?",o);
struct vector_t * vector_init(int capacity, int increment);
int vector_push(struct vector_t * v, struct obj_t o);
int vector_grow(struct vector_t * v);
void vector_free(struct vector_t * v);

DEFN_1 (bool_p, "boolean?",o);
DECL_INITIALIZER (bool,bool_t)

DECL_INITIALIZER (integer,integer_t)
DEFN_1 (integer_p, "integer?",o);

DECL_INITIALIZER (fpn,fpn_t)
DEFN_1 (float_p, "float?",o);
DEFN_1 (string_p, "string?",o);
DEFN_1 (keyword_p, "keyword?",o);
DEFN_1 (symbol_p, "symbol?",o);
DEFN_1 (native_func_p, "machine-function?",o);
DEFN_1 (special_form_p, "special-form?",o);
