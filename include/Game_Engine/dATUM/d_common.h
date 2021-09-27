#define D_PASTE_NOEXP(A, B) A ## B
#define D_PASTE(A, B) D_PASTE_NOEXP(A,B)
#define D_PASTE3(A,B,C) D_PASTE(D_PASTE(A,B),C)
