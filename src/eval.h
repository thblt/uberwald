/**
 * @file
 * @ingroup core
 * @brief Lisp evaluation
 *
 * This is the core of the Lisp evaluation mechanism.
 */

#pragma once

#include "config.h"
#include "object.h"

/** @brief Evaluator opcodes.
 *
 * Because Überwald's evaluator is non-recursive (it never calls into
 * itself, nor into any other function), it needs a way to pass
 * instructions to itself at an unspecified depth.  Opcodes are
 * invalid pointers that can be pushed to the stack to control the
 * operations of the evaluator.
 */
typedef enum
  {
   /** @brief The bottom opcode.
    *
    * When the evaluator hits `OC_BOTTOM` at top-level, it terminates
    * immediately
    *
    * When the evaluator is called on a form, the stack should be
    * initialized to the state:
    *
    * OC_EVAL [head]
    * &form
    * OC_BOTTOM.
    *
    * Because of `OC_EVAL`'s behavior, when evaluation is complete,
    * the stack will be on the state:
    *
    * OC_BOTTOM
    * &result
    *
    * Which means the evaluator terminates with the result of top of
    * the stack.
    */
   OC_BOTTOM = 0x00,

   /** @brief Evaluate a form.
    *
    * Evaluate the form pointed to by the pointer at the head of the
    * stack, pop the next value (which is expected to be an opcode),
    * push a pointer to the result of the evaluation, push back the
    * next opcode.  In pseudo-code:
    *
    *     form = pop();
    *     next = pop();
    *     push(eval(form));
    *     push(next);
    */
   OC_EVAL = 0x01,

   /** @brief Evaluate the car of a list up to the actual callable.
    *
    * In Lisp, it is trivial to determine the actual
    * function to invoke by calling another function.  For
    * example:
    *
    *     ((if substract - +) 5 2)
    *
    * This opcode orders the reduction of the car of a list until it
    * is either `(callable?)` or non-evaluable.  In pseudo code, it
    * determines the following behavior:
    *
    *     car = pop()
    *     if (callable?(car)) {
    *         push(car)
    *         push(apply)
    *     } else if (evaluatable?(car)) {
    *         push (OC_CAREVAL)
    *         push (car)
    *         push (OC_EVAL)
    *     } else {
    *         push (OC_ERROR); // Neither callable nor reducible!
    *     }
    */
   OC_CAREVAL = 0x02,

   /** @brief Apply a list to a callable (call a function with arguments)
    *
    * @TODO Document
    */
   OC_APPLY = 0x03,

   /* Recursively evaluate each element of a loop. */
   OC_MAPEVAL = 0x04,
   OC_COLLECT = 0x05
  } ubw_opcode;
