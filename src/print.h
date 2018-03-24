#include "common.h"
#include "object.h"

void print(ubw_obj *o);

#ifdef UBW_EXPOSE_INTERNALS
void doprint(ubw_obj *o, int depth, bool cdr);
#endif
