#include <stdio.h>

#include "read.h"
#include "heap.h"

ubw_reader * ubw_reader_init(ubw_reader *r) {
  // Initialize the reader
  r->pos = 0;
  r->line = 1;
  r->col = 0;
  r->err = OK;

  return r;
}

ubw_reader * ubw_reader_reset(ubw_rt *rt, ubw_reader *r) {
  r->err = (NO_EPH_STORE == r->err) ? r->err : OK;

  // Release one hold on the ephemeral store.
  ubw_es_release(&rt->h);

  return r;
}

ubw_obj * ubw_read(ubw_rt *rt, ubw_reader *r, const char* buf) {
  ubw_token t;
  ubw_obj *ret = NULL, *o, *head, *newhead;

  while (1) {

    o = NULL;
    next_token(r, &t, buf);

    // Initialize -- or not -- an object depending on token type.
    switch(t.type) {
    case TK_BOL:
      o = ubw_new(&rt->h);
      ubw_list_init(o, NULL, NULL);
      break;

    case TK_EOL:
      if (NULL == ret) {
        r->err = UNEXPECTED_TOKEN;
        return ret;
      } else {
        ubw_stack_fpop(&r->stack);
        if (0 == ubw_stack_length(&r->stack)) {
          r->err = DONE;
          return ret;
        }
      }
      break;

    case TK_OTHER:
      o = ubw_new(&rt->h);
      ubw_symbol_init(o, ubw_stbl_intern(&rt->stbl, &buf[t.pos], &buf[t.pos + t.length]));
      break;

    case TK_END:
      r->err = UNEXPECTED_END_OF_INPUT;
      return ret;

    case TK_BOV:
    case TK_EOV:
    case TK_MACROCHAR:
      assert(false);
      break;
    }

    if (NULL == o) continue;

    // If we don't have a return value yet, we assign it.
    if (NULL == ret) {
      ret = o;
    }

    if (0 == ubw_stack_length(&r->stack)) {

      if (ubw_list_p(o)) {
        ubw_stack_fpush(&r->stack, o);
      } else {
        r->err = DONE;
        return ret;
      }
    } else {
      head = ubw_stack_fpeek(&r->stack);
      assert(ubw_list_p(head));

      if (NULL == ubw_list_car(head)) {
        head->list.car = o;
      } else {
        assert(NULL == ubw_list_cdr(head));

        newhead = ubw_new(&rt->h);
        ubw_list_init(newhead, o, NULL);
        head->list.cdr = newhead;
        ubw_stack_fpop(&r->stack);
        ubw_stack_fpush(&r->stack, newhead);
      }
    }
  }
}

void next_token(ubw_reader *r, ubw_token *t, const char *buf) {
  while (true) {
    t->pos = r->pos;
    t->length = 1;
    r->col++;
    switch (buf[r->pos++]) {

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
      t->type = TK_END;
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
      t->length = next_sep(r, buf) - r->pos + 1;
      r->pos += t->length - 1;
      r->col += t->length - 1;
      return;
    }
  }
}

int next_sep(ubw_reader *r, const char *buf) {
  int ret = r->pos;
  while (buf[ret] != ' ' &&
         buf[ret] != '\t' &&
         buf[ret] != '\n' &&
         buf[ret] != 0x00 &&
         buf[ret] != ')' &&
         buf[ret] != '(' &&
         buf[ret] != '[' &&
         buf[ret] != ']')
    ret ++;
  return ret;
}
