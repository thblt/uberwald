/**
 * @file
 *
 * @brief Container types.
 *
 * @defgroup util Utility
 * @{
 * @defgroup containers Containers
 * @brief Simple data containers
 * @{
 * @defgroup Stacks
 * @defgroup Vectors
 * @defgroup Queues
 * @}
 * @}
 */

#pragma once

#include <stdbool.h>
#include <stddef.h>

#include "common.h"
#include "object.h"

#include "containers.decl.h"

#define ubw_stack_init(stack, capacity, dptr)                           \
  _Generic((stack),                                                     \
           ubw_lops*: ubw_lops_init,                                    \
           ubw_los*: ubw_los_init,                                      \
           ubw_ps*: ubw_ps_init                                         \
           ) (stack, capacity, dptr);
