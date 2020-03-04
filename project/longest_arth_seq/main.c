#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "longest_arth_seq.h"

#define SCANF_SINGLE_VAL_SUCCESS 1
#define MIN_ARR_SIZE 1
#define INVALID_INPUT "Invalid input\n"

void print_arr(const int *const arr, size_t size);

int main(void) {
  int32_t input_size = INVALID_LENGTH;  // Not valid size as default
  if (scanf("%d", &input_size) != SCANF_SINGLE_VAL_SUCCESS) {
    fprintf(stderr, INVALID_INPUT);
    return EXIT_FAILURE;
  }

  if (input_size < MIN_ARR_SIZE) {
    fprintf(stderr, "Size should be positive\n");
    return EXIT_FAILURE;
  }

  const size_t size = (size_t)input_size;
  int *const arr = (int *)malloc(size * sizeof(int));
  if (!arr) {
    return EXIT_FAILURE;
  }

  for (size_t iter = 0; iter < size; ++iter) {
    if (scanf("%d", &arr[iter]) != SCANF_SINGLE_VAL_SUCCESS) {
      fprintf(stderr, INVALID_INPUT);
      free(arr);
      return EXIT_FAILURE;
    }
  }

  int *arth_seq = NULL;
  int arth_seq_len = longest_arith_seq(arr, size, &arth_seq);
  if (arth_seq_len == INVALID_LENGTH) {
    free(arr);
    return EXIT_FAILURE;
  }

  printf("arth_seq_size: %d\n", arth_seq_len);
  print_arr(arth_seq, arth_seq_len);
  
  free(arr);
  free(arth_seq);
  return EXIT_SUCCESS;
}

void print_arr(const int *const arr, size_t size) {
  if (!arr) {
    return;
  }

  for (size_t iter = 0; iter < size; ++iter) {
    printf("%d ", arr[iter]);
  }
  printf("\n");
}
