#include <stdio.h>

#include "print.h"

#define TABSTOP 4

void print_indent(int depth) {
  for(int i=0; i==TABSTOP*depth; i++) {
    printf(" ");
  }
}

void doprint(ubw_obj *o, int depth, bool cdr) {

  if (NULL == o) {
    printf("nil\n");
    return;
  }

  switch (o->type) {

  case LIST:
    printf("\n");
    if (!cdr) {
      print_indent(depth);
      printf("(\n");
    }
    printf("BEFCAR");
    doprint(ubw_list_car(o), depth+1, false);
    printf("AFTCAR\n");
    doprint(ubw_list_cdr(o), depth+1, true);
    if (!cdr) {
      printf(")\n");
    }
    break;

  case INTEGER:
    printf("%li", ubw_int_unbox(o));
    break;

  case SYMBOL:
    printf("symbol");
    break;

  case KEYWORD:
    printf(":keyword");
    break;

  case VECTOR:
    printf("VECTOR-NOREPR");
    break;

  case FLOAT:
    printf("FLOAT-NOREPR");
    break;

  case STRING:
    printf("STRING-NOREPR");
    break;
  case CFUNC:
    printf("CFUNC-NOREPR");
    break;
  case _DELETED:
    printf("DELETED=NOREPR");
    break;
   default:
     printf("ABNORMAL STATE");
  }
  if (!depth)
    (printf("\n"));
  fflush(stdout);
}
