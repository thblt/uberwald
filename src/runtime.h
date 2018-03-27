#include "env.h"
#include "stack.h"
#include "heap.h"
#include "read.h"
#include "symtbl.h"

/** @brief The Überwald runtime.
 *
 * The runtime contains:
 *  - a reader;
 *  - the heap controller;
 *  - the symbol table controller;
 *  - the environment stack.
 */
typedef struct {
  /** @brief Heap */
  ubw_heap h;
  /** @brief Symbol table */
  ubw_symtbl s;
  /** @brief Environment stack */
  ubw_env env;
} ubw_rt;
