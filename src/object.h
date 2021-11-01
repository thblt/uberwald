/**
 * @file
 * @brief Lisp object
 *
 * The primitive Lisp structures, along with a few utility functions for inspecting them.
 *
 * @defgroup config_object Configuration directives for object.h
 */

#pragma once

#include <stdlib.h>

#include "config.h"

typedef struct ubw_obj ubw_obj;

// * Vectors
typedef struct {
  int capacity;
  int size;
  int increment;
  ubw_obj *data;
} ubw_vector;

typedef char* ubw_string;

/** @brief
*/
typedef struct {
  /** @brief The function
   *
   *  */
  void *(*f)();

  /** \enum ubw_cfunc_args
   *
   * */
  enum ubw_cfunc_argc
    {
     UBW_ARGC0, UBW_ARGC0V, UBW_ARGC1, UBW_ARGC1V, UBW_ARGC2, UBW_ARGC2V,
     UBW_ARGC3, UBW_ARGC3V, UBW_ARGC4, UBW_ARGC4V, UBW_ARGC5, UBW_ARGC5V,
     UBW_ARGC6, UBW_ARGC6V, UBW_ARGC7, UBW_ARGC7V, UBW_ARGC8, UBW_ARGC8V,
     UBW_ARGC9, UBW_ARGC9V, UBW_ARGC10, UBW_ARGC10V, UBW_ARGC11, UBW_ARGC11V,
     UBW_ARGC12, UBW_ARGC12V, UBW_ARGC13, UBW_ARGC13V, UBW_ARGC14, UBW_ARGC14V,
     UBW_ARGC15, UBW_ARGC15V, UBW_ARGC16, UBW_ARGC16V, UBW_ARGC17, UBW_ARGC17V,
     UBW_ARGC18, UBW_ARGC18V, UBW_ARGC19, UBW_ARGC19V, UBW_ARGC20, UBW_ARGC20V,
     UBW_ARGC21, UBW_ARGC21V, UBW_ARGC22, UBW_ARGC22V, UBW_ARGC23, UBW_ARGC23V,
     UBW_ARGC24, UBW_ARGC24V, UBW_ARGC25, UBW_ARGC25V, UBW_ARGC26, UBW_ARGC26V,
     UBW_ARGC27, UBW_ARGC27V, UBW_ARGC28, UBW_ARGC28V, UBW_ARGC29, UBW_ARGC29V,
     UBW_ARGC30, UBW_ARGC30V
    }
    argc;
} ubw_cfunc;

/**
 * @brief The primitive Lisp object.
 *
 * \warning This documentation is provided for information only.
 */
struct ubw_obj {

  /** @type @brief Possible types of a Lisp object. */
  enum {
    LIST,   //!< @brief List
    VECTOR, //!< @brief Vector

    INTEGER, //!< @brief Integer
    FLOAT, //!< @brief Float
    CHAR, //!< @brief Character
    STRING, //!< @brief String

    SYMBOL, //!< @brief Regular symbol
    KEYWORD, //!< @brief Keyword

    CFUNC, //!< @brief Native function @see ubw_cfunc

    _DELETED
  }

    /** \var type
        @brief The type of this object. */
    type;

  /** @brief The value of this object. */
  union {
    struct { ubw_obj *car, *cdr; } list;
    ubw_vector vector;

    ubw_int integer;
    ubw_float fpn;
    ubw_char character;
    ubw_string string;

    ubw_symbid symbol;
    ubw_symbid keyword;

    ubw_cfunc cfunc;
  };
};


// * Predicates

/** @brief Determine whether `o` is a list */
inline bool ubw_list_p(ubw_obj *o) { return o->type == LIST; }
/** @brief Determine whether `o` is a vector */
inline bool ubw_vector_p(ubw_obj *o) { return o->type == VECTOR; }
/** @brief Determine whether `o` is an integer */
inline bool ubw_int_p(ubw_obj *o) { return o->type == INTEGER; }
/** @brief Determine whether `o` is a floating-point number */
inline bool ubw_float_p(ubw_obj *o) { return o->type == FLOAT; }
/** @brief Determine whether `o` is a character */
inline bool ubw_char_p(ubw_obj *o) { return o->type == CHAR; }
/** @brief Determine whether `o` is a string */
inline bool ubw_string_p(ubw_obj *o) { return o->type == STRING; }
/** @brief Determine whether `o` is a symbol */
inline bool ubw_symbol_p(ubw_obj *o) { return o->type == SYMBOL; }
/** @brief Determine whether `o` is a keyword */
inline bool ubw_keyword_p(ubw_obj *o) { return o->type == KEYWORD; }
/** @brief Determine whether `o` is a pointer to a C function */
inline bool ubw_cfunc_p(ubw_obj *o) { return o->type == CFUNC; }

// * Unboxing functions
/** @brief Return the contents of `o` as a vector.
 *
 * \note If assertions are enabled and `o` is not of the correct type,
 * this function will abort execution.
 */
inline ubw_vector ubw_vector_unbox(ubw_obj *o) {
  assert(ubw_vector_p(o));
  return o->vector;
}

/** @brief Return the contents of `o` as a int.
 *
 * \note If assertions are enabled and `o` is not of the correct type,
 * this function will abort execution.
 */
inline ubw_int ubw_int_unbox(ubw_obj *o) {
  assert(ubw_int_p(o));
  return o->integer;
}
/** @brief Return the contents of `o` as a float.
 *
 * \note If assertions are enabled and `o` is not of the correct type,
 * this function will abort execution.
 */

inline ubw_float ubw_float_unbox(ubw_obj *o) {
  assert(ubw_float_p(o));
  return o->fpn;
}

