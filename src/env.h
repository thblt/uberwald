/**
 * @file
 * @ingroup core
 * @brief Environment
 *
 *
 */

#pragma once

#include "config.h"
#include "object.h"

typedef struct {
  void * symbol;
  ubw_obj * value;
} ubw_binding;

typedef struct ubw_env ubw_env;

struct ubw_env {
  ubw_env * parent;
  int refcount,
    size,
    capacity;
  ubw_binding ** bindings;
};
