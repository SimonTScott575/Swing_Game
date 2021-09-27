#ifndef GR_TYPES_H
#define GR_TYPES_H

#include <Game_Engine/dATUM/dTypes.h>

#include <stdint.h>

D_HEADER_dType(uint32_t, , grType) // D_DEFINE_dType(uint32_t, , grType)

extern struct grTypes grTypes;

void grInit_Types();

#endif
