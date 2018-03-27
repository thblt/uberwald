#include "symtbl.h"

ubw_symbid ubw_fnv1(ubw_char *str) {
/*   hash = offset_basis */
/* for each octet_of_data to be hashed */
/*         hash = hash * FNV_prime */
/*         hash = hash xor octet_of_data */
/* return has */
  ubw_symbid hash = 2166136261;
  int pos = 0;
  ubw_char c;
  while (c = str[pos++]) {
    hash *= 16777619;
    hash ^= c;
  }


}

ubw_symtbl * ubw_symtbl_init(ubw_symtbl *t, int sz, ubw_symb *tbl) {

}
