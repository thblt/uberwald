#include <stdio.h>
#include <stdlib.h>

#include "readline/readline.h"

#include "uberwald.h"

int main (int argc, char ** argv) {
  printf("Überwald Lisp machine, v%d.%d.%d.\n",
         UBW_VERSION_MAJOR,
         UBW_VERSION_MINOR,
         UBW_VERSION_PATCH);

  char * line = 0x00;
  do {
    line = readline("> ");
    ubw_read(line);
  } while (NULL != line);
}
