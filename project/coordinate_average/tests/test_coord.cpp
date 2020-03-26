#include <gtest/gtest.h>

extern "C" {
  #include "coord.h"
}

TEST(coord, create_coord) {
  const size_t dim = 3;
  coord_t *coord = create_coord(dim);
  if (!coord) {
    FAIL();
    return;
  }

  free_coord(coord);
}

TEST(coord, create_coord_memory_error) {
  const size_t dim = SIZE_MAX;
  coord_t *coord = create_coord(dim);
  if (coord != NULL) {
    FAIL();
    return;
  }

  free_coord(coord);
}

int main(int argc, char *argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
