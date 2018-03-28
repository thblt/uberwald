/**
 * @file
 * @ingroup core
 * @brief Reader
 *
 * The elementary Lisp reader.
 */

#pragma once

#include "heap.h"
#include "object.h"
#include "runtime.h"
#include "stack.h"

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
  int
  //! @brief Current character position in buffer.
  pos,
  //! @brief Current column (for error reporting)
    line,
  //! @brief Current column (for error reporting)
    col;

  //! @brief Object stack
  ubw_stack stack;
  /** @brief The last error.
   * This should be initialized to the null pointer,
   * and the read function should check for it.
   */
  enum {
    OK = false,
    NO_EPH_STORE,
    DONE,
    UNEXPECTED_TOKEN,
    UNEXPECTED_END_OF_INPUT
  } err;
} ubw_reader;

/** @brief Initialize a new reader object */
ubw_reader * ubw_reader_init(ubw_rt *rt, ubw_reader *r);

/** @brief read a Lisp form from a string. @TODO Document */
void ubw_read(ubw_rt *rt, ubw_reader *rd, const char *buf);

/** @brief Lisp wrapper around ubw_read, which see. */
ubw_obj * ubw_lread(ubw_rt *rt, ubw_obj* buf);

#ifdef UBW_EXPOSE_INTERNALS
void ubw_read_(ubw_rt *rt, ubw_reader *rd, const char *buf);

/** @brief Read next token from r */
void next_token(ubw_reader *r, ubw_token *t, const char* buf);

/** @brief Return the position of the next separator (whitespace or NULL)
*/
int next_sep(ubw_reader * r, const char *buf);
#endif
