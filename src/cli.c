/** @file
 * @brief Command-line interface */

#include <stdio.h>
#include <stdlib.h>

#include "readline/readline.h"

#include "uberwald.h"

/** @brief Main function */
int main () {
  printf("Überwald Lisp machine v%d.%d.%d.\n",
         UBW_VERSION_MAJOR,
         UBW_VERSION_MINOR,
         UBW_VERSION_PATCH);

  char * line = 0x00;
  while (NULL != (line = readline("> "))) {
    ubw_reader * r = ubw_reader_new(NULL, line);
    ubw_read(r);
    free(r);
  }

  return EXIT_SUCCESS;
}
