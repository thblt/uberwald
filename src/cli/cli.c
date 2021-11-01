/**
 * @defgroup cli CLI
 * @brief Command-line interface and REPL
 * @file
 * @brief Command-line interface */

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "readline/readline.h"

#include "uberwald.h"

#ifdef DEBUG
#define CLI_BUILD_INFO " (debug build)"
#else
#define CLI_BUILD_INFO ""
#endif

#include "string.h"

/** @brief Main function */
int main () {

  printf("Überwald Lisp machine v%sd%s\n",
         UBW_VERSION_STRING,
         CLI_BUILD_INFO
         );



  ubw_rt rt;
  ubw_reader rd;
  ubw_obj *obj;
  char * line;

  while (NULL != (line = readline("ü» "))) {
    ubw_reader *r = ubw_reader_init(&rd);
    ubw_stack_init (&r->stack, 500, NULL);
    obj = ubw_read(&rt, &rd, line);
    switch(r->err) {
    case OK: printf("Abnormal state (reader returned with OK error code).\n"); break;
    case NO_EPH_STORE: printf("Cannot initialize ephemeral store\n");
    case DONE:
      print(obj);
      printf("(All good.)\n"); break;
    case UNEXPECTED_TOKEN: printf("Unexpected token (reader in position %d)!\n", r->pos); break;
    case UNEXPECTED_END_OF_INPUT: printf("Unexpected EOF!\n"); break;
    }
    free(rd.stack.beg);
  }

  return EXIT_SUCCESS;
}
