/**
 * @file
 * @ingroup core
 * @brief Symbol bindings environment
 *
 * A Lisp environment is made of two components:
 *
 * - a set of pairs associating a program symbol with a location in memory;
 * - a pointer set to either `NULL` or the location of a parent
      environment.
 */

#pragma once

#include "config.h"
#include "object.h"
#include "stbl.h"

typedef struct ubw_env {
  /** @brief This environement's parent, or NULL for the root environment */
  struct ubw_env * parent;
  struct {
    ubw_symbid s;
    ubw_obj *v;
  } *env;
  int sz, c;
} ubw_env;
