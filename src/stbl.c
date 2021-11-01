#include "stbl.h" 
ubw_stbl * ubw_stbl_init(ubw_stbl *t, int capac, ubw_symb *flt, ubw_symb *rlt) {
  t->flt = (NULL == flt) ? malloc(sizeof(ubw_symb) * capac) : flt;

  t->c = capac;
  t->sz = 0;

  return t;
}

uint64_t ubw_fnv1_64(const char *beg, const char *end) {
  uint64_t hash = 14695981039346656037;
  const char *pos = beg;
  do {
    hash *= 1099511628211;
    hash ^= *pos;
  } while (++pos < end);
  return hash;
}

char * ubw_stbl_reverse(const ubw_stbl *t, const ubw_symbid id) {
  for (int i = 0; i<t->sz; i++) {
    if (t->flt[i].id == id)
      return t->flt[i].name;
  }
  return NULL;
}

ubw_symbid ubw_stbl_intern(ubw_stbl *t, const char *beg, const char *end) {
  // FIXME Check symbol length before interning

  ubw_symbhash hash = ubw_stbl_hash(beg, end);
  ubw_symb* pos;

  // Lookup/memcpy only if the table is not empty.
  if (0 != t->sz) {

    pos = ubw_symb_hlk(t, hash);

    // If we already know this symbol.
    // @FIXME Handle collisions
    if (pos->hash == hash) {
      return pos->id;
    }

    if (hash > pos->hash) pos++;

    // Make room for the new symbol
    for (ubw_symb *ptr = &t->flt[t->sz]; ptr > pos ; ptr--) {
      memcpy(ptr, ptr-1, sizeof(ubw_symb));
    }
  } else {
    pos = t->flt;
  }

  t->sz++;
  pos->hash = hash;
  pos->id = t->sz;
  memcpy(pos->name, beg, end-beg);
  pos->name[end-beg] = 0x00; // FIXME this could be *a lot* cleaner.
  return t->sz;
}

ubw_symb * _ubw_symb_hlk(ubw_symbhash hash, ubw_symb *low, ubw_symb *high) {
  ubw_symb * pivot = low + (high-low) / 2;

  if ((pivot->hash == hash)
      || (pivot == low)) return pivot;

  if (pivot->hash > hash) {
    return _ubw_symb_hlk(hash, low, pivot);
  } else {
    return _ubw_symb_hlk(hash, pivot, high);
  }
}

ubw_symb * ubw_symb_hlk(ubw_stbl *t, ubw_symbhash h) {
  // ubw_symbhash hash = ubw_stbl_hash(s);
  return _ubw_symb_hlk(h, t->flt, &t->flt[t->sz]);
}
