/**
 * @file
 * @ingroup core
 * @brief Runtime state.  See description in ubw_rt.
 */

#pragma once

#include "env.h"
#include "stack.h"
#include "heap.h"
#include "stbl.h"

/** @brief The Überwald runtime.
 *
 * The runtime contains:
 *  - a reader;
 *  - the heap controller;
 *  - the symbol table controller;
 *  - the environment stack.
 */
typedef struct ubw_rt {
  /** @brief Heap */
  ubw_heap h;
  /** @brief Symbol table */
  ubw_stbl stbl;
  /** @brief Environment stack */
  ubw_env env;
} ubw_rt;
