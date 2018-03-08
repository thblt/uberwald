#pragma once

#include "common.h"
#include "ltypes.h"

/** The current error object */
extern LispObject * ubw_error;

void ubw_raise(char * msg);

/** Raise a Lisp exception.  Interrupt execution flow and rewind the
    stack until an appropriate handler is found. */
DEFN_2(ubw_lraise, "raise", exception, msg);
