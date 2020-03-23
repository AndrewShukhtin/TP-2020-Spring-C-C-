#include "coord.h"
#include "coord_arrays.h"
#include "coord_mean.h"
#include "coord_mean_parall.h"

#include <stdio.h>
#include <stdlib.h>

int main(void) {
  coord_arrays_t *coord_arrays = create_coord_arrays_from_file(stdin);
  if (!coord_arrays) {
    return EXIT_FAILURE;
  }

  coord_t *coord = create_coord(coord_arrays->dim);
  if (!coord) {
    free_coord_arrays(coord_arrays);
    return EXIT_FAILURE;
  }

  if (compute_each_coordinate_mean(coord_arrays, coord)) {
    free_coord_arrays(coord_arrays);
    free_coord(coord);
    return EXIT_FAILURE;
  }
  printf("coord:        {%2.16lf, %2.16lf, %2.16lf}\n", coord->data[0], coord->data[1], coord->data[2]);

  coord_t *coord_parall = create_coord(coord_arrays->dim);
  if (!coord_parall) {
    free_coord_arrays(coord_arrays);
    free_coord(coord);
    return EXIT_FAILURE;
  }

  if (compute_each_coordinate_mean_parall(coord_arrays, coord_parall)) {
    free_coord_arrays(coord_arrays);
    free_coord(coord);
    free_coord(coord_parall);
    return EXIT_FAILURE;
  }
  printf("coord_parall: {%2.16lf, %2.16lf, %2.16f}\n", coord_parall->data[0], coord_parall->data[1], coord_parall->data[2]);

  free_coord_arrays(coord_arrays);
  free_coord(coord);
  free_coord(coord_parall);

  return EXIT_SUCCESS;
}
