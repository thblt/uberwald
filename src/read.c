#include <stdio.h>

#include "common.h"
#include "object.h"
#include "read.h"
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
  r->err = OK;

  ubw_store_init(&r->eph_store, UBW_READER_STORE_SIZE, 0);
  lostk_init(&r->stack, UBW_READER_STACK_SIZE);

  return r;
}

ubw_obj * ubw_read(ubw_reader *r) {
  ubw_obj *o;
  bool repeat;

  do {
    repeat = true;
    o = NULL;

    while (repeat) {
      repeat = false;
      switch (r->buf[r->pos]) {
      case '(':
        printf("Beginning of a list!\n");
        r->col++;
        r->pos++;
        o = ubw_list_new(r->store, NULL, NULL);
        break;

      case ')':
        printf("End of a list!\n");
        r->col++;
        r->pos++;
        break;

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
        repeat = true;
        break;

      case LB:
        r->line++;
        r->col=0;
        r->pos++;
        repeat = true;
        break;

      case 0x00: // @FIXME Better determine end of input..
        // @FIXME Cleanly return.
        printf("Attempting to read beyond input data!!!!!i\n");
        exit(EXIT_FAILURE);

      default:
        o = read_unknown(r, ubw_store_new(r->store));
      }
    }
  } while (push_object(r, o)
           && OK == r->err);

  return r->root;
}

/** @brief Handle a recently read object */
bool push_object(ubw_reader *r, ubw_obj *o) {
  // If we don't have an object, it means input terminated early.
  if (NULL == o) {
    r->err = UNEXPECTED_END_OF_INPUT;
    return false;
  }
  // (If we're here, we've read something.  Hurrah.)

  // If we don't have a root object yet, then it's our first read.
  // The object we've just read is then, obviously, root.
  if (NULL == r->root) {
    r->root = o;
  }

  // If we don't have anything on stack, then there's no need to
  // continue, it means we've read a non-container object (symbol,
  // string, keyword, whatever), that is neither a list nor a vector.
  // Reading terminates here.
  if (0 == lostk_length(&r->stack)) {
    return false;
  }

  // We need to push the new object to the object on top of stack.

  ubw_obj *head = lostk_peek(&r->stack);

  // Is it a list?
  if (ubw_list_p(head)) {

    // Does it have a car?
    if (NULL == head->data.list.car) {
      // Newly created lists have neither car nor cdr.
      head->data.list.car = o;
    } else if (NULL == head->data.list.cdr) {
      ubw_list_new(&r->eph_store, o, NULL);
    }
  }
  return o;
}

/** Return the position of the next separator (whitespace or NULL) */
int next_sep(ubw_reader * r) {
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
ubw_obj * read_unknown(ubw_reader * r, ubw_obj *o) {
  int end = next_sep(r);
  bool maybe_int = 1,
    maybe_float = 1,
    seen_dot = 0;
  // This may not be the most efficient approach, but it's easy to write.

  for (int i=r->pos; (maybe_int || maybe_float) && i<end; i++) {
    switch (r->buf[i]) {

    case '-':
    case '+':
      // Minus and plus may appear at the beginning of a number.
      if (i > r->pos) {
        maybe_int = maybe_float = false;
      }
      break;

    case '.':
      if (seen_dot) {
        maybe_int = maybe_float = false;
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
      maybe_int = maybe_float = false;
    }
  }
  if (maybe_int) ubw_int_init(o, 1);
  else if (maybe_float) ubw_float_init(o, 1.5);
  else ubw_symbol_init(o, 1);

  r->col += (end - r->pos);
  r->pos = end;

  return o;
}
