#include "utils.h"

#include <stdlib.h>
#include <unistd.h>

#define SC_ERROR -1

static size_t ceil_by_div(size_t value, size_t div);

int set_pthread_mean_value_args(pthread_mean_value_args_t *pthread_mean_value_args,
                                              const double *const arr, size_t size) {
  if (!pthread_mean_value_args || !arr) {
    return EXIT_FAILURE;
  }

  pthread_mean_value_args->arr = arr;
  pthread_mean_value_args->sum = 0.0;

  size_t number_of_logical_cpu = 0;
  if (get_number_of_core_threads(&number_of_logical_cpu)) {
    return EXIT_FAILURE;
  }

  pthread_mean_value_args->number_of_threads = number_of_logical_cpu;
  pthread_mean_value_args->offset = ceil_by_div(size, number_of_logical_cpu);
  pthread_mean_value_args->size = size;

  return EXIT_SUCCESS;
}

int get_number_of_core_threads(size_t *number_of_threads) {
  if (!number_of_threads) {
    return EXIT_FAILURE;
  }

  long number_of_logical_cpu = sysconf(_SC_NPROCESSORS_ONLN);
  if (number_of_logical_cpu == SC_ERROR) {
    return EXIT_FAILURE;
  }

  *number_of_threads = (size_t)number_of_logical_cpu;

  return EXIT_SUCCESS;
}

size_t min(size_t lhs, size_t rhs) {
  return lhs < rhs? lhs : rhs;
}

static size_t ceil_by_div(size_t value, size_t div) {
  size_t modulo = value % div;
  if (!modulo) {
    return value / div;
  }

  return value / div + 1;
}
