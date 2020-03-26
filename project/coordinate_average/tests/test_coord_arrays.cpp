#include <gtest/gtest.h>
#include <limits.h>

extern "C" {
  #include "coord_arrays.h"
}

#define TEST_1 "test_data/test_mean.txt"
#define TEST_INVALID_DIM "test_data/test_invalid_dim.txt"
#define TEST_INVALID_SIZE "test_data/test_invalid_size.txt"
#define TEST_INVALID_DATA "test_data/test_invalid_data.txt"

TEST(coord_arrays, create_coord_arrays) {
  const size_t dim = 3;
  const size_t size = 24;
  coord_arrays_t *coord_arrays = create_coord_arrays(dim, size);
  if (!coord_arrays) {
    FAIL();
    return;
  }

  free_coord_arrays(coord_arrays);
}

TEST(coord_arrays, create_coord_arrays_invalid_dim) {
  const size_t dim = SIZE_MAX; 
  const size_t size = 24;
  coord_arrays_t *coord_arrays = create_coord_arrays(dim, size);
  if (coord_arrays != NULL) {
    FAIL();
    return;
  }
}

TEST(coord_arrays, create_coord_arrays_invalid_size) {
  const size_t dim = 3;
  const size_t size = SIZE_MAX;
  coord_arrays_t *coord_arrays = create_coord_arrays(dim, size);
  if (coord_arrays != NULL) {
    FAIL();
    return;
  }
}

TEST(coord_arrays, create_coord_arrays_from_file) {
  FILE *file = fopen(TEST_1, "r");
  if (!file) {
    FAIL();
    return;
  }

  coord_arrays_t *coord_arrays = create_coord_arrays_from_file(file);
  if (!coord_arrays) {
    FAIL();
    fclose(file);
    return;
  }

  free_coord_arrays(coord_arrays);
  fclose(file);
}

TEST(coord_arrays, create_coord_arrays_from_file_invalid_dim) {
  FILE *file = fopen(TEST_INVALID_DIM, "r");
  if (!file) {
    FAIL();
    return;
  }

  coord_arrays_t *coord_arrays = create_coord_arrays_from_file(file);
  if (coord_arrays != NULL) {
    FAIL();
    fclose(file);
    return;
  }

  fclose(file);
}

TEST(coord_arrays, create_coord_arrays_from_file_invalid_size) {
  FILE *file = fopen(TEST_INVALID_SIZE, "r");
  if (!file) {
    FAIL();
    return;
  }

  coord_arrays_t *coord_arrays = create_coord_arrays_from_file(file);
  if (coord_arrays != NULL) {
    FAIL();
    fclose(file);
    return;
  }

  fclose(file);
}

TEST(coord_arrays, create_coord_arrays_from_file_invalid_data) {
  FILE *file = fopen(TEST_INVALID_DATA, "r");
  if (!file) {
    FAIL();
    return;
  }

  coord_arrays_t *coord_arrays = create_coord_arrays_from_file(file);
  if (coord_arrays != NULL) {
    FAIL();
    fclose(file);
    return;
  }

  fclose(file);
}

int main(int argc, char *argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
