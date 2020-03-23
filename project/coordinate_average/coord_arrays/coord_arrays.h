#ifndef PROJECT_COORDINATE_AVERAGE_COORD_ARRAYS_COORD_ARRAYS_H_
#define PROJECT_COORDINATE_AVERAGE_COORD_ARRAYS_COORD_ARRAYS_H_

#include <stddef.h>
#include <stdio.h>

typedef struct coord_arrays_t {
  double **data;
  size_t dim;
  size_t size;
} coord_arrays_t;

coord_arrays_t *create_coord_arrays(size_t dim, size_t size);
coord_arrays_t *create_coord_arrays_from_file(FILE *file);
void free_coord_arrays(coord_arrays_t *coord_arrays);

#endif  // PROJECT_COORDINATE_AVERAGE_COORD_ARRAYS_COORD_ARRAYS_H_
