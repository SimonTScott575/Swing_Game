#include "../dFile.c"

int main() {

  // =====
  // Files
  // =====

  FILE* empty_file = fopen("tests/empty_file.txt", "rb");
  if (empty_file == NULL) {
    printf("ERROR : Failed to open file");
    fclose(empty_file);
    return 1;
  }
  FILE* test_file = fopen("tests/test_file.txt", "rb");
  if (test_file == NULL) {
    printf("ERROR : Failed to open file");
    fclose(test_file);
    return 1;
  }
  FILE* test_file2 = fopen("tests/test_file2.txt", "rb");
  if (test_file2 == NULL) {
    printf("ERROR : Failed to open file");
    fclose(test_file2);
    return 1;
  }

  int n_files = 3;

  FILE* files[3] = { empty_file, test_file, test_file2 };
  int file_lengths[3] = { 0, 28, 16 };

  // =======
  // Testing
  // =======

  for (int i = 0; i < n_files; i++) {
    FILE* file = files[i];
    int file_length = file_lengths[i];

    for (int j = 0; j < file_length + 2; j++) {

      fseek(file, j, SEEK_SET);
      int file_pos = ftell(file);

      int result;

      fseek(file, j, SEEK_SET);
      result = dFile_length(file);
      if (result != file_length) {
        printf("\n\nWRONG TEST RESULT : dFile_length : file %d file_pos %d result %d\n\n", i, j, result);
      }
      if (file_pos != ftell(file)) {
        printf("\n\nWRONG TEST RESULT : dFile_length: file %d file_pos %d result %d\n\n", i, j, result);
      }

      fseek(file, j, SEEK_SET);
      result = dStart_of_file(file);
      if (file_pos == 0 && result != 1) {
        printf("\n\nWRONG TEST RESULT : dStart_of_file : file %d file_pos %d result %d\n\n", i, j, result);
      }
      if (file_pos != 0 && result == 1) {
        printf("\n\nWRONG TEST RESULT : dStart_of_file : file %d file_pos %d result %d\n\n", i, j, result);
      }
      if (file_pos != ftell(file)) {
        printf("\n\nWRONG TEST RESULT : dStart_of_file : file %d file_pos %d result %d\n\n", i, j, result);
      }

      fseek(file, j, SEEK_SET);
      result = dEnd_of_file(file);
      if ( file_pos >= file_length && result != 1) {
        printf("\n\nWRONG TEST RESULT : dEnd_of_file : file %d file_pos %d result %d\n\n", i, j, result);
      }
      if (file_pos < file_length && result == 1) {
        printf("\n\nWRONG TEST RESULT : dEnd_of_file : file %d file_pos %d result %d\n\n", i, j, result);
      }
      if (file_pos != ftell(file)) {
        printf("\n\nWRONG TEST RESULT : dEnd_of_file : file %d file_pos %d result %d\n\n", i, j, result);
      }

      fseek(file, j, SEEK_SET);
      result = dStart_of_line(file);
      if (file_pos != ftell(file)) {
        printf("\n\nWRONG TEST RESULT : dStart_of_line : file %d file_pos %d result %d\n\n", i, j, result);
      }
      if (file_pos == 0 && result != 1) {
        printf("\n\nWRONG TEST RESULT : dStart_of_line : file %d file_pos %d result %d\n\n", i, j, result);
      }
      if (file_length == 0) {
        if (file_pos > 0 && result != 0) {
          printf("\n\nWRONG TEST RESULT : dStart_of_line : file %d file_pos %d result %d\n\n", i, j, result);
        }
      }
      if (0 < file_pos && file_pos < file_length) {
        fseek(file, -1, SEEK_CUR);
        char prev = fgetc(file);
        if (prev == '\n' && result != 1) {
          printf("\n\nWRONG TEST RESULT : dStart_of_line : file %d file_pos %d result %d\n\n", i, j, result);
        }
        if (prev != '\n' && result != 0) {
          printf("\n\nWRONG TEST RESULT : dStart_of_line : file %d file_pos %d result %d\n\n", i, j, result);
        }
      }
      if (0 < file_length && file_length < file_pos) {
        if (result != 0) {
          printf("\n\nWRONG TEST RESULT : dStart_of_line : file %d file_pos %d result %d\n\n", i, j, result);
        }
      }

      fseek(file, j, SEEK_SET);
      result = dEnd_of_line(file);
      if (file_pos != ftell(file)) {
        printf("\n\nWRONG TEST RESULT : dEnd_of_line : file %d file_pos %d result %d\n\n", i, j, result);
      }
      if (file_pos >= file_length && result != -1) {
        printf("\n\nWRONG TEST RESULT : dEnd_of_line : file %d file_pos %d result %d\n\n", i, j, result);
      }
      if (2 < file_length && file_pos <= file_length-2) {
        char next = fgetc(file);
        char next_next = fgetc(file);
        fseek(file, -2, SEEK_CUR);
        if (next == '\r' && next_next == '\n') {
          if (result != 1) {
            printf("\n\nWRONG TEST RESULT : dEnd_of_line : file %d file_pos %d result %d\n\n", i, j, result);
          }
        } else if (next == '\n') {
          if (result != 1) {
            printf("\n\nWRONG TEST RESULT : dEnd_of_line : file %d file_pos %d result %d\n\n", i, j, result);
          }
        } else {
          if (result != 0) {
            printf("\n\nWRONG TEST RESULT : dEnd_of_line : file %d file_pos %d result %d\n\n", i, j, result);
          }
        }
      }
      if (1 < file_length && file_pos <= file_length-1) {
        char next = fgetc(file);
        fseek(file, -1, SEEK_CUR);
        if (next == '\n') {
          if (result != 1) {
            printf("\n\nWRONG TEST RESULT : dEnd_of_line : file %d file_pos %d result %d\n\n", i, j, result);
          }
        } else if ( next != '\r' ) {
          if (result != 0) {
            printf("\n\nWRONG TEST RESULT : dEnd_of_line : file %d file_pos %d result %d\n\n", i, j, result);
          }
        }
      }

      fseek(file, j, SEEK_SET);
      result = dEnd_LINE(file);
      int is_eol = dEnd_of_line(file);
      if (result != is_eol) {
        printf("\n\nWRONG TEST RESULT : dEnd_LINE : file %d file_pos %d result %d\n\n", i, j, result);;
      }

      fseek(file, j, SEEK_SET);
      result = dNext_LINE(file);
      if (ftell(file) < file_length) {
        if (result != 1) {
          printf("\n\nWRONG TEST RESULT : dNext_LINE : file %d file_pos %d result %d\n\n", i, j, result);
        }
      }
      if (file_length > 1 && 0 < ftell(file) && ftell(file) < file_length) {
        fseek(file, -1, SEEK_CUR);
        if (fgetc(file) != '\n') {
          printf("\n\nWRONG TEST RESULT : dNext_LINE : file %d file_pos %d result %d\n\n", i, j, result);
        }
      }
      
      fseek(file, j, SEEK_SET);
      result = dStart_LINE(file);
      if (ftell(file) == 0 && result != -1) {
        printf("\n\nWRONG TEST RESULT : dStart_LINE : file %d file_pos %d result %d\n\n", i, j, result);
      }
      if (ftell(file) != 0) {
        fseek(file, -1, SEEK_CUR);
        if (fgetc(file) != '\n') {
          printf("\n\nWRONG TEST RESULT : dStart_LINE : file %d file_pos %d result %d\n\n", i, j, result);
        }
        if (result != 1) {
          printf("\n\nWRONG TEST RESULT : dStart_LINE : file %d file_pos %d result %d\n\n", i, j, result);
        }
      }

    }
  }

  // =====
  // Close
  // =====

  fclose(empty_file);
  fclose(test_file);
  fclose(test_file2);

  printf("\n\nPROGRAM TERMINATES SUCCESFULLY\n\n");

  return 0;

}
