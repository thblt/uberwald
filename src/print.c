#include <stdio.h>

#include "print.h"

#define TABSTOP 4

void print(ubw_obj *o) {
  print_(o, false);
  printf("\n");
}

void print_(ubw_obj *o, bool cdr) {

  if (NULL == o) {
    return;
  }

  switch (o->type) {

  case LIST:
    if (NULL == ubw_list_car(o) && NULL == ubw_list_cdr(o))
      printf(cdr ? "" : "nil ");
    else {
      if (!cdr) printf("( ");
      print_(ubw_list_car(o), false);
      print_(ubw_list_cdr(o), true);
      if (!cdr) printf(") ");
    }

    break;

  case INTEGER:
    printf("%li ", ubw_int_unbox(o));
    break;

  case SYMBOL:
    printf("symbol ");
    break;

  case KEYWORD:
    printf(":keyword ");
    break;

  case VECTOR:
    printf("VECTOR-NOREPR ");
    break;

  case FLOAT:
    printf("FLOAT-NOREPR ");
    break;

  case STRING:
    printf("STRING-NOREPR ");
    break;
  case CFUNC:
    printf("CFUNC-NOREPR ");
    break;
  case _DELETED:
    printf("DELETED=NOREPR ");
    break;
   default:
     printf("[?????? %d] ", o->type);
  }}
