#include "coord.h"
#include "coord_arrays.h"
#include "coord_mean.h"
#include "coord_mean_parall.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <sys/sysctl.h>

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

  // {
  //   struct  timeval start;
  //   gettimeofday(&start, NULL);
  //   if (compute_each_coordinate_mean(coord_arrays, coord)) {
  //     free_coord_arrays(coord_arrays);
  //     free_coord(coord);
  //     return EXIT_FAILURE;
  //   }
  //   struct  timeval end;
  //   gettimeofday(&end, NULL);
  //   long time = (end.tv_sec - start.tv_sec) * 1000 + (end.tv_usec - start.tv_usec) / 1000;
  //   printf("coord:        {%2.8lf, %2.8lf, %2.8lf}, time: %ld\n",
  //    coord->data[0], coord->data[1], coord->data[2], time);
  // }

  coord_t *coord_parall = create_coord(coord_arrays->dim);
  if (!coord_parall) {
    free_coord_arrays(coord_arrays);
    free_coord(coord);
    return EXIT_FAILURE;
  }

  {
    struct  timeval start;
    gettimeofday(&start, NULL);
    if (compute_each_coordinate_mean_parall(coord_arrays, coord)) {
      free_coord_arrays(coord_arrays);
      free_coord(coord);
      return EXIT_FAILURE;
    }
    struct  timeval end;
    gettimeofday(&end, NULL);
    long time = (end.tv_sec - start.tv_sec) * 1000 + (end.tv_usec - start.tv_usec) / 1000;
    printf("coord:        {%2.8lf, %2.8lf, %2.8lf}, time: %ld\n",
     coord->data[0], coord->data[1], coord->data[2], time);
  }

  free_coord_arrays(coord_arrays);
  free_coord(coord);
  free_coord(coord_parall);

  return EXIT_SUCCESS;
}
