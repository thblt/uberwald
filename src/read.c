#include <stdio.h>

#include "containers.h"
#include "object.h"
#include "read.h"
#include "store.h"
#include "eval.h"

#define SPACE ' '
#define TAB '\t'
#define LB '\n'

/** @brief Allocate and initialize a new reader object */
ubw_reader * ubw_reader_new(ubw_store *s, char *buf) {
  ubw_reader *ret = malloc(sizeof(ubw_reader));
  ubw_reader_init(ret, s, buf);
  return ret;
}

/** @brief Initialize a new reader object */
ubw_reader * ubw_reader_init(ubw_reader *r, ubw_store *s, char *buf) {
  r->buf = buf;
  r->store = s;
  r->pos = 0;
  r->line = 1;
  r->col = 0;
  r->root = NULL;
  r->err = OK;

  ubw_store_init(&r->eph_store, UBW_READER_STORE_SIZE, 0);
  ubw_stack_init(&r->stack, UBW_READER_STACK_SIZE, NULL);

  return r;
}

ubw_obj * ubw_read(ubw_reader *r) {

  ubw_obj *o = NULL;

  do {
    switch (r->buf[r->pos]) {
    case '(':
      o = ubw_store_new(r->store);
      ubw_list_init(o, NULL, NULL);
      push_object(r, o);
      ubw_lops_fcpush(&r->stack, o);

      r->col++;
      r->pos++;
      break;

    case ')':
      ubw_lops_pop(&r->stack);
      if (0 == ubw_lops_length(&r->stack)) {
        r->err = DONE;
      }
      r->col++;
      r->pos++;
      continue;

    case '[':
      // @TODO
      r->col++;
      r->pos++;
      break;

    case ']':
      // @TODO
      r->col++;
      r->pos++;
      break;

    case SPACE:
    case TAB:
      r->col++;
      r->pos++;
      break;

    case LB:
      r->line++;
      r->col=0;
      r->pos++;
      break;

    case 0x00:
      r->err = UNEXPECTED_END_OF_INPUT;
      break;

    default:
      o = ubw_store_new(r->store);
      read_unknown(r, o);
      push_object(r, o);
    }
  } while (OK == r->err);

  return r->root;
}

void push_object(ubw_reader *r, ubw_obj *o) {
  // If we don't have a root, that object is the new root.
  if (NULL == r->root) {
    r->root = o;
    if (!ubw_list_p(o)) {
      // This is the first object, and it's not a list: we're done.
      r->err = DONE;
    }
    return;
  }

  // If we're here, we're inside a list.  We then have to push this
  // last object on top (cddddd...dr) of the list.
  ubw_obj *head = ubw_lops_dfpeek(&r->stack);


  // Remember we initialize lists with car = cdr = NULL.
  if (NULL == ubw_list_car(head)) {
    // If we don't have a car, we just set it.
    head->data.list.car = o;
  } else if (NULL == ubw_list_cdr(head)) {
    // If we already have a car, this object must become cdr, hence a
    // new list.  This is just a bit trickier.
    ubw_obj *nhead = ubw_list_new(r->store, ubw_list_p(o) ? NULL : o, NULL);

    ubw_lops_fpop(&r->stack);
    ubw_lops_cpush(&r->stack, nhead);
    head->data.list.cdr = nhead;
  } else {
    printf("ABNORMAL!!!\n");
    exit(EXIT_FAILURE);
  }
}

int next_sep(ubw_reader *r) {
  int ret = r->pos;
  while (r->buf[ret] != SPACE &&
         r->buf[ret] != TAB &&
         r->buf[ret] != LB &&
         r->buf[ret] != 0x00 &&
         r->buf[ret] != ')' &&
         r->buf[ret] != '(' &&
         r->buf[ret] != '[' &&
         r->buf[ret] != ']')
    ret ++;
  return ret;
}

/** Decode a null or whitespace-terminated sequence of characters as
    an integer, a float or a symbol, in that order of priority. */
ubw_obj * read_unknown(ubw_reader *r, ubw_obj *o) {
  int end = next_sep(r);
  bool maybe_int = true,
    maybe_float = true,
    seen_dot = false;
  // This may not be the most efficient approach, but it's easy to write.

  for (int i=r->pos; (maybe_int || maybe_float) && i<end; i++) {
    switch (r->buf[i]) {

    case '-':
    case '+':
      // Minus and plus may appear at the beginning of a number.
      if (i > r->pos) {
        maybe_int = false;
        maybe_float = false;
      }
      break;

    case '.':
      if (seen_dot) {
        maybe_int = false;
        maybe_float = false;
      } else {
        maybe_int = false;
        seen_dot = true;
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
      maybe_int = false;
      maybe_float = false;
    }
  }

  if (maybe_int) ubw_int_init(o, 1);
  else if (maybe_float) ubw_float_init(o, 1.5);
  else ubw_symbol_init(o, 1);

  r->col += (end - r->pos);
  r->pos = end;

  return o;
}
