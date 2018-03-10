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

    This will return the unique
    identifier of that symbol.  Symbols are stored as a sorted array,
    so lookup is in Ο(log n), insertion may be a bit more expansive
    because we may have to move data in memory around. */
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
  ubw_symbol * symbols;
  int symb_count,
    symb_capac;
  ubw_obj * heap;
} ubw_store;

/** @brief Allocate a new store */
ubw_store * ubw_store_create();

/** Allocate a new object on the heap and return a pointer to this
    object.  To create a new virtual machine, see ubw_store_create() */
struct ubw_obj * ubw_store_new(ubw_store *s);

/** Allocate continuous space on the heap for n objects objects and
    return a pointer to the first object. */
struct ubw_obj * ubw_store_alloc(ubw_store *s, int n);

/** Return the true-ish object */
inline ubw_obj * ubw_store_t(ubw_store *s) {
  return & s->heap[0]; // @FIXME Define and use a constant.
}

/** Return the false-ish object */
inline ubw_obj * ubw_store_nil(ubw_store *s) {
  return & s->heap[1]; // @FIXME Define and use a constant.
}
