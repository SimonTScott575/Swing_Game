#ifndef GE_COMMON_H
#define GE_COMMON_H

#include <stdio.h>

#ifdef GE_DEBUG_MODE
  #define GE_DEBUG_LOG(FORMAT, ...) \
    printf(FORMAT, __VA_ARGS__)
#else
  #define GE_DEBUG_LOG(FORMAT, ...)
#endif

#endif
