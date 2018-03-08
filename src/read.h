#pragma once

#include "ltypes.h"
#include "stack.h"

/**
  * reader state.
  */
struct ubw_read_state {
  /** the list and vector stack */
  lostk_t stack;
  /** the head of the current list, where the next object will be pushed */
  LispObject * head;
  /** The current position in input data */
  int pos,
  /** The current line in input data, for error reporting */
    line,
  /** The current column in input data, for error reporting */
    col;
};

/** reader error */
struct ubw_read_error {
  int pos,
    line,
    col;
  char * error;
};

/** read Lisp from a C-type string.  This is only a thin wrapper
    around the actual read function. */
LispObject ** cstr_read(char ** s);

/** read Lisp from a Lisp string. */
DEFN_1(ubw_read, "read", str);

int read_dispatch(char * buf, int pos);
