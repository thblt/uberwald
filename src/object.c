#include "object.h"

#define IMPL_TYPE_BASE(name, ctype, identifier) \
  ubw_bool ubw_ ## name ## _p (ubw_obj * o) {   \
    if (identifier == o->type) {                \
      return true;                              \
    } else {                                    \
      return false;                             \
    }                                           \
  }                                             \
                                                \
  ctype * ubw_ ## name ## _unbox(ubw_obj * o) { \
    return & o->data.name;                        \
  }                                             \

ubw_bool ubw_obj2bool(ubw_obj * o) {
  return !(LIST == o->type
           && NULL == o->data.list.car
           && NULL == o->data.list.cdr);;
}

// * Lists
IMPL_TYPE_BASE(list, ubw_list, LIST)

IMPL_TYPE_BASE(vector, ubw_vector, VECTOR)
IMPL_TYPE_BASE(integer, ubw_int, INTEGER)
IMPL_TYPE_BASE(fpn, ubw_float, FLOAT)
IMPL_TYPE_BASE(string, ubw_string, STRING)
IMPL_TYPE_BASE(cfunc, ubw_cfunc, CFUNC)
