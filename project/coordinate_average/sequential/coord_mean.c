#include "coord.h"
#include "coord_arrays.h"
#include "coord_mean.h"

#include <stdio.h>
#include <stdlib.h>

#define UNKNOWN_ERROR_MSG "Unknown error occured while computing mean"

static int compute_mean_by_coordinate(const double *const arr, size_t size, double *mean_value);

int compute_each_coordinate_mean(const coord_arrays_t *const coord_arrays, coord_t *each_coord_mean) {
  if (!coord_arrays || !each_coord_mean) {
    return EXIT_FAILURE;
  }

  for (size_t coord_idx = 0; coord_idx < coord_arrays->dim; ++coord_idx) {
    if (compute_mean_by_coordinate(coord_arrays->data[coord_idx],
                                   coord_arrays->size,
                                   &each_coord_mean->data[coord_idx])) {
      fprintf(stderr, "%s\n", UNKNOWN_ERROR_MSG);

      return EXIT_FAILURE;
    }
  }

  return EXIT_SUCCESS;
}

static int compute_mean_by_coordinate(const double *const arr, size_t size, double *mean_value) {
  if (!arr || !mean_value) {
    return EXIT_FAILURE;
  }

  double sum = 0.0;
  for (size_t idx = 0; idx < size; ++idx) {
    sum += arr[idx];
  }

  *mean_value = sum / size;

  return EXIT_SUCCESS;
}
