#pragma once

#include "object.h"
#include "stack.h"

/** reader error */
typedef struct {
  int pos,
    line,
    col;
  char * msg;
} ubw_rderr_t;

/**
  * reader state.
  */
typedef struct {
  char * buf;
  /** the list and vector stack */
  lostk_t stack;
  /** the head of the current list, where the next object will be pushed */
  ubw_obj * head;
  /** The current position in input data */
  int pos,
  /** The current line in input data, for error reporting */
    line,
  /** The current column in input data, for error reporting */
    col;
  /** The last error.  This should be initialized to the null pointer,
      and the read function should check for it. */
  ubw_rderr_t * err;
} ubw_rdst_t;

/** read Lisp from a C-type string.  This is only a thin wrapper
    around the actual read function. */
ubw_obj ** cstr_read(char ** s);

/** read Lisp from a Lisp string. */
void ubw_read(char * str);

#ifdef _UBERWALD_INTERNALS
int next_sep(ubw_rdst_t * st);
void read_unknown(ubw_rdst_t * st);
void begin_list(ubw_rdst_t * st);
void end_list(ubw_rdst_t * st);
void begin_vector(ubw_rdst_t * st);
void end_vector(ubw_rdst_t * st);
#endif
