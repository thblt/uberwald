/**
 * @file
 * @ingroup core
 * @brief Symbol lookup table
 */

#pragma once

#include <string.h>

#include "config.h"
#include "object.h"

/** @brief Associate a symbol name to a globally unique ID */
typedef struct {
  /** @brief The unique identifier for this symbol */
  ubw_symbid id;
  /** @brief The hash of this symbol's name, which *should* be unique
      but isn't obviously guaranteed to be. */
  ubw_symbhash hash;
  char name[UBW_LISP_MAX_SYMBOL_LENGTH];
} ubw_symb;

typedef struct {
  ubw_symb
  /** @brief Forward lookup table, sorted by hash. */
  *flt;
  int sz, c;
} ubw_stbl;

ubw_stbl * ubw_stbl_init(ubw_stbl *t, int capac, ubw_symb *flt, ubw_symb *rlt);

/**
 * @brief Intern a new or existing symbol.
 *
 * This will return the unique identifier of that symbol.  Symbols are
 * stored as a sorted array, so lookup is in Ο(log n), insertion may
 * be a bit more expensive because we may have to move data in memory
 * around.
 *
 * @param beg The first character of the symbol to intern;
 * @param end The character-after-last;
 */
ubw_symbid ubw_stbl_intern(ubw_stbl *t, const char *beg, const char *end);

/** @brief Find the name of a symbol.
 *
 * The complexity of this function depends on build options.  If fast
 * reverse lookup is enabled, it's in O(log n), else in O(n).
 */
char * ubw_stbl_reverse(const ubw_stbl *t, const ubw_symbid id);

uint64_t ubw_fnv1_64(const char *beg, const char *end);

#ifdef UBW_EXPOSE_INTERNALS

/**
 * @brief Look up the ubw_stbl.htbl for a record with a given hash,
 * using a binary search.
 *
 * \return Either a pointer to an object with hash `h` or to the
 * object after which this object would be.
 *
 */
ubw_symb * ubw_symb_hlk(ubw_stbl *t, ubw_symbhash h);

inline bool ubw_symb_comp(ubw_symb *a, ubw_symb *b) {
  if (a->hash != b->hash) return false;

  return (0 == strcmp(a->name, b->name));
}

#endif
