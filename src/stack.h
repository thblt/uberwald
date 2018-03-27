/** @file
  * @brief Stack of pointers.
  *
  * This is a simple stack of pointers to ubw_obj.
  */

#pragma once

#include <stddef.h>

#include "object.h"

typedef struct {
  /** @brief Beginning of stack */
  ubw_obj **beg,
  /** @brief Stack head (first free location) */
    **head,
  /** @brief End of stack (last usable location) */
    **end;
}
  ubw_stack;

/** @brief Initialize a new stack.
 *
 * @param s The ubw_stack to initialize.
 * @param capacity Length.
 * @param dptr Either null, or a pointer to an allocated memory range >= capacity*sizeof(ubw_obj*).
 */
ubw_stack * ubw_stack_init(ubw_stack *s, const int capacity, ubw_obj **dptr);

/** @brief Return a pointer to the head value without decreasing head index.
 *
 * This function returns either a valid pointer to the stack head or
 * NULL if the stack is empty.  To ignore the emptyness check, use
 * ubw_stack_fpeek instead.
 *
 * @param s The ubw_stack to initialize.
 */
ubw_obj * ubw_stack_peek(const ubw_stack *s);

/** @brief Fast peek: like ubw_stack_peek, but without safety checks.
 *
 * See ubw_stack_peek for documentation.
 */
ubw_obj * ubw_stack_fpeek(const ubw_stack *s);

/** @brief Return a pointer to the object at head of the stack and
    decrase head pointer by one.
 *
 * If the stack is empty, this function will return NULL instead.
 */
ubw_obj * ubw_stack_pop(ubw_stack *s);
/** @brief Fast pop: like ubw_stack_pop without safety checks.
 *
 * See ubw_stack_pop for documentation.
 */
ubw_obj * ubw_stack_fpop(ubw_stack *s);

/** @TODO Document */
ubw_obj * ubw_stack_push(ubw_stack *s, ubw_obj* o);

/** @TODO Document */
ubw_obj * ubw_stack_fpush(ubw_stack *s, ubw_obj* o);

/**
 * @brief Return the length of a ubw_stack.
 *
 *x @param s The ubw_stack.
 */
inline ptrdiff_t ubw_stack_length(const ubw_stack *s) {
  return s->head - s->beg;
}
