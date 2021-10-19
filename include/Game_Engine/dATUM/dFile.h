#ifndef D_FILE_H
#define D_FILE_H

//NOTE: MUST be in the correct r/w mode for all functions to behave as expected.

#include <stdio.h>
#include <stdint.h>

#define D_RESET_RW(file) fseek((file),0,SEEK_CUR)

// =====
// State
// =====

uint64_t dFile_length(FILE* file);

int32_t dStart_of_file(FILE* file);
int32_t dEnd_of_file(FILE* file);

int32_t dStart_of_line(FILE* file);
int32_t dEnd_of_line(FILE* file);

uint64_t dLength_Of_Line(FILE* file);

// ==========
// Navigation
// ==========

int32_t dNext_Line(FILE* file);
int32_t dEnd_Line(FILE* file);
int32_t dStart_Line(FILE* file);

#endif
