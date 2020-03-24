#include "utils.h"

#include <stdlib.h>
#include <stdio.h>

#if defined(__linux__)
#include <sys/sysinfo.h>
#include <unistd.h>
#elif defined(__APPLE__)
#include <sys/sysctl.h>
#endif

#define SC_ERROR -1

int set_pthread_mean_value_args(pthread_mean_value_args_t *pthread_mean_value_args,
                                              const double *const arr, size_t size) {
  if (!pthread_mean_value_args || !arr) {
    return EXIT_FAILURE;
  }

  pthread_mean_value_args->arr = arr;
  pthread_mean_value_args->sum = 0.0;

  size_t number_of_logical_cpu = 0;
  if (get_number_of_logical_cpu(&number_of_logical_cpu)) {
    return EXIT_FAILURE;
  }

  pthread_mean_value_args->number_of_threads = number_of_logical_cpu;
  pthread_mean_value_args->offset = ceil_by_div(size, number_of_logical_cpu);
  pthread_mean_value_args->size = size;

  return EXIT_SUCCESS;
}

int get_number_of_logical_cpu(size_t *number_of_logical_cpu) {
  if (!number_of_logical_cpu) {
    return EXIT_FAILURE;
  }

  long res = 0l;
#if defined(__linux__)
  res = sysconf(_SC_NPROCESSORS_ONLN);
  if (res == SC_ERROR) {
    return EXIT_FAILURE;
  }
#elif defined(__APPLE__)
  int mib[2] = {CTL_HW, HW_NCPU};
  size_t len = sizeof(res);
  sysctl(mib, 2, &res, &len, NULL, 0);
#endif

  *number_of_logical_cpu = (size_t)res;

  return EXIT_SUCCESS;
}

int get_number_of_physical_cpu(size_t *number_of_physical_cpu) {
  if (!number_of_physical_cpu) {
    return EXIT_FAILURE;
  }

  int res = 0l;
#if defined(__linux__)
  res = get_nprocs_conf();
#elif defined(__APPLE__)
  const char hw_comand_name[] = "hw.physicalcpu_max";
  size_t len = sizeof(res);
  if (sysctlbyname(hw_comand_name, &res, &len, NULL, 0)) {
    return EXIT_FAILURE;
  }
#endif

  *number_of_physical_cpu = (size_t)res;

  return EXIT_SUCCESS;
}

int get_l1cache_line_size(size_t *l1cache_line_size) {
  if (!l1cache_line_size) {
    return EXIT_FAILURE;
  }

  long res = 0l;
#if defined(__linux__)
  res = sysconf(_SC_LEVEL1_DCACHE_LINESIZE);
  if (res == SC_ERROR) {
    res = sizeof(void *);
  }
#elif defined(__APPLE__)
  const char hw_comand_name[] = "hw.cachelinesize";
  size_t len = sizeof(res);
  if (sysctlbyname(hw_comand_name, &res, &len, NULL, 0)) {
    res = sizeof(void *);
  }
#endif

  *l1cache_line_size = (size_t)res;

  return EXIT_SUCCESS;
}

int get_l1dcache_size(size_t *l1dcache_size) {
  if (!l1dcache_size) {
    return EXIT_FAILURE;
  }

  long res = 0l;
#if defined(__linux__)
  res = sysconf(_SC_LEVEL1_DCACHE_SIZE);
  if (res == SC_ERROR) {
    return EXIT_FAILURE;
  }
#elif defined(__APPLE__)
  const char hw_comand_name[] = "hw.l1dcachesize";
  size_t len = sizeof(res);
  if (sysctlbyname(hw_comand_name, &res, &len, NULL, 0)) {
    return EXIT_FAILURE;
  }
#endif

  *l1dcache_size = (size_t)res;

  return EXIT_SUCCESS;
}

size_t ceil_by_div(size_t value, size_t div) {
  size_t modulo = value % div;
  if (!modulo) {
    return value / div;
  }

  return value / div + 1;
}

size_t min(size_t lhs, size_t rhs) {
  return lhs < rhs? lhs : rhs;
}
