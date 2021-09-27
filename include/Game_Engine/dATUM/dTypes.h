#ifndef D_TYPES_H
#define D_TYPES_H

#if defined(D_AS_HEADER)
  #define D__TYPES_SCOPE__ extern //TODO: not working, complicated
#elif defined(D_AS_SOURCE)
  #define D__TYPES_SCOPE__ //TODO: not working, complicated
#else
  #define D__TYPES_SCOPE__ static
#endif

// ==================
// DECLARATION Macros
// ==================

#define D__TYPES_HEADER_TYPE__(TYPE, ADDITIONAL, NAME) \
  typedef TYPE NAME; \
  struct NAME ## s; \
  struct NAME ## s { \
    NAME _uint; \
    NAME _uint8_t; \
    NAME _uint16_t; \
    NAME _uint32_t; \
    NAME _uint64_t; \
                    \
    NAME _int; \
    NAME _int8_t; \
    NAME _int16_t; \
    NAME _int32_t; \
    NAME _int64_t; \
                   \
    NAME _float; \
    NAME _double; \
                  \
    NAME _bool; \
                \
    NAME _size_t; \
                  \
    NAME _dType; \
                \
    ADDITIONAL \
  };

#define D_HEADER_TYPE(TYPE, ADDITIONAL, NAME) \
  D__TYPES_HEADER_TYPE__(TYPE, ADDITIONAL, NAME)
/*** LEGACY ***/
#define D_HEADER_dType D_HEADER_TYPE
/**************/

// ============
// Declarations
// ============

#ifndef D_NO_DEFAULTS

  D__TYPES_HEADER_TYPE__(int, , dType)

#endif

// ===========
// Definitions
// ===========

#ifndef D_NO_DEFAULTS

  D__TYPES_SCOPE__ const struct dTypes dTypes = {

    ._uint          = 0,
    ._uint8_t       = 1,
    ._uint16_t      = 2,
    ._uint32_t      = 3,
    ._uint64_t      = 4,

    ._int           = 5,
    ._int8_t        = 6,
    ._int16_t       = 7,
    ._int32_t       = 8,
    ._int64_t       = 9,

    ._float         = 10,
    ._double        = 11,

    ._bool          = 12,

    ._size_t        = 13,


    ._dType         = 14,

  };

#endif

#endif
