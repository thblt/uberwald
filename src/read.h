#pragma once

#include "object.h"
#include "stack.h"
#include "store.h"

#define UBW_READER_STACK_SIZE 256
#define UBW_READER_STORE_SIZE 1024

/**
  * reader.
  */
typedef struct {
  char * buf;      //!< Input buffer.
  int pos,         //!< Current character position in buffer.
    line,          //!< Current line (for error reporting)
    col;           //!< Current column (for error reporting)
  ubw_obj * root;  //!< The head object
    lostk_t stack; //!< Object stack
  ubw_store *store,//!< The main object and symbols store;
    eph_store;     //!< The ephemeral store.
  /** The last error.  This should be initialized to the null pointer,
      and the read function should check for it. */
  enum {
    OK = false,
    UNEXPECTED_TOKEN,
    UNEXPECTED_END_OF_INPUT
  } err;
} ubw_reader;

/** read Lisp from a C-type string.  This is only a thin wrapper
    around the actual read function. */
ubw_obj ** cstr_read(char ** s);

/** read Lisp from a Lisp string. */
ubw_reader * ubw_reader_new(ubw_store *s, char *buf);
ubw_reader * ubw_reader_init(ubw_reader *r, ubw_store *s, char *buf);
ubw_obj * ubw_read(ubw_reader *s);

#ifdef _UBERWALD_INTERNALS
int next_sep(ubw_reader * st);
bool push_object(ubw_reader *r, ubw_obj *o);
ubw_obj * read_unknown(ubw_reader *r, ubw_obj *obj);
#endif
