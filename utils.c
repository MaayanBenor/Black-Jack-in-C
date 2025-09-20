#include "utils.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void my_assert(bool condition, const char *file, const char *func, const int line, const char *error_message) {
  if (!condition) {
    printf(RED);
    fprintf(stderr, "file: %s function: %s line: %d message: %s", file, func, line, error_message);
    printf(RST);
    exit(EXIT_FAILURE);
  }
}

void clear_buffer() {
  scanf("%*[^\n]"); // clears the buffer until \n
  getchar();        // clears the leftover \n
}

size_t get_user_input_size_t() {
  char user_input[100];
  size_t result;
  char *end_pointer;

  while (1) {
    scanf("%99s", user_input);
    clear_buffer();

    if (user_input[0] == '-') {
      printf("Do you want me to give you money?...\nTry again please: ");
      continue;
    }

    errno = 0;
    result = strtoull(user_input, &end_pointer, 10);

    // Check for conversion failure or overflow
    if (errno == ERANGE || *end_pointer != '\0') {

      printf("Whoah! That number is way to big, our casino doesn't handle these types of sums.\nTry again please: ");
      continue;
    }

    break;
  }

  return result;
}