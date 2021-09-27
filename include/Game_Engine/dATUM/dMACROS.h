#ifndef D_MACROS_H
#define D_MACROS_H

#define D_EMPTY

// =========
// Stringify
// =========

#define D_STR_M(A) #A
#define D_STR_DEF(A) D_STR_M(A)

// ===========
// Concatenate
// ===========

#define D_CONCAT_M(A, B) A ## B
#define D_CONCAT_DEF(A, B) D_CONCAT_M(A, B)

#endif
