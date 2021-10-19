#ifndef D_LLIST_H
#define D_LLIST_H

#include <stdlib.h>
#include <stdint.h>
#include <stdarg.h>

#include "d_common.h"

#if defined(D_AS_HEADER)
  #define D__LList_SCOPE__ extern //TODO: not working, complicated
#elif defined(D_AS_SOURCE)
  #define D__LList_SCOPE__ //TODO: not working, complicated
#else
  #define D__LList_SCOPE__ static
#endif

// ==================
// DECLARATION Macros
// ==================

#define dLList(POSTFIX) D_PASTE3(dLList__,POSTFIX,__)
#define dNode_LL(POSTFIX) D_PASTE3(dNode_LL__,POSTFIX,__)

#define D__TYPES_HEADER_LLIST__(TYPE, POSTFIX) \
  typedef struct dLList(POSTFIX) dLList(POSTFIX) ; \
  typedef struct dNode_LL(POSTFIX) dNode_LL(POSTFIX) ; \
  struct dLList(POSTFIX) { \
    dNode_LL(POSTFIX) * start; \
    dNode_LL(POSTFIX) * end; \
  }; \
  struct dNode_LL(POSTFIX) { \
    TYPE element; \
    dNode_LL(POSTFIX) * next; \
    dNode_LL(POSTFIX) * prev; \
  };

#define new_dLList(POSTFIX) D_PASTE3(new_dLList__, POSTFIX, __)
#define del_dLList(POSTFIX) D_PASTE3(del_dLList__, POSTFIX, __)
#define dPrepend_LL(POSTFIX) D_PASTE3(dPrepend_LL__,POSTFIX,__)
#define dAppend_LL(POSTFIX) D_PASTE3(dAppend_LL__,POSTFIX,__)
#define dInsert_Before_LL(POSTFIX) D_PASTE3(dInsert_Before_LL__,POSTFIX,__)
#define dInsert_After_LL(POSTFIX) D_PASTE3(dInsert_After_LL__,POSTFIX,__)
#define dRemove_LL(POSTFIX) D_PASTE3(dRemove_LL__,POSTFIX,__)
#define dCircularise_LL(POSTFIX) D_PASTE3(dCircularise_LL__,POSTFIX,__)
#define dLinearise_LL(POSTFIX) D_PASTE3(dLinearise_LL__,POSTFIX,__)

#define D__FUNCS_HEADER_LLIST__(TYPE, POSTFIX, SCOPE) \
  SCOPE dLList(POSTFIX) * new_dLList(POSTFIX) ( \
    uint64_t N, \
    TYPE * init_values \
  ); \
  SCOPE void del_dLList(POSTFIX) ( \
    dLList(POSTFIX) * llist \
  ); \
  SCOPE dNode_LL(POSTFIX) * dPrepend_LL(POSTFIX) ( \
    TYPE new, \
    dLList(POSTFIX) * llist \
  ); \
  SCOPE dNode_LL(POSTFIX) * dAppend_LL(POSTFIX) ( \
    TYPE new, \
    dLList(POSTFIX) * llist \
  ); \
  SCOPE dNode_LL(POSTFIX) * dInsert_Before_LL(POSTFIX) ( \
    TYPE new, \
    dNode_LL(POSTFIX) * node, \
    dLList(POSTFIX) * llist \
  ); \
  SCOPE dNode_LL(POSTFIX) * dInsert_After_LL(POSTFIX) ( \
    TYPE new, \
    dNode_LL(POSTFIX) * node, \
    dLList(POSTFIX) * llist \
  ); \
  SCOPE TYPE dRemove_LL(POSTFIX) ( \
    dNode_LL(POSTFIX) * node, \
    dLList(POSTFIX) * llist \
  ); \
  SCOPE void dCircularise_LL(POSTFIX) ( \
    dLList(POSTFIX) * llist \
  ); \
  SCOPE void dLinearise_LL(POSTFIX) ( \
    dLList(POSTFIX) * llist \
  );

