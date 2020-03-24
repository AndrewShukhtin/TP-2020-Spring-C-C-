#include "coord.h"
#include "coord_arrays.h"
#include "coord_mean.h"
#include "coord_mean_parall.h"
#include "utils.h"

#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#define UNKNOWN_ERROR_MSG "Unknown error occured while computing mean"

static int compute_mean_by_coordinate_parall(const double *const arr, size_t size, double *mean_value);
static void *pthread_mean_value(void *args);
static int malloc_aligned_l1dcache(void **ptr, size_t size);
static int get_l1dsize_per_thread(size_t *l1dsize_per_thread);

pthread_mean_value_args_t mean_value_args = {.arr               =  NULL,
                                             .sum               =  0.0,
                                             .number_of_threads =  0,
                                             .offset            =  0,
                                             .size              =  0};

pthread_mutex_t mutex_sum = PTHREAD_MUTEX_INITIALIZER;

int compute_each_coordinate_mean_parall(const coord_arrays_t *const coord_arrays, coord_t *each_coord_mean) {
  if (!coord_arrays || !each_coord_mean) {
    return EXIT_FAILURE;
  }

  size_t l1dcache_size = 0;
  if (get_l1dcache_size(&l1dcache_size)) {
    return EXIT_FAILURE;
  }

  if (l1dcache_size > coord_arrays->size) {
    return compute_each_coordinate_mean(coord_arrays, each_coord_mean);
  }

  for (size_t coord_idx = 0; coord_idx < coord_arrays->dim; ++coord_idx) {
    if (compute_mean_by_coordinate_parall(coord_arrays->data[coord_idx],
                                        coord_arrays->size,
                                        &each_coord_mean->data[coord_idx])) {
      fprintf(stderr, "%s\n", UNKNOWN_ERROR_MSG);

      return EXIT_FAILURE;
    }
  }

  return EXIT_SUCCESS;
}

static int compute_mean_by_coordinate_parall(const double *const arr, size_t size, double *mean_value) {
  if (!arr || !mean_value) {
    return EXIT_FAILURE;
  }

  if (set_pthread_mean_value_args(&mean_value_args, arr, size)) {
    return EXIT_FAILURE;
  }

  pthread_t *threads = calloc(mean_value_args.number_of_threads, sizeof(pthread_t));
  if (!threads) {
    return EXIT_FAILURE;
  }

  size_t *thread_ids = calloc(mean_value_args.number_of_threads, sizeof(size_t));
  if (!thread_ids) {
    free(threads);
    return EXIT_FAILURE;
  }

  for (size_t id = 0; id < mean_value_args.number_of_threads; ++id) {
    thread_ids[id] = id;

    if (pthread_create(&threads[id], NULL, pthread_mean_value, (void *)&thread_ids[id])) {
      free(thread_ids);
      free(threads);
      return EXIT_FAILURE;
    }
  }
  free(thread_ids);

  for (size_t id = 0; id < mean_value_args.number_of_threads; ++id) {
    if (pthread_join(threads[id], NULL)) {
      free(threads);
      return EXIT_FAILURE;
    }
  }

  *mean_value = mean_value_args.sum / size;
  free(threads);

  return EXIT_SUCCESS;
}

static void *pthread_mean_value(void *arg) {
  if (!arg) {
    pthread_exit(NULL);
  }

  size_t l1dsize_per_thread = 0;
  if (get_l1dsize_per_thread(&l1dsize_per_thread)) {
    pthread_exit(NULL);
  }

  double *cache = NULL;
  if (malloc_aligned_l1dcache((void **)&cache, l1dsize_per_thread)) {
    pthread_exit(NULL);
  }

  size_t id = *((size_t *)arg);
  const size_t begin_idx = mean_value_args.offset * id;
  const size_t end_idx = min(mean_value_args.offset * (id + 1), mean_value_args.size);
  size_t size = end_idx - begin_idx;

  size_t cache_size = l1dsize_per_thread / sizeof(double);
  size_t ceil_parts_cout = ceil_by_div(size, cache_size);

  double sum = 0.0;
  for (size_t idx = 0; idx < ceil_parts_cout; ++idx) {
    size_t cache_begin = begin_idx + idx * cache_size;
    size_t cache_end = min(begin_idx + (idx + 1) * cache_size, end_idx);
    
    memcpy(cache, mean_value_args.arr + cache_begin, (cache_end - cache_begin) * sizeof(double));

    for (size_t cache_idx = 0; cache_idx < cache_end - cache_begin; ++cache_idx) {
      sum += cache[cache_idx];
    }
  }

  pthread_mutex_lock(&mutex_sum);
  mean_value_args.sum += sum;
  pthread_mutex_unlock(&mutex_sum);

  free(cache);
  pthread_exit(NULL);
  return NULL;
}

static int malloc_aligned_l1dcache(void **ptr, size_t size) {
  if (!ptr || !size) {
    return EXIT_FAILURE;
  }

  size_t l1cache_line_size = 0;
  if (get_l1cache_line_size(&l1cache_line_size)) {
    return EXIT_FAILURE;
  }

  return posix_memalign(ptr, l1cache_line_size, size);
}

static int get_l1dsize_per_thread(size_t *l1dsize_per_thread) {
  if (!l1dsize_per_thread) {
    return EXIT_FAILURE;
  }

  size_t number_of_logical_cpu = 0;
  if (get_number_of_logical_cpu(&number_of_logical_cpu)) {
    return EXIT_FAILURE;
  }

  size_t number_of_physical_cpu = 0;
  if (get_number_of_physical_cpu(&number_of_physical_cpu)) {
    return EXIT_FAILURE;
  }

  size_t l1dcache_size = 0;
  if (get_l1dcache_size(&l1dcache_size)) {
    return EXIT_FAILURE;
  }

  *l1dsize_per_thread = l1dcache_size / (number_of_logical_cpu / number_of_physical_cpu);

  return EXIT_SUCCESS;
}
