#ifndef D_SORT_H
#define D_SORT_H

#include <stdbool.h>
#include <stdint.h>

#if defined(D_AS_HEADER)
  #define D__SORT_SCOPE__ extern //TODO: not working, complicated
#elif defined(D_AS_SOURCE)
  #define D__SORT_SCOPE__ //TODO: not working, complicated
#else
  #define D__SORT_SCOPE__ static
#endif

// ============
// Declarations
// ============

typedef bool (*dCompare_fn)(void* a, void* b); // returns 1 if a <= b in sort order else 0 //? lt or lte ?
typedef void (*dAssign_fn)(void* dest, void* source);
typedef void* (*dIncrement_fn)(void* to_increment, uint64_t n);

// ===========
// Definitions
// ===========

D__SORT_SCOPE__ void dSort_INSERTION(void* array, void* dest, uint64_t length, dCompare_fn comp, dAssign_fn assign, dIncrement_fn incr) {

  assign( dest, array );
  for (uint64_t i = 1, j = 1; (j = i, i < length); i++, j++) {

    while ( comp( incr(array, i), incr(dest, j-1) ) ) {
      assign( incr(dest, j), incr(dest, j-1) );
      if (--j == 0) { break; }
    }
    assign( incr(dest, j), incr(array, i) );

  }
}

#endif
