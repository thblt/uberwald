/**
 * @defgroup reader
 * @brief The Überwald standard reader
 * @{
 */

#pragma once

#include "object.h"
#include "stack.h"
#include "store.h"

/** @brief The size of the reader stack.
 *
 * This is equivalent to the deeper allowed nesting.
*/
#define UBW_READER_STACK_SIZE 256
/**
 * @brief Slot count in the ephemeral store.
 */
#define UBW_READER_STORE_SIZE 1024

/** @brief @TODO  */
typedef struct {
  enum {
    TK_BOL,
    TK_EOL,
    TK_BOV,
    TK_EOV,
    TK_OTHER,
    TK_MACROCHAR,
    TK_END
  } type;
  int pos, length;
} ubw_token;

/**
  * @brief The Überwald reader object
  */
typedef struct {
  //! @brief Input buffer.
  // @FIXME This probably shouldn't be here.
  char * buf;

  int
  //! @brief Current character position in buffer.
  pos,
  //! @brief Current column (for error reporting)
    line,
  //! @brief Current column (for error reporting)
    col;

  //< @brief The head object
  ubw_obj * root;
  //! @brief Object stack
  ubw_stack stack;
  //! @brief The main object and symbols store;
  ubw_store *store,
  //! @brief The ephemeral store.
    eph_store;
  /** @brief The last error.
   * This should be initialized to the null pointer,
   * and the read function should check for it.
   */
  enum {
    OK = false,
    DONE,
    UNEXPECTED_TOKEN,
    UNEXPECTED_END_OF_INPUT
  } err;
} ubw_reader;

ubw_reader * ubw_reader_new(ubw_store *s, char *buf);

/** @brief Initialize a new reader object */
ubw_reader * ubw_reader_init(ubw_reader *r, ubw_store *s, char *buf);
void ubw_reader_reset(ubw_reader *r, char *buf);

/** @brief read Lisp from a Lisp string. @TODO Document */
void ubw_read(ubw_reader *s);

#ifdef UBW_EXPOSE_INTERNALS

/** @brief Read next token from r */
void next_token(ubw_reader *r, ubw_token *t);
void identify(ubw_reader *r, ubw_token *t);

/** @brief Return the position of the next separator (whitespace or NULL)
*/
int next_sep(ubw_reader * r);
#endif
