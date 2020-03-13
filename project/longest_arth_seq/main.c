#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include "parse_input.h"
#include "longest_arth_seq.h"

void print_arr(const int *const arr, size_t size) {
  if (!arr) {
    return;
  }

  for (size_t i = 0; i < size; ++i) {
    printf("%i ", arr[i]);
  }

  printf("\n");
}

int main(void) {
  printf("Enter array size:\n");
  size_t size = 0;
  if (read_size_from_input(&size)) {
    return EXIT_FAILURE;
  }

  printf("Enter array:\n");
  int *arr = NULL;
  if (read_array_from_input(&arr, size)) {
    return EXIT_FAILURE;
  }

  int *arth_seq = NULL;
  int arth_size = longest_arith_seq(arr, size, &arth_seq);
  if (arth_size == INVALID_LENGTH) {
    return EXIT_FAILURE;
  }

  printf("Longest arithmetic sequence in array:\n");
  print_arr(arth_seq, (size_t)arth_size);

  return EXIT_SUCCESS;
}