#define D_HEADER_LLIST(TYPE, POSTFIX) \
  D__TYPES_HEADER_LLIST__(TYPE, POSTFIX) \
  D__FUNCS_HEADER_LLIST__(TYPE, POSTFIX, )
/*** LEGACY ***/
#define D_HEADER_dLList D_HEADER_LLIST
/**************/

// ============
// Declarations
// ============

#ifndef D_NO_DEFAULTS

  D__TYPES_HEADER_LLIST__(int, int)
  D__TYPES_HEADER_LLIST__(unsigned int, uint)
  D__TYPES_HEADER_LLIST__(float, float)
  D__TYPES_HEADER_LLIST__(double, double)

  D__FUNCS_HEADER_LLIST__(int, int, D__LList_SCOPE__)
  D__FUNCS_HEADER_LLIST__(unsigned int, uint, D__LList_SCOPE__)
  D__FUNCS_HEADER_LLIST__(float, float, D__LList_SCOPE__)
  D__FUNCS_HEADER_LLIST__(double, double, D__LList_SCOPE__)

#endif

// =================
// DEFINITION Macros
// =================

// dLList by reference
#define D__SOURCE_LLIST__(TYPE, POSTFIX, SCOPE) \
  SCOPE dLList(POSTFIX) * new_dLList(POSTFIX) ( \
    uint64_t N, \
    TYPE * init_values \
  ) { \
      \
    dLList(POSTFIX) * result = malloc(sizeof( dLList(POSTFIX) )); \
    if (result == NULL) { return NULL; } \
    result->start = NULL; \
    result->end = NULL; \
                        \
    if ( init_values != NULL ) { \
      result->start = malloc( sizeof( dNode_LL(POSTFIX) ) ); \
      if (result->start == NULL) { \
        del_dLList(POSTFIX)(result); \
        return NULL;  \
      } \
      result->start->element = init_values[0]; \
      result->start->prev = NULL; \
                                  \
      dNode_LL(POSTFIX) * current = result->start; \
      for (int i = 1; i < N; i++) { \
        current->next = malloc( sizeof( dNode_LL(POSTFIX) ) ); \
        if (current->next == NULL) { \
          del_dLList(POSTFIX)(result); \
          return NULL; \
        } \
        current->next->prev = current; \
        current = current->next; \
                                 \
        current->element = init_values[i]; \
      } \
        \
      current->next = NULL; \
      result->end = current; \
    } \
      \
    return result; \
  } \
    \
  SCOPE void del_dLList(POSTFIX) ( \
    dLList(POSTFIX) * list \
  ) { \
    dNode_LL(POSTFIX) * current = list->start; \
    dNode_LL(POSTFIX) * next; \
    while (current != NULL) { \
      next = current->next; \
      free(current); \
      current = next; \
                      \
      if (current == list->start) { \
        break; \
      } \
    } \
      \
    free(list); \
  } \
    \
  SCOPE dNode_LL(POSTFIX) * dPrepend_LL(POSTFIX) ( \
    TYPE new, \
    dLList(POSTFIX) * llist \
  ) { \
    dNode_LL(POSTFIX) * result = malloc( sizeof( dNode_LL(POSTFIX) ) ); \
    if (result == NULL) { return NULL; } \
    result->element = new; \
                           \
    if (llist->start != NULL) { \
      result->prev = llist->start->prev; \
      result->next = llist->start; \
      llist->start->prev = result; \
      llist->start = result; \
    } else { \
      llist->start = llist->end = result; \
      result->next = result->prev = NULL; \
    } \
                   \
    return result; \
  } \
    \
  SCOPE dNode_LL(POSTFIX) * dAppend_LL(POSTFIX) ( \
    TYPE new, \
    dLList(POSTFIX) * llist \
  ) { \
    dNode_LL(POSTFIX) * result = malloc( sizeof( dNode_LL(POSTFIX) ) ); \
    if (result == NULL) { return NULL; } \
    result->element = new; \
                           \
    if (llist->end != NULL) { \
      result->next = llist->end->next; \
      result->prev = llist->end; \
      llist->end->next = result; \
      llist->end = result; \
    } else { \
      llist->start = llist->end = result; \
      result->next = result->prev = NULL; \
    } \
      \
    return result; \
  } \
    \
  SCOPE dNode_LL(POSTFIX) * dInsert_Before_LL(POSTFIX)( \
    TYPE new, \
    dNode_LL(POSTFIX) * node, \
    dLList(POSTFIX) * llist \
  ) { \
    dNode_LL(POSTFIX) * result = malloc( sizeof( dNode_LL(POSTFIX) ) ); \
    if (result == NULL) { return NULL; } \
    result->element = new; \
                           \
    result->next = node; \
    result->prev = node->prev; \
                                  \
    if (node->prev != NULL) { \
      node->prev->next = result; \
    } \
    node->prev = result; \
                            \
    if (llist->start == node) { \
      llist->start = result; \
    } \
                           \
    return result; \
  } \
  SCOPE dNode_LL(POSTFIX) * dInsert_After_LL(POSTFIX) ( \
    TYPE new, \
    dNode_LL(POSTFIX) * node, \
    dLList(POSTFIX) * llist \
  ) { \
    dNode_LL(POSTFIX) * result = malloc( sizeof( dNode_LL(POSTFIX) ) ); \
    if (result == NULL) { return NULL; } \
    result->element = new; \
                           \
    result->next = node->next; \
    result->prev = node; \
                            \
    if (node->next != NULL) { \
      node->next->prev = result; \
    } \
    node->next = result; \
                            \
    if (llist->end == node) { \
      llist->end = result; \
    } \
      \
    return result; \
  } \
  SCOPE TYPE dRemove_LL(POSTFIX) ( \
    dNode_LL(POSTFIX) * node, \
    dLList(POSTFIX) * llist \
  ) { \
      \
    if (node->prev != NULL) { \
      node->prev->next = node->next; \
    } \
    if (node->next != NULL) { \
      node->next->prev = node->prev; \
    } \
    if (node == llist->start) { \
      llist->start = node->next; \
    } \
    if (node == llist->end) { \
      llist->end = node->prev; \
    } \
      \
    TYPE result = node->element; \
    free(node); \
                   \
    return result; \
  } \
    \
  SCOPE void dCircularise_LL(POSTFIX) ( \
    dLList(POSTFIX) * llist \
  ) { \
    if (llist->start != NULL) { \
      llist->end->next = llist->start; \
      llist->start->prev = llist->end; \
    } \
  } \
  SCOPE void dLinearise_LL(POSTFIX) ( \
    dLList(POSTFIX) * llist \
  ) { \
    if (llist->start != NULL) { \
      llist->start->prev = NULL; \
      llist->end->next = NULL; \
    } \
  }
#define D_SOURCE_LLIST(TYPE, POSTFIX) \
  D__FUNCS_HEADER_LLIST__(TYPE, POSTFIX, ) \
  D__SOURCE_LLIST__(TYPE, POSTFIX, )
#define D_STATIC_LLIST(TYPE, POSTFIX) \
  D__FUNCS_HEADER_LLIST__(TYPE, POSTFIX, static) \
  D__SOURCE_LLIST__(TYPE, POSTFIX, static)

/*** LEGACY ***/
#define D_SOURCE_dLList D_SOURCE_LLIST
#define D_STATIC_dLList D_STATIC_LLIST
/*************/

// ========
// Defaults
// ========

#ifndef D_NO_DEFAULTS

  D__SOURCE_LLIST__(int, int, D__LList_SCOPE__)
  D__SOURCE_LLIST__(unsigned int, uint, D__LList_SCOPE__)
  D__SOURCE_LLIST__(float, float, D__LList_SCOPE__)
  D__SOURCE_LLIST__(double, double, D__LList_SCOPE__)

#endif

#endif
