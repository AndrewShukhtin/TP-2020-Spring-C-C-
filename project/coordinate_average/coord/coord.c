#include "coord.h"

#include <stdlib.h>

coord_t *create_coord(size_t dim) {
  coord_t *coord = (coord_t *)calloc(1, sizeof(coord_t));
  if (!coord) {
    return NULL;
  }

  coord->data = (double *)calloc(dim, sizeof(double));
  if (!coord->data) {
    free(coord);
    return NULL;
  }

  coord->dim = dim;

  return coord;
}

void free_coord(coord_t *coord) {
  if (!coord) {
    return;
  }

  free(coord->data);
  free(coord);
}
