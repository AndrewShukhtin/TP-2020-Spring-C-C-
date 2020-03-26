#include <gtest/gtest.h>

extern "C" {
  #include "coord.h"
  #include "coord_arrays.h"
  #include "coord_mean.h"
}

#define TEST_MEAN "test_data/test_mean.txt"

TEST(coord_mean, compute_each_coordinate_mean) {
  FILE *file = fopen(TEST_MEAN, "r");
  if (!file) {
    FAIL();
    return;
  }

  coord_arrays_t *coord_arrays = create_coord_arrays_from_file(file);
  if (!coord_arrays) {
    fclose(file);
    FAIL();
    return;
  }
  fclose(file);

  coord_t *coord = create_coord(coord_arrays->dim);
  if (!coord) {
    free_coord_arrays(coord_arrays);
    FAIL();
    return;
  }

  if (compute_each_coordinate_mean(coord_arrays, coord)) {
    free_coord_arrays(coord_arrays);
    free_coord(coord);
    FAIL();
    return;
  }
  free_coord_arrays(coord_arrays);

  coord_t *exp_coord = create_coord(coord_arrays->dim);
  if (!exp_coord) {
    free_coord(coord);
    FAIL();
    return;
  }

  exp_coord->data[0] = 4.1191839599609956;
  exp_coord->data[1] = 4.1231742630005295;
  exp_coord->data[2] = 4.1112425994873361;

  for (size_t coord_idx = 0; coord_idx < exp_coord->dim; ++coord_idx) {
    EXPECT_FLOAT_EQ(exp_coord->data[coord_idx], coord->data[coord_idx]);
  }

  free_coord(coord);
  free_coord(exp_coord);
}

TEST(coord_mean, compute_each_coordinate_mean_invalid_args) {
  if (!compute_each_coordinate_mean(NULL, NULL)) {
    FAIL();
    return;
  }
}

TEST(coord_mean, compute_mean_by_coordinate_invalid_args) {
  const size_t dim = 3;
  const size_t size = 24;
  coord_arrays_t *coord_arrays = create_coord_arrays(dim, size);
  if (!coord_arrays) {
    FAIL();
    return;
  }

  coord_t *coord = create_coord(coord_arrays->dim);
  if (!coord) {
    free_coord_arrays(coord_arrays);
    FAIL();
    return;
  }

  free(coord_arrays->data[0]);
  coord_arrays->data[0] = NULL;

  if (!compute_each_coordinate_mean(coord_arrays, coord)) {
    free_coord_arrays(coord_arrays);
    free_coord(coord);
    FAIL();
    return;
  }

  free_coord_arrays(coord_arrays);
  free_coord(coord);
}

int main(int argc, char *argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
