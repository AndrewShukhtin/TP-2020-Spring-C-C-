#include "parse_input.h"
#include <stdio.h>
#include <stdlib.h>

#define SCANF_ONE_CHARACTER_SUCCESS 1

static int read_array_from_input(int **arr, size_t size);

int get_array_from_input(int **arr, size_t *size) {
  if (!arr || !size) {
    return EXIT_FAILURE;
  }

  int input_size = 0;
  if (scanf("%i", &input_size) != SCANF_ONE_CHARACTER_SUCCESS) {
    return EXIT_FAILURE;
  }

  if (input_size < 1) {
    fprintf(stderr, "Size should be above zero\n");
    return EXIT_FAILURE;
  }

  if (read_array_from_input(arr, (size_t)input_size)) {
    return EXIT_FAILURE;
  }

  *size = (size_t)input_size;

  return EXIT_SUCCESS;
}

static int read_array_from_input(int **arr, size_t size) {
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