/** @file
 * @brief Command-line interface */

#include <stdio.h>
#include <stdlib.h>

#include "readline/readline.h"

#include "uberwald.h"

#ifdef DEBUG
#define CLI_BUILD_INFO " (debug build)"
#else
#define CLI_BUILD_INFO ""
#endif

/** @brief Main function */
int main () {
  printf("Überwald Lisp machine v%d.%d.%d%s\n",
         UBW_VERSION_MAJOR,
         UBW_VERSION_MINOR,
         UBW_VERSION_PATCH,
         CLI_BUILD_INFO
         );

  printf("(Überwald uses the following data lengths:\n");
  printf("(char = %d ; int = %d, float = %d:\n",
         sizeof(ubw_char),
         sizeof(ubw_int),
         sizeof(ubw_float));

  char * line = 0x00;
  while (NULL != (line = readline("> "))) {
    ubw_reader * r = ubw_reader_new(NULL, line);
    print(ubw_read(r));
    switch(r->err) {
    case OK: printf("Weird state.\n"); break;
    case DONE: printf("All good.\n"); break;
    case UNEXPECTED_TOKEN: printf("Unexpected token!\n"); break;
    case UNEXPECTED_END_OF_INPUT: printf("Unexpected EOF!\n"); break;
    }
        free(r);
  }

  return EXIT_SUCCESS;
}
