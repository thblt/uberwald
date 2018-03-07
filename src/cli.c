#include <stdio.h>

#include "uberwald.h"

int main (int argc, char ** argv) {
  printf("Überwald Lisp, v0.0.0.\n");

  if (argc > 1) {
    read_dispatch(argv[1], 0);
  }

  printf("Integer is: %d\n", ubw_getinteger(ubw_newinteger(3)));
}
