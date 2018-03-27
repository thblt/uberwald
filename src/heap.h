/**
 * @file
 * @brief Heap management.
 *
 * The heap is a contiguous memory area whose size is expressed in
 * LISP objects.  In systems with a libc, heap management is partially
 * delegated to the standard malloc() and free() functions, else it is
 * entirely manual.
 */

#pragma once

#include "common.h"
#include "object.h"

/** The Überwald in-memory storage system.  This should store a
    reference to the root environment, the first free position on the
    heap, etc.  For now, it's a dummy representation so that the rest
    compiles. */
typedef struct {
  ubw_obj
  /** @brief First slot */
  *h,
  /** @brief Last slot */
    *hend;

  /** @brief Free map */
  struct {
    ubw_obj *s, *e;
  } f[UBW_HEAP_MAX_FRAGMENTATION];

  ubw_obj
  /** @brief First slot of ephemeral store, if existing, or NULL.  T
   *
   * The ephemeral store ranges from `h` to the end of the heap,
   * `hend`.  It contains at least one slot.
   *
   * Formally, if NULL != es, it is guaranteed that: es <= esh && esh
   * <= hend && es != hend.
   */
    *es,
  /** @brief Head of ephemeral store.  Meaningless if NULL == es. */
    *esh;
  /** @brief Counter for users of the ephemeral store. */
  int esc;
} ubw_heap;

/** @brief Initialize a new heap. */
ubw_heap * ubw_heap_init(ubw_heap *h, int sz, ubw_obj *dptr);

/** @brief Clear the heap.
 *
 * Deallocate everything on the heap.
*/
bool ubw_heap_clear(ubw_heap *h);

/** @brief Allocate a new object on the heap.
 *
  * Allocate a new object on the heap and return a pointer to this
  * object. */
struct ubw_obj * ubw_heap_new(ubw_heap *h);

/** @brief Allocate contiguous space on the heap for n objects and
    return a pointer to the first object. */
struct ubw_obj * ubw_heap_alloc(ubw_heap *h, int size);

/** @brief Resize already allocated block.
 *
 * Return a pointer to the new location of the block, which is not
 * guaranteed to be neither identical or different to the previous
 * pointer. */
ubw_obj * ubw_heap_realloc(ubw_heap *h, ubw_obj *b, int size, int prevsize);

/** @brief Free slot at o.
 *
 * \warning This is a shallow free which may lead to memory leaks
 * (depending on the GC used). In most cases, ubw_heap_delete should
 * be used instead.
 **/
ubw_obj * ubw_heap_free(ubw_heap *h, ubw_obj *o, int size);

/** @brief Delete object at o and free the memory it uses.
 *
 * This is a "deep free" which shouldn't lead to memory leaks,
 * provided it's used to free objects as pointed to by an environment
 * binding.
 **/
ubw_obj * ubw_heap_delete(ubw_heap *h, ubw_obj *o);

/** @brief Copy an object.
  *
  * Perform a deep (recursive) copy of the object at f into t.
  *
  * @param h the heap controller from which memory will be required.
  * @param f the object to copy.
  * @param t pointer to the expected destination, or NULL to allocate a new slot.
  *
 **/
ubw_obj * ubw_copy(ubw_heap *h, ubw_obj *f, ubw_obj *t);

/** @brief Move an object.
  *
  * This is equivalent to calling ubw_copy then ubw_heap_delete.
  **/
ubw_obj * ubw_move(ubw_heap *h, ubw_obj *f, ubw_obj *t);

/** @brief Allocate the ephemeral store.
 *
 * @param h The heap controller.
 * @param size The number of slots to allocate.
 *
 * Since the position of the ephemeral store is fixed (at the end of
 * the heap), allocating the store may require defragmenting the heap
 * first.  In this case, defragmentation is always performed in full.
 *
 * \return a pointer to the newly allocated store or NULL.  NULL has
 * two meanings, depending on the value of h->es:
 *
 * \return - if NULL == h->es; there isn't enough memory on the heap
 *    to allocate `size` slots.
 *
 * \return - otherwise, the ephemeral store was already allocated and
 * no further allocation has taken place.
 *
 * \warning
 */
ubw_obj * ubw_es_alloc(ubw_heap *h, int size);

/** @brief Like ubw_es_alloc, but returns a pointer even if the
 * ephemeral store exists.
 *
 * \warning This function won't resize an existing store.  If the
 * store is already allocated, `size` is ignored.
 */
inline ubw_obj * ubw_es_maybe_alloc(ubw_heap *h, int size) {
  ubw_es_alloc(h, size);
  return h->es;
}

/** @brief Destroy the ephemeral store of h */
void ubw_es_destroy(ubw_heap *h);

/** @brief Use the ephemeral store.
 *
 * Increase the consumer count of the ephemeral store.
 */
inline void ubw_es_claim(ubw_heap *h) {
  h->esc++;
}

/** @brief End use of the ephemeral store.
 *
 * Decrease the consumer count of the ephemeral store.  If count
 * reaches zero, the store gets cleared, but not deallocated.
 */
inline void ubw_es_release(ubw_heap *h) {
  h->esc--;
  if (0 == h->esc) {

  }
}
