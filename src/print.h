/**
 * @file
 * @ingroup core
 * @brief Lisp printer
 *
 * A basic recursive printer for Lisp objects.
 */

#pragma once

#include "config.h"
#include "object.h"
#include "runtime.h"

void print(ubw_rt *rt, ubw_obj *o);

#ifdef UBW_EXPOSE_INTERNALS
void print_(ubw_rt *rt, ubw_obj *o, bool cdr);
#endif
