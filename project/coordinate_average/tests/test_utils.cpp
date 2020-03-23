#include <gtest/gtest.h>
#include <dlfcn.h>

extern "C" {
  #include "utils.h"
}

TEST(utilities, set_pthread_mean_value_args_invalid_args) {
  if (!set_pthread_mean_value_args(NULL, NULL, 0)) {
    FAIL();
  }
}

TEST(utilities, get_number_of_core_threads_invalid_args) {
  if (!get_number_of_core_threads(NULL)) {
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
