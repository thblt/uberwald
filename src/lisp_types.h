// This file defines the primitive Lisp types used in Lispy.

#include <stdint.h>

#define DEFN_0(name, lisp_name) LispObject * name ()
#define DEFN_1(name, lisp_name) LispObject * name (LispObject * arg0)
#define DEFN_MANY(name, lisp_name) LispObject * name (LispObject * args)

#define LFUN_0(name) LispObject * name ()
#define LFUN_1(name) LispObject * name (LispObject * arg0)
#define LFUN_MANY(name) LispObject * name (LispObject * args)


// Lists

struct list_t {
  struct obj_t * car;
  struct obj_t * cdr;
};

// Vectors

struct vector_t {
  int capacity;
  int size;
  int increment;
  struct obj_t ** data;
};

// Booleans

enum boolean_t { T, NIL };

// Integer

#define integer_t int

// Floats

#define float_t double

// Strings
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

  enum boolean_t boolean;
  integer_t integer;
  float_t fpn;
  string_t string;

  struct nfunc_t nfunc;
  struct sform_t sform;
};

enum type_t {
  LIST,
  VECTOR,

  BOOLEAN,
  INTEGER,
  FLOAT,
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

DEFN_1 (list_p, "list?");
DEFN_1 (list_car, "car");
DEFN_1 (list_cdr, "cdr");

DEFN_1 (vector_p, "vector?");
struct vector_t * vector_init(int capacity, int increment);
int vector_push(struct vector_t * v, struct obj_t o);
int vector_grow(struct vector_t * v);
void vector_free(struct vector_t * v);

DEFN_1 (list_p, "boolean?");

DEFN_1 (boolean_p, "boolean?");
LispObject * bool_true();
LispObject * bool_false();

DEFN_1 (integer_p, "integer?");
DEFN_1 (float_p, "float?");
DEFN_1 (string_p, "string?");
DEFN_1 (keyword_p, "keyword?");
DEFN_1 (symbol_p, "symbol?");
DEFN_1 (native_func_p, "machine-function?");
DEFN_1 (special_form_p, "special-form?");
