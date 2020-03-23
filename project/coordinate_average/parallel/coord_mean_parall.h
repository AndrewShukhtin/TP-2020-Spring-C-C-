#ifndef PROJECT_COORDINATE_AVERAGE_PARALLEL_COORD_MEAN_PARALL_H_
#define PROJECT_COORDINATE_AVERAGE_PARALLEL_COORD_MEAN_PARALL_H_

#include <stddef.h>

typedef struct coord_t coord_t;
typedef struct coord_arrays_t coord_arrays_t;

int compute_each_coordinate_mean_parall(const coord_arrays_t *const coord_arrays, coord_t *each_coord_mean);

#endif  // PROJECT_COORDINATE_AVERAGE_PARALLEL_COORD_MEAN_PARALL_H_
