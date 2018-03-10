#include <stdio.h>

#include "common.h"
#include "object.h"
#include "read.h"
#include "eval.h"
#include "uberwald.h"

#define SPACE ' '
#define TAB '\t'
#define LB '\n'

void ubw_read(char * str) {
  ubw_rdst_t st = {
    .buf = str,
    .stack = * lostk_new(256),
    .line = 1,
    .col = 0,
    .pos = 0,
    .err = NULL
  };

  // Read character
  while (st.buf[st.pos] != 0x00) {
    printf("[%d:%d], character is %c, and we read: ",
           st.line,
           st.col,
           st.buf[st.pos]);

    switch (st.buf[st.pos]) {
    case '(':
      begin_list(&st);
      break;
    case ')':
      end_list(&st);
      break;
    case '[':
      begin_vector(&st);
      break;
    case ']':
      end_vector(&st);
      break;
    case SPACE:
    case TAB:
      printf("Whitespace!\n");
      st.col++;
      st.pos++;
      break;
    case LB:
      printf("Linebreak!\n");
      st.line++;
      st.col=0;
      st.pos++;
      break;
    default:
      read_unknown(&st);
    }
    if ((0 == lostk_length(& st.stack))  // The stack is empty
        ||                               // or
        ((1 == lostk_length(& st.stack)  // it contains a single object
          &&                              // which is
          !(ubw_list_p(lostk_peek(&st.stack))   // neither a list
            || ubw_vector_p(lostk_peek(&st.stack)))))) // nor a vector
      {
          break;
        }
      // The head of the

  }
}

/** Return the position of the next separator (whitespace or NULL) */
int next_sep(ubw_rdst_t * st) {
  int ret = st->pos;
  while (st->buf[ret] != SPACE &&
         st->buf[ret] != TAB &&
         st->buf[ret] != LB &&
         st->buf[ret] != 0x00 &&
         st->buf[ret] != ')' &&
         st->buf[ret] != '(' &&
         st->buf[ret] != '[' &&
         st->buf[ret] != ']')
    ret ++;
  return ret;
}

/** push the latest read object in its expected position.  Such  */
void push_object(ubw_rdst_t * st, ubw_obj * o) {
  if (lostk_length(& st->stack)) {
    // If there's already something on the stack
  }
}


/** Decode a null or whitespace-terminated sequence of characters as
    an integer, a float or a symbol, in that order of priority. */
void read_unknown(ubw_rdst_t * st) {
  int end = next_sep(st),
    maybe_int = 1,
    maybe_float = 1,
    seen_dot = 0;
  // This may not be the most efficient approach, but it's easy to write.

  for (int i=st->pos; (maybe_int || maybe_float) && i<end; i++) {
    switch (st->buf[i]) {

    case '-':
    case '+':
      // Minus and plus may appear at the beginning of a number.
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
  if (maybe_int) printf ("Integer");
  else if (maybe_float) printf ("Float");
  else printf ("Identifier");

  st->col += (end - st->pos);
  st->pos = end;
}

void begin_list(ubw_rdst_t * st) {
  printf("Beginning of a list!\n");
  st->col++;
  st->pos++;
}

void end_list(ubw_rdst_t * st) {
  printf("End of a list!\n");
  st->col++;
  st->pos++;
}

void begin_vector(ubw_rdst_t * st) {
  printf("Beginning of a vector!\n");
  st->col++;
  st->pos++;
}

void end_vector(ubw_rdst_t * st) {
  printf("End of a vector!\n");
  st->col++;
  st->pos++;
}
