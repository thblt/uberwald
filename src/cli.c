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
         UBW_VERSION_PATCH,
         sizeof(ubw_obj)
         );

  char * line = 0x00;
  while (NULL != (line = readline("> "))) {
    ubw_read(line);
  }

  return EXIT_SUCCESS;
}
