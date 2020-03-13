#include "parse_input.h"
#include <stdio.h>
#include <stdlib.h>

#define SCANF_ONE_CHARACTER_SUCCESS 1

static int is_invalid_size(int input_size);

int read_size_from_input(size_t *size) {
  if (!size) {
    return EXIT_FAILURE;
  }

  int input_size = 0;
  if (scanf("%i", &input_size) != SCANF_ONE_CHARACTER_SUCCESS || is_invalid_size(input_size)) {
    return EXIT_FAILURE;
  }

  *size = (size_t)input_size;

  return EXIT_SUCCESS;
}

int read_array_from_input(int **arr, size_t size) {
  if (!arr) {
    return EXIT_FAILURE;
  }

  *arr = (int *)calloc(size, sizeof(int));
  if (!*arr) {
    return EXIT_FAILURE;
  }

  for (size_t i = 0; i < size; ++i) {
    if (scanf("%i", &(*arr)[i]) != SCANF_ONE_CHARACTER_SUCCESS) {
      free(*arr);
      *arr = NULL;

      return EXIT_FAILURE;
    }
  }

  return EXIT_SUCCESS;
}

static int is_invalid_size(int input_size) {
  if (input_size < 1) {
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
