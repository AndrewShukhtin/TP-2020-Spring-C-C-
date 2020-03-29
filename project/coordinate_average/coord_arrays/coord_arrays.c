#include "coord_arrays.h"

#include <stdlib.h>

#define SCANF_ONE_CHAR_SUCCESS 1

coord_arrays_t *create_coord_arrays(size_t dim, size_t size) {
  coord_arrays_t *coord_arrays = (coord_arrays_t *)calloc(1, sizeof(coord_arrays_t));
  if (!coord_arrays) {
    return  NULL;
  }

  coord_arrays->data = (double **)calloc(dim, sizeof(double *));
  if (!coord_arrays->data) {
    free(coord_arrays);
    return NULL;
  }

  for (size_t coord_idx = 0; coord_idx < dim; ++coord_idx) {
    coord_arrays->data[coord_idx] = (double *)malloc(size * sizeof(double));

    if (!coord_arrays->data[coord_idx]) {
      free_coord_arrays(coord_arrays);
      return NULL;
    }
  }

  coord_arrays->dim = dim;
  coord_arrays->size = size;

  return coord_arrays;
}

coord_arrays_t *create_coord_arrays_from_file(FILE *file) {
  size_t dim = 0;
  if (fscanf(file, "%zu", &dim) != SCANF_ONE_CHAR_SUCCESS) {
    return NULL;
  }

  size_t size = 0;
  if (fscanf(file, "%zu", &size) != SCANF_ONE_CHAR_SUCCESS) {
    return NULL;
  }

  coord_arrays_t *coord_arrays = create_coord_arrays(dim, size);
  if (!coord_arrays) {
    return NULL;
  }

  for (size_t coord_idx = 0; coord_idx < dim; ++coord_idx) {
    for (size_t idx = 0; idx < size; ++idx) {
      if (fscanf(file, "%lf", &coord_arrays->data[coord_idx][idx]) != SCANF_ONE_CHAR_SUCCESS) {
        free_coord_arrays(coord_arrays);
        return NULL;
      }
    }
  }

  return coord_arrays;
}

void free_coord_arrays(coord_arrays_t *coord_arrays) {
  if (!coord_arrays) {
    return;
  }

  for (size_t coord_idx = 0; coord_idx < coord_arrays->dim; ++coord_idx) {
    free(coord_arrays->data[coord_idx]);
    coord_arrays->data[coord_idx] = NULL;
  }

  free(coord_arrays->data);
  free(coord_arrays);
}
