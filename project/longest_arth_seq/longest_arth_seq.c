#include "longest_arth_seq.h"
#include <stdlib.h>
#include <stdio.h>

#define MIN_LENGTH 2

static int compute_len_table(const int *const arr, size_t size, size_t **len_table, int *step);
static int max(int lhs, int rhs);
static int find_max_in_len_table(const size_t *const len_table, size_t size, size_t *max_val, size_t *max_idx);
static int min_len_case(const int *const arr, size_t max_len, int **arth_seq);
static int compute_arth_seq(int **arth_seq, size_t max_len, int last_elem, int step);

int longest_arith_seq(const int *const arr, size_t size, int **arth_seq) {
  if (!arr || !arth_seq) {
    return INVALID_LENGTH;
  }

  size_t *len_table = NULL;
  int step = 0;
  if (compute_len_table(arr, size, &len_table, &step)) {
    return INVALID_LENGTH;
  }

  size_t max_len = 0;
  size_t max_idx = 0;
  if (find_max_in_len_table(len_table, size, &max_len, &max_idx)) {
    free(len_table);
    return INVALID_LENGTH;
  }
  free(len_table);

  if (!min_len_case(arr, max_len, arth_seq)) {
    return MIN_LENGTH;
  }

  if (compute_arth_seq(arth_seq, max_len, arr[max_idx], step)) {
    return INVALID_LENGTH;
  }

  return max_len;
}

static int compute_len_table(const int *const arr, size_t size, size_t **len_table, int *step) {
  if (!arr || !len_table || !step) {
    return EXIT_FAILURE;
  }

  size_t number_of_non_zeros = size * size - size * (size - 1) / 2;
  *len_table = (size_t *)calloc(number_of_non_zeros, sizeof(size_t));
  if (!*len_table) {
    return EXIT_FAILURE;
  }

  for (size_t i = 0; i < size; ++i) {
    (*len_table)[i * (size - i) + i] = 1;
    for (size_t j = i + 1; j < size; ++j) {
      (*len_table)[i * (size - i) + j] = 2;
      int diff = arr[j] - arr[i];
      for (size_t k = 0; k < i; ++k) {
        if (arr[i] - arr[k] == diff) {
          (*len_table)[i * (size - i) + j]
            = max((*len_table)[k * (size - k) + i] + 1, (*len_table)[i * (size - i) + j]);
          *step = diff;
        }
      }
    }
  }

  return EXIT_SUCCESS;
}

static int max(int lhs, int rhs) {
  if (lhs < rhs) {
    return rhs;
  }

  return lhs;
}

static int find_max_in_len_table(const size_t *const len_table, size_t size, size_t *max_val, size_t *max_idx) {
  if (!len_table || !max_val || !max_idx) {
    return EXIT_FAILURE;
  }

  size_t max_len = 0;
  size_t idx = 0;
  for (size_t i = 0; i < size; ++i) {
    for (size_t j = i + 1; j < size; ++j) {
      if (max_len < len_table[i * (size - i) + j]) {
        max_len = len_table[i * (size - i) + j];
        idx = j;
      }
    }
  }

  *max_val = max_len;
  *max_idx = idx;
  return EXIT_SUCCESS;
}

static int min_len_case(const int *const arr, size_t max_len, int **arth_seq) {
  if (!arr || max_len != MIN_LENGTH) {
    return EXIT_FAILURE;
  }

  *arth_seq = (int *)calloc(max_len, sizeof(int));
  if (!*arth_seq) {
    return EXIT_FAILURE;
  }

  (*arth_seq)[0] = arr[0];
  (*arth_seq)[1] = arr[1];

  return EXIT_SUCCESS;
}

static int compute_arth_seq(int **arth_seq, size_t max_len, int last_elem, int step) {
  if (!arth_seq) {
    return EXIT_FAILURE;
  }

  *arth_seq = (int *)calloc(max_len, sizeof(int));
  if (!*arth_seq) {
    return EXIT_FAILURE;
  }

  for (int i = max_len - 1; i >= 0; --i) {
    (*arth_seq)[i] = last_elem  - step * (max_len - 1 - i);
  }

  return EXIT_SUCCESS;
}
