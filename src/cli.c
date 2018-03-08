#include <stdio.h>
#include <stdlib.h>

#include "readline/readline.h"

#include "uberwald.h"

int main (int argc, char ** argv) {
  printf("Überwald Lisp, v0.0.0.\n");

  if (argc > 1) {
    read_dispatch(argv[1], 0);
  }

  char * line = 0x00;
  do {
    line = readline("> ");
    ubw_read(line);
  } while (NULL != line);
}
