/**
 * @file
 * @brief The storage system
 */

#pragma once

#include "object.h"
#include "stack.h"

// * Symbols

/** @brief Associate a symbol name to a globally unique ID */
typedef struct {
  int id;
  ubw_char name[UBW_MAX_SYMBOL_LENGTH];
} ubw_symb;

/** @brief intern a new or existing symbol.

    This will return the unique identifier of that symbol.  Symbols
    are stored as a sorted array, so lookup is in Ο(log n), insertion
    may be a bit more expansive because we may have to move data in
    memory around.

    @param name The symbol name as a null-terminated Überwald string.

*/
int ubw_intern(ubw_char * name);

/** return the name of a symbol.  This requires complete traversal of
    the symbol table, so is in O(n) */
ubw_char * ubw_symbol_name(ubw_obj * s);

// * Heap

// * Store

/** The Überwald in-memory storage system.  This should store a
    reference to the root environment, the first free position on the
    heap, etc.  For now, it's a dummy representation so that the rest
    compiles. */
typedef struct {
  ubw_obj * heap;
  int heap_c,
    heap_sz;
  ubw_symb * symt;
  int symt_c,
    symt_sz;
} ubw_store;

/** @brief Allocate a new store.
  *
  * @param heap_sz The base heap capacity.  If zero, heap isn't
  * allocated at all and pointer will be NULL.
  *
  * @param symt_sz Symbol table base capacity.  If zero, symbol
  * tables aren't allocated at all and pointer will be NULL. */
ubw_store * ubw_store_create(int heap_sz, int symt_sz);

void ubw_store_init(ubw_store *s, int heap_sz, int symt_sz);

/** @brief Allocate a new object on the heap.
 *
  * Allocate a new object on the heap.and return a pointer to this
  * object.  To create a new virtual machine, see
  * ubw_store_create() */
struct ubw_obj * ubw_store_new(ubw_store *s);

/** @brief Allocate continuous space on the heap for n objects objects and
    return a pointer to the first object. */
struct ubw_obj * ubw_store_alloc(ubw_store *s, int n);

/** @brief Copy an object onto the store. */
struct ubw_obj * ubw_copy(ubw_store *s, ubw_obj *o);

/** @brief Move an object onto the store. */
struct ubw_obj * ubw_move(ubw_obj * o);

/** Return the true-ish object */
inline ubw_obj * ubw_store_t(ubw_store *s) {
  return & s->heap[0]; // @FIXME Define and use a constant.
}

/** Return the false-ish object */
inline ubw_obj * ubw_store_nil(ubw_store *s) {
  return & s->heap[1]; // @FIXME Define and use a constant.
}
