#include <stdio.h> // @FIXME Remove when raise works.

#include "eval.h"

LispObject * ubw_error = 0x00;

void ubw_raise(char * msg) {
  printf("ERROR! %s\n", msg); // @FIXME Correctly implement error handling.
}

DEFN_2(ubsw_lraise,, exception, msg) {
    return 0x00;
}
