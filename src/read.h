#pragma once

#include "ltypes.h"

struct ubw_read_state {
  LispObject * stack;
  int stack_head;
};

/** read Lisp from a C-type string.  This is only a thin wrapper
    around the actual read function. */
LispObject ** cstr_read(char ** s);

/** read Lisp from a Lisp string. */
DEFN_1(ubw_read, "read", str);

int read_dispatch(char * buf, int pos);
