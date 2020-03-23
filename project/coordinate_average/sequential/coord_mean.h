#ifndef PROJECT_COORDINATE_AVERAGE_SEQUENTIAL_COORD_MEAN_H_
#define PROJECT_COORDINATE_AVERAGE_SEQUENTIAL_COORD_MEAN_H_

#include <stddef.h>

typedef struct coord_t coord_t;
typedef struct coord_arrays_t coord_arrays_t;

int compute_each_coordinate_mean(const coord_arrays_t *const coord_arrays, coord_t *each_coord_mean);

#endif  // PROJECT_COORDINATE_AVERAGE_SEQUENTIAL_COORD_MEAN_H_