/** @brief Return the contents of `o` as a char.
 *
 * \note If assertions are enabled and `o` is not of the correct type,
 * this function will abort execution.
 */
inline ubw_char ubw_char_unbox(ubw_obj *o) {
  assert(ubw_char_p(o));
  return o->character;
}

/** @brief Return the contents of `o` as a string.
 *
 * \note If assertions are enabled and `o` is not of the correct type,
 * this function will abort execution.
 */
inline ubw_string ubw_string_unbox(ubw_obj *o) {
  assert(ubw_string_p(o));
  return o->string;
}
/** @brief Return the contents of `o` as a symbol.
 *
 * \note If assertions are enabled and `o` is not of the correct type,
 * this function will abort execution.
 */
inline ubw_symbid ubw_symbol_unbox(ubw_obj *o) {
  assert(ubw_symbol_p(o));
  return o->symbol;
}
/** @brief Return the contents of `o` as a keyword.
 *
 * \note If assertions are enabled and `o` is not of the correct type,
 * this function will abort execution.
 */
inline ubw_symbid ubw_keyword_unbox(ubw_obj *o) {
  assert(ubw_keyword_p(o));
  return o->keyword;
}
/** @brief Return the contents of `o` as a cfunc.
 *
 * \note If assertions are enabled and `o` is not of the correct type,
 * this function will abort execution.
 */
inline ubw_cfunc ubw_cfunc_unbox(ubw_obj *o) {
  assert(ubw_cfunc_p(o));
  return o->cfunc;
}



// * Lists
/** @brief Initialize a new list
 *
 * @param o the object to initialize
 * @param car the car of the list
 * @param cdr the cdr of the list
 */
ubw_obj * ubw_list_init (ubw_obj *o, ubw_obj *car, ubw_obj *cdr);
#define ubw_list_new(heap, car, cdr) ubw_list_init(ubw_new(heap), car, cdr)

/** @brief Return the car of `o`. */
inline ubw_obj * ubw_list_car (ubw_obj *list) {
  return list->list.car;
}

/** @brief Return the cdr of `o`. */
inline ubw_obj * ubw_list_cdr (ubw_obj *list) {
  return list->list.cdr;
}

// * Vectors
ubw_obj * ubw_vector_init (ubw_obj *o);
ubw_obj * ubw_vector_nth (ubw_obj *vec, int nth);

// * "Booleans"
bool ubw_obj2bool(ubw_obj * o);

// * Integers
ubw_obj * ubw_int_init (ubw_obj *o, ubw_int v);
#define ubw_int_new(heap, val) ubw_int_init(ubw_new(heap), val)


// * Floats

ubw_obj * ubw_float_init (ubw_obj *o, ubw_float v);
#define ubw_float_new(heap, val) ubw_float_init(ubw_new(heap), v)


// * Chars
ubw_obj * ubw_char_init (ubw_obj *o, ubw_char c);

// * Strings
ubw_obj * ubw_string_init (ubw_obj *o, ubw_string s);

/** @brief Initialize `o` as a symbol.
 *
 * Symbols and keywords have the exact same internal representation, a
 * value of type `ubw_symbid`, and differ only by their tag.  except
 * for the tag.  The difference between them is semantic: a symbol
 * evaluates to a value stored in an environment, where a keyword
 * evaluates to itself.
 *
 * @param i the symbol id, as returned by `ubw_stbl_intern()`.
 */
ubw_obj * ubw_symbol_init (ubw_obj *o, ubw_symbid i);
#define ubw_symbol_new(heap, val) ubw_symbol_init(ubw_new(heap), v)

// * Keywords

/** @brief Initialize `o` as a keyword.
 *
 * @see ubw_symbol_init() */

ubw_obj * ubw_keyword_init (ubw_obj *o, ubw_symbid i);
#define ubw_keyword_new(heap, val) ubw_keyword_init(ubw_new(heap), v)

// * CFunc

/** @brief Initialize `o` as a foreign C function.
 *
 * This exposes a pointer to a C function to Lisp code, so that this
 * function can be called as any Lisp function.
 *
 * To be usable, a C function must have the following properties:
 *
 * - take a `const ubw_rt *` as its first argument.  This argument is
 *   the **runtime**, to which C functions have full access.
 *
 * - take between 0 and 31 `const ubw_obj *` as its only supplementary
 *   arguments.  These are the **Lisp arguments**.
 *
 * - return an `ubw_obj *` (NULL is acceptable as a return value, but
 *   the function can't be declared `void`)
 *
 * For example:
 *
 *      ubw_obj * func(const ubw_rt * rt,
 *                     const ubw_obj *arg1,
 *                     const ubw_obj *arg2,
 *                     const ubw_obj *arg3);
 *
 * @param f The function to expose
 * @param argc The number of Lisp arguments this function expects.
 *
 * This is an anonymous enum type whose values have the forms
 * `UBW_ARGCn` and `UBW_ARGCnV`, where n is the number of arguments
 * the function takes.  `A3`, for example, means the function takes
 * exactly three arguments, *ie, that its prototype is:
 *
 * Values with the `V` suffix, like `A3V`, indicate that the
 * function is variadic, that is, it takes a certain number of
 * required arguments (here, 3) followed by any number of optional
 * of arguments.  The prototype if a variadic function of $n$
 * arguments is the same as a non-variadic function of $n-1$
 * arguments.  The definition above, for example, is a valid
 * prototype of `A3` or `A2V` functions.
 *
 * When calling a variadic function, it is guaranteed that the last
 * argument will always be a list.
 *
 * \endparblock
 *
 */
ubw_obj * ubw_cfunc_init(ubw_obj *o, void* (*f)(), enum ubw_cfunc_argc argc);
