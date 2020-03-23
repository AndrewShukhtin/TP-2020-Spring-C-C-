#ifndef PROJECT_COORDINATE_AVERAGE_COORD_COORD_H_
#define PROJECT_COORDINATE_AVERAGE_COORD_COORD_H_

#include <stddef.h>

typedef struct coord_t {
  double *data;
  size_t dim;
} coord_t;

coord_t *create_coord(size_t dim);
void free_coord(coord_t *coord);

#endif  // PROJECT_COORDINATE_AVERAGE_COORD_COORD_H_
