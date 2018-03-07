#include <stdio.h>

#include "read.h"
#include "eval.h"

int read_symbol(char * buf, int pos) {
  printf("Symbol!\n");
  return 0;
}

int read_number(char * buf, int pos) {
  printf("Number!\n");
  return 0;
}
int begin_list(char * buf, int pos) {
  printf("Beginning of a list!\n");
  return 0;
}
int end_list(char * buf, int pos) {
  printf("End of a list!\n");
  return 0;
}

int read_dispatch(char * buf, int pos) {
  if (('a' <= buf[pos] && 'z' >= buf[pos])
      || ('A' <= buf[pos] && 'Z' >= buf[pos])
      || '_' == buf[pos]) {
    return read_symbol (buf, pos);
  }
  else if ('0' <= buf[pos] && '1' >= buf[pos]) {
    return read_number (buf, pos);
  } else if ('(' == buf[pos]) {
    return begin_list(buf, pos);
  }
  else if (')' == buf[pos]) {
   return end_list(buf, pos);
  }
  ubw_raise("Unknown symbol!");
  return pos+1;



}
