/**
 * @file
 * @ingroup core
 * @brief Symbol lookup table
  *
  * The symbol table is an associative data structure mapping strings
  * to some numeric identifiers.
  */

#pragma once

#include "config.h"
#include "object.h"

#if 32==UBW_SYMTBL_SYMBID_SIZE
#define UBW_FNV1_OFFSET_BASIS 2166136261
#define UBW_FNV1_PRIME 16777619
#elif 64==UBW_SYMTBL_SYMBID_SIZE
#define UBW_FNV1_OFFSET_BASIS 14695981039346656037
#define UBW_FNV1_PRIME 1099511628211
#elif 128==UBW_SYMTBL_SYMBID_SIZE
#define UBW_FNV1_OFFSET_BASIS 14695981039346656037
#define UBW_FNV1_PRIME 309485009821345068724781371
#elif 256==UBW_SYMTBL_SYMBID_SIZE
#define UBW_FNV1_OFFSET_BASIS 14695981039346656037
#define UBW_FNV1_PRIME 374144419156711147060143317175368453031918731002211
#elif 512==UBW_SYMTBL_SYMBID_SIZE
#define UBW_FNV1_OFFSET_BASIS 14695981039346656037
#define UBW_FNV1_PRIME 35835915874844867368919076489095108449946327955754392558399825615420669938882575126094039892345713852759
#elif 1024==UBW_SYMTBL_SYMBID_SIZE
#define UBW_FNV1_OFFSET_BASIS 14695981039346656037
#define UBW_FNV1_PRIME 5016456510113118655434598811035278955030765345404790744303017523831112055108147451509157692220295382716162651878526895249385292291816524375083746691371804094271873160484737966720260389217684476157468082573
#else
#error Unknown hash size for FNV-1.
#endif

/** @brief Associate a symbol name to a globally unique ID */
typedef struct {
  ubw_symbid id;
  ubw_char name[UBW_LISP_MAX_SYMBOL_LENGTH];
} ubw_symb;

typedef struct {
  ubw_symbid *tbl;
  int sz, c;
} ubw_symtbl;

ubw_symtbl * ubw_symtbl_init(ubw_symtbl *t, int sz, ubw_symb *tbl);

/** @brief intern a new or existing symbol.

    This will return the unique identifier of that symbol.  Symbols
    are stored as a sorted array, so lookup is in Ο(log n), insertion
    may be a bit more expensive because we may have to move data in
    memory around.

    @param name The symbol name.
*/
ubw_symbid ubw_symtbl_intern(ubw_symtbl *t, ubw_string *name);

/** @brief look up an existing symbol.
  *
  * like ubw_symtbl_intern, but doesn't allocate a new symbol.
  *
  *
  * @param name The symbol name.
  */
struct { bool exists; ubw_symbid id; } ubw_symtbl_lookup(ubw_symtbl *t, ubw_string *name);

/** @brief Find the name of a symbol.
 *
 * The complexity of this function depends on build options.  If fast
 * reverse lookup is enabled, it's in O(log n), else in O(n).
 */
ubw_string * ubw_symbol_reverse(ubw_symtbl *t, ubw_symbid s);

#ifdef UBW_EXPOSE_INTERNALS
ubw_symbid ubw_fnv1(ubw_char *str);
#endif
