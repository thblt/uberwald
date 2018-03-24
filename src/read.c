#include <stdio.h>

#include "object.h"
#include "read.h"
#include "store.h"

/** @brief Allocate and initialize a new reader object */
ubw_reader * ubw_reader_new(ubw_store *s, char *buf) {
  ubw_reader *ret = malloc(sizeof(ubw_reader));
  ubw_reader_init(ret, s, buf);
  return ret;
}

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

void ubw_reader_reset(ubw_reader *r, char *buf) {
  r->buf = buf;
  // @TODO Empty stores
  r->pos = 0;
  r->line = 1;
  r->col = 0;
  r->root = NULL;
  r->err = OK;
}

void ubw_read(ubw_reader *r) {
  ubw_token t;
  ubw_obj *o, *head, *newhead;

  while (true) {

    printf("Reading at position %d\n", r->pos);

    o = NULL;
    next_token(r, &t);
    switch(t.type) {
    case TK_BOL:
      o = ubw_store_new(r->store);
      ubw_list_init(o, NULL, NULL);
      break;

    case TK_EOL:
      if (NULL == r->root) {
        r->err = UNEXPECTED_TOKEN;
        return;
      } else {
        ubw_stack_fpop(&r->stack);
        if (0 == ubw_stack_length(&r->stack)) {
          r->err = DONE;
          return;
        }
      }
      break;

    case TK_OTHER:
      o = ubw_store_new(r->store);
      ubw_int_init(o, 153);
      break;

    case TK_END:
      r->err = UNEXPECTED_END_OF_INPUT;
      return;

    case TK_BOV:
    case TK_EOV:
    case TK_MACROCHAR:
      assert(false);
      break;
    }

    if (NULL == o) continue;

    if (0 == ubw_stack_length(&r->stack)) {
      r->root = o;

      if (ubw_list_p(o)) {
        ubw_stack_fpush(&r->stack, o);
      } else {
        r->err = DONE;
        return;
      }
    } else {
      assert(ubw_stack_length(&r->stack));

      head = ubw_stack_fpeek(&r->stack);

      if (NULL == ubw_list_car(head)) {
        head->data.list.car = o;
      } else {
        // cdr MUST be null
        assert(NULL == ubw_list_cdr(head));
        newhead = ubw_store_new(r->store);
        ubw_list_init(newhead, o, NULL);
        head->data.list.cdr = newhead;
        ubw_stack_fpop(&r->stack);
        ubw_stack_fpush(&r->stack, newhead);
      }
    }
  }
}

void next_token(ubw_reader *r, ubw_token *t) {
  while (true) {
    t->pos = r->pos;
    t->length = 1;
    r->col++;
    switch (r->buf[r->pos++]) {

    case '(':
      t->type = TK_BOL;
      return;

    case ')':
      t->type = TK_EOL;
      return;

    case '[':
      t->type = TK_BOV;
      return;

    case ']':
      t->type = TK_EOV;
      return;

    case 0x00:
      t->type = EOF;
      return;

    case ' ':
    case '\t':
      break;

    case '\n':
      r->line++;
      r->col=0;
      break;

    default:
      t->type = TK_OTHER;
      t->length = next_sep(r) - r->pos + 1;
      r->pos += t->length - 1;
      r->col += t->length - 1;
      return;
    }
  }
}

int next_sep(ubw_reader *r) {
  int ret = r->pos;
  while (r->buf[ret] != ' ' &&
         r->buf[ret] != '\t' &&
         r->buf[ret] != '\n' &&
         r->buf[ret] != 0x00 &&
         r->buf[ret] != ')' &&
         r->buf[ret] != '(' &&
         r->buf[ret] != '[' &&
         r->buf[ret] != ']')
    ret ++;
  return ret;
}
