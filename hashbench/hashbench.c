#include <stdio.h>
#include <time.h>

#include "stbl.h"

extern const char *hashwords[];

#define WORDCOUNT 466544
#define REPETITIONS_COUNT 10

int lengths[WORDCOUNT];

uint32_t hashes32[WORDCOUNT];
uint64_t hashes64[WORDCOUNT];

clock_t start, end;

int comp32(const void *a, const void *b) {
  uint32_t va = *(uint32_t*)a,
    vb = *(uint32_t*)b;

  if (va < vb) return -1;
  if (va > vb) return 1;
  return 0;
}

int comp64(void *a, void *b) {
  uint64_t va = *(uint64_t*)a,
    vb = *(uint64_t*)b;

  if (va < vb) return -1;
  if (va > vb) return 1;
  return 0;
}

/ * This should

void report(const char *fname,
            short size,
            clock_t ticks,
            unsigned int unique,
            unsigned int collisions) {
  printf("| %-20s | %-4d | %-10ld | %-13d | %10d | %6.2f%% | \n",
         fname,
         size,
         ticks,
         unique,
         collisions,
         100*((double)collisions/WORDCOUNT));
}

int64_t consthash(const char* s) {
  return 12;
}

void benchmark64(const char *fname, uint64_t (func) (const char *, const char *)) {
  start = clock();
  for (int r = 0; r < REPETITIONS_COUNT; r++)
    for (int i = 0; i < WORDCOUNT; i++)
      hashes64[i] = func(hashwords[i], hashwords[i] + lengths[i]);
  end = clock();

  qsort(hashes64,
        WORDCOUNT,
        sizeof(uint64_t),
        comp32);

  unsigned int coll = 0, unique = 1;
  for (int i = 1; i < WORDCOUNT; i++) {

    if (hashes64[i] == hashes64[i-1]) {
      coll++;
    } else {
      unique++;
    }
  }
  report(fname, 64, end-start, unique, coll);
}

int main() {
  for (int i = 0; i<WORDCOUNT; i++) {
    lengths[i] = strlen(hashwords[i]);
  }

  if (hashwords[WORDCOUNT] != 0x00) {
    printf("Bad WORDCOUNT, aborting.\n");
    exit(EXIT_FAILURE);
  }

   printf("+----------------------+------+------------+---------------+------------+---------+\n");
  printf("| Function             | Size | Ticks      | Unique hashes | Collisions | Badness |\n");
  printf("+----------------------+------+------------+---------------+------------+---------+\n");

  benchmark64("ubw_fnv1_64", ubw_fnv1_64);
  benchmark64("bad", consthash);

  printf("+----------------------+------+------------+---------------+------------+---------+\n");

  return EXIT_SUCCESS;
}
