/**
 * @file
 * @ingroup core
 * @brief Lisp printer
 *
 * A basic recursive printer for Lisp objects.
 */


#include "common.h"
#include "object.h"

void print(ubw_obj *o);

#ifdef UBW_EXPOSE_INTERNALS
void print_(ubw_obj *o, bool cdr);
#endif
