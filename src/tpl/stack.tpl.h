typedef struct {
  /** @brief Pointer to underlying data */
  ubw_conttype *d;

  unsigned int
  /** @brief Head position (last record) == length */
  h,
  /** @brief Capacity */
  c,
  /** @brief grow size (for vector-like manipulation) */
    g,
  /** @brief index as a queue (if queue, length == h-q). */
    q;
}
  ubw_contname;


/** @brief Initialize a new ubw_contname.
 *
 * @param s The ubw_contname to initialize.
 * @param capacity Length.
 * @param dptr Either null, or a pointer to an allocated memory range able to store capacity ubw_conttype objects.
 */
ubw_contname * ubw_contname_init(ubw_contname *s, const int capacity, ubw_conttype *dptr);

/** @brief Return a pointer to the head value without decreasing head index.
 *
 * This function returns either a valid pointer to the stack head or
 * NULL if the stack is empty.  To ignore the emptyness check, use
 * ubw_contname_fpeek instead.
 *
 * @param s The ubw_contname to initialize.
 */
ubw_conttype * ubw_contname_peek(const ubw_contname *s);

/** @brief Fast peek: like ubw_contname_peek, but without safety checks.
 *
 * See ubw_contname_peek for documentation.
 */
ubw_conttype * ubw_contname_fpeek(const ubw_contname *s);

/** @brief Return a pointer to the object at head of the stack and
    decrase head pointer by one.
 *
 * If the stack is empty, this function will return NULL instead.
 */
ubw_conttype * ubw_contname_pop(ubw_contname *s);
/** @brief Fast pop: like ubw_contname_pop without safety checks.
 *
 * See ubw_contname_pop for documentation.
 */
ubw_conttype * ubw_contname_fpop(ubw_contname *s);
ubw_conttype * ubw_contname_push(ubw_contname *s, ubw_conttype* o);
ubw_conttype * ubw_contname_fpush(ubw_contname *s, ubw_conttype* o);
ubw_conttype * ubw_contname_cpush(ubw_contname *s, ubw_conttype o);
ubw_conttype * ubw_contname_fcpush(ubw_contname *s, ubw_conttype o);

/**
 * @brief Return the length of a ubw_contname.
 *
 * @param s The ubw_contname.
 */
inline int ubw_contname_length(ubw_contname *s) {
  return s->h;
}

/** @brief Dereferencing peek: same as peek, but return the object instead of a pointer */
inline ubw_conttype ubw_contname_dpeek(const ubw_contname *s) {
  return *ubw_contname_peek(s);
}

/** @brief Dereferencing fpeek: same as fpeek, but return the object instead of a pointer */
inline ubw_conttype ubw_contname_dfpeek(const ubw_contname *s) {
  return *ubw_contname_fpeek(s);
}

/** @brief Dereferencing pop: same as pop, but return the object instead of a pointer */
inline ubw_conttype ubw_contname_dpop(ubw_contname *s) {
  return *ubw_contname_pop(s);
}

/** @brief Dereferencing fpop: same as fpop, but return the object instead of a pointer */
inline ubw_conttype ubw_contname_dfpop(ubw_contname *s) {
  return *ubw_contname_fpop(s);
}
