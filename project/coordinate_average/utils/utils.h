#ifndef PROJECT_COORDINATE_AVERAGE_UTILS_UTILS_H_
#define PROJECT_COORDINATE_AVERAGE_UTILS_UTILS_H_

#include <stddef.h>

typedef struct pthread_mean_value_args_t {
  const double *arr;
  double sum;
  size_t number_of_threads;
  size_t offset;
  size_t size;
} pthread_mean_value_args_t;

int set_pthread_mean_value_args(pthread_mean_value_args_t *pthread_mean_value_args,
                                                const double *const arr, size_t size);
int get_number_of_core_threads(size_t *number_of_threads);
size_t min(size_t lhs, size_t rhs);

#endif  // PROJECT_COORDINATE_AVERAGE_UTILS_UTILS_H_
