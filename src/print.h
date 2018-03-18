#include "common.h"
#include "object.h"

void doprint(ubw_obj *o, int depth, bool cdr);
inline void print(ubw_obj *o) {
  doprint(o, 0, false);
}
