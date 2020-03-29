#include <gtest/gtest.h>
#include <dlfcn.h>

extern "C" {
  #include "utils.h"
}

TEST(utilities, set_pthread_mean_value_args) {
  pthread_mean_value_args_t pthread_mean_value_args{};
  const size_t size = 5;
  double *arr = (double *)calloc(size, sizeof(double));
  if (set_pthread_mean_value_args(&pthread_mean_value_args, arr, size)) {
    FAIL();
  }

  free(arr);
}

TEST(utilities, set_pthread_mean_value_args_invalid_args) {
  if (!set_pthread_mean_value_args(NULL, NULL, 0)) {
    FAIL();
  }
}

TEST(utilities, get_number_of_logical_cpu) {
  size_t number_of_logical_cpu = 0;
  if (get_number_of_logical_cpu(&number_of_logical_cpu) || number_of_logical_cpu == 0) {
    FAIL();
  }
}

TEST(utilities, get_number_of_logical_cpu_invalid_args) {
  if (!get_number_of_logical_cpu(NULL)) {
    FAIL();
  }
}

TEST(utilities, get_number_of_physical_cpu) {
  size_t number_of_physical_cpu = 0;
  if (get_number_of_physical_cpu(&number_of_physical_cpu) || number_of_physical_cpu == 0) {
    FAIL();
  }
}

TEST(utilities, get_number_of_physical_cpu_invalid_args) {
  if (!get_number_of_physical_cpu(NULL)) {
    FAIL();
  }
}

TEST(utilities, get_l1cache_line_size) {
  size_t l1cache_line_size = 0;
  if (get_l1cache_line_size(&l1cache_line_size) || l1cache_line_size == 0) {
    FAIL();
  }
}

TEST(utilities, get_l1cache_line_size_invalid_args) {
  if (!get_l1cache_line_size(NULL)) {
    FAIL();
  }
}

TEST(utilities, get_l1dcache_size) {
  size_t l1dcache_size = 0;
  if (get_l1dcache_size(&l1dcache_size) || l1dcache_size == 0) {
    FAIL();
  }
}

TEST(utilities, get_l1dcache_size_invalid_args) {
  if (!get_l1cache_line_size(NULL)) {
    FAIL();
  }
}

TEST(utilities, ceil_by_div) {
  const size_t value = 10;
  const size_t div = 3;
  const size_t ceil = 4;
  if (ceil != ceil_by_div(value, div)) {
    FAIL();
  }
}

TEST(utilities, minimun) {
  const size_t min_value = 3;
  const size_t max_value = 10;
  if (min_value != min(min_value, max_value)) {
    FAIL();
  }
}

int main(int argc, char *argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
