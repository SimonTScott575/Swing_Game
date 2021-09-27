#include "dFile.h"

// =====
// State
// =====

uint64_t dFile_length(FILE* file) {

  D_RESET_RW(file);

  uint64_t init_pos = ftell(file);
  fseek(file, 0, SEEK_END);
  uint64_t length = ftell(file);
  fseek(file, init_pos, SEEK_SET);

  D_RESET_RW(file);

  return length;
}

int32_t dStart_of_file(FILE* file) {
  return !ftell(file);
}
int32_t dEnd_of_file(FILE* file) {

  D_RESET_RW(file);

  int next_char = fgetc(file);

  if (next_char == EOF) {
    return 1;
  }
  fseek(file, -1, SEEK_CUR);

  D_RESET_RW(file);

  return 0;
}

// Checks if file at start of the file (ftell == 0)
// returns 1 if infront of \n
// returns -1 if at start of file
// returns 0 else
int32_t dStart_of_line(FILE* file) {

  D_RESET_RW(file);

  // If start of file, return 1
  if (!ftell(file)) {
    return -1;
  }
  // If previous character \n then return 1 else 0
  fseek(file, -1, SEEK_CUR);
  int prev_char = fgetc(file);
  if (prev_char == EOF) {
    fseek(file, 1, SEEK_CUR);
    return 0;
  }

  D_RESET_RW(file);

  return prev_char == '\n';
}
// Checks if file position at end of a line (\n or \r\n or EOF)
// returns 1 if at \n or \r\n
// returns -1 if at EOF
// returns 0 else
int32_t dEnd_of_line(FILE* file) {

  D_RESET_RW(file);

  int next_char = fgetc(file);
  int next_next_char;

  if (next_char == EOF) { return -1; }
  if (next_char == '\n') {
    fseek(file, -1, SEEK_CUR);
    return 1;
  }

  if ( (next_next_char = fgetc(file)) == '\n' && next_char == '\r' ) {
    fseek(file, -2, SEEK_CUR);
    return 1;
  }
  if (next_next_char == EOF) {
    fseek(file, -1, SEEK_CUR);
    return 0;
  }

  fseek(file, -2, SEEK_CUR);

  D_RESET_RW(file);

  return 0;
}

uint64_t dLength_Of_Line(FILE* file) {

  D_RESET_RW(file);

  long int start_pos = ftell(file);

  uint64_t n = 0;

  int c = fgetc(file);
  while (c != '\r' && c != '\n' && c != EOF) {
    n++;
    c = fgetc(file);
  }

  fseek(file, start_pos, SEEK_SET);

  D_RESET_RW(file);

  return n;

}

// ==========
// Navigation
// ==========

int32_t dNext_Line(FILE* file) {

  D_RESET_RW(file);

  int current_char;
  while ( (current_char = fgetc(file)) != EOF ) {
    if (current_char == '\n') {
      return 1;
    }
  }

  D_RESET_RW(file);

  return -1;
}
// Moves file position to the end of the line it is currently on (given by \r,\r\n,EOF).
// If between \r and \n then it was move back behind that \r
// returns 1 if at end of line
// returns -1 else if at EOF
int32_t dEnd_Line(FILE* file) {

  D_RESET_RW(file);

  if (dFile_length(file) == 1) {
    if (ftell(file) == 0) {
      if (fgetc(file) == '\n') {
        fseek(file, -1, SEEK_CUR);
        return 1;
      } else {
        return -1;
      }
    }
  }

  if (dNext_Line(file) == -1) {
      return -1;
  }

  fseek(file, -2, SEEK_CUR);
  char current_char = fgetc(file);
  if (current_char == '\r') {
    fseek(file, -1, SEEK_CUR);
  }

  D_RESET_RW(file);

  return 1;
}
// Moves file position to just after previous \n, or start of file if non existent;
// returns 1 if then behind \n
// returns -1 if then at start of file
int32_t dStart_Line(FILE* file) {

  D_RESET_RW(file);

  if (ftell(file) > dFile_length(file)) {
    fseek(file, 0, SEEK_END);
  }

  if (ftell(file) == 0) {
    return -1;
  }

  fseek(file, -1, SEEK_SET);
  if (fgetc(file) == '\n') {
    return 1;
  }

  do {
    fseek(file, -2, SEEK_CUR);
    if (fgetc(file) == '\n') {
      return 1;
    }
  } while (ftell(file) != 1);

  fseek(file, 0, SEEK_SET);

  D_RESET_RW(file);

  return -1;
}

// void dClear_Line(FILE* file) {
//
//   D_RESET_RW(file);
//
//   char start_pos = ftell(file);
//
//   uint64_t length_of_line = dLength_Of_Line(file);
//
//   char c = fgetc(file);
//   while ( c != '\r' && c != '\n' && c != EOF ) {
//
//     fputc('\0', file);
//
//   }
//
//   D_RESET_RW(file);
//
// }
