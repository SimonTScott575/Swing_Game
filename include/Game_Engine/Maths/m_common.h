#ifndef M_COMMON_H
#define M_COMMON_H

#define M_PASTE_T(A,B) A ## B
#define M_PASTE(A,B) M_PASTE_T(A,B)

#define M_PASTE3(A,B,C) M_PASTE(M_PASTE(A,B),C)
#define M_PASTE5(A,B,C,D,E) M_PASTE3(M_PASTE3(A,B,C),D,E)

#endif
