#include <stdio.h>

#include "read.h"
#include "eval.h"

#define SPACE ' '
#define TAB '\t'
#define LB '\n'

void ubw_read(char * str) {
  ubw_rdst_t st = {
    .buf = str,
    .stack = * lostk_new(1024),
    .line = 0,
    .col = 0,
    .pos = 0,
    .err = NULL
  };
  read_dispatch(&st);
}

/** Return the position of the next separator (whitespace or NULL) */
int next_sep(ubw_rdst_t * st) {
  int ret = st->pos;
  while (st->buf[ret] != SPACE &&
         st->buf[ret] != TAB &&
         st->buf[ret] != LB &&
         st->buf[ret] != 0x00) {
    ret ++;
  }
  return ret;
}

/** Decode a null or whitespace-terminated sequence of characters as
    an integer, a float or a symbol, in that order of priority..*/
int read_unknown(ubw_rdst_t * st) {
  int end = next_sep(st),
    maybe_int = 1,
    maybe_float = 1,
    seen_dot = 0;
  // This is not the most efficient approach, but it's easy to write.

  printf("%d -- %d\n", st->pos, end);

  for (int i=st->pos; (maybe_int || maybe_float) && i<end; i++) {
    switch (st->buf[i]) {
    case '-':
      // Minus sign is legal as the first character.
      if (i > st->pos) {
        maybe_int = 0;
        maybe_float = 0;
      }
      break;

    case '.':
      if (seen_dot) {
        maybe_float = 0;
        maybe_int = 0;
      } else {
        maybe_int = 0;
        seen_dot = 1;
      }
      break;

    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
      break;
    default:
      maybe_float = 0;
      maybe_int = 0;
      }
  }
  if (maybe_int) printf ("Integer\n");
  else if (maybe_float) printf ("Float\n");
  else printf ("Identifier\n");

  st->pos = end;
}

int begin_list(ubw_rdst_t * st) {
  printf("Beginning of a list!\n");
  st->col++;
  st->pos++;
  return 0;
}

int end_list(ubw_rdst_t * st) {
  printf("End of a list!\n");
  st->col++;
  st->pos++;
  return 0;
}

int begin_vector(ubw_rdst_t * st) {
  printf("Beginning of a vector!\n");
    st->col++;
  st->pos++;
  return 0;
}

int end_vector(ubw_rdst_t * st) {
  printf("End of a vector!\n");
  st->col++;
  st->pos++;
  return 0;
}

void read_dispatch(ubw_rdst_t * st) {
  switch (st->buf[st->pos]) {
  case '(':
    begin_list(st);
    break;
  case ')':
    end_list(st);
    break;
  case '[':
    begin_vector(st);
    break;
  case ']':
    end_vector(st);
    break;
  case SPACE:
  case TAB:
    st->col++;
    st->pos++;
    break;
  case LB:
    st->line++;
    st->col=0;
    st->pos++;
    break;
  default:
    read_unknown(st);
  }
}
