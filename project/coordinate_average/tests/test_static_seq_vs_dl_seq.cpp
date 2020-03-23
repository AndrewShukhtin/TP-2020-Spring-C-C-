#include <gtest/gtest.h>
#include <dlfcn.h>

extern "C" {
  #include "coord.h"
  #include "coord_arrays.h"
  #include "coord_mean.h"
}

#define DL_PATH "./build/lib_coord_mean_dl.so"
#define TEST_1  "test_data/test1.txt"         // dim = 3, size = 24        | 448B
#define TEST_2  "test_data/test2.txt"         // dim = 3, size = 8388608   | 148M

// NOTE(vendroid): Too large test for sequential algortithm
// #define TEST_3  "test_data/test3.txt"         // dim = 3, size = 33554432  | 593M

TEST(static_seq_vs_dl_seq, create_coords) {
  void *dl_handle = dlopen(DL_PATH, RTLD_LAZY);
  if (!dl_handle) {
    fprintf(stderr, "%s\n", dlerror());
    FAIL();
    return;
  }

  coord_t *(*dl_create_coord)(size_t) = NULL;
  dl_create_coord = (coord_t *(*)(size_t))dlsym(dl_handle, "create_coord");
  if (!dl_create_coord) {
    dlclose(dl_handle);
    FAIL();
    return;
  }

  void (*dl_free_coord)(coord_t *) = NULL;
  dl_free_coord = (void (*)(coord_t *))dlsym(dl_handle, "free_coord");
  if (!dl_free_coord) {
    dlclose(dl_handle);
    FAIL();
    return;
  }

  const size_t dim = 3;
  coord_t *coord_st = create_coord(dim);
  if (!coord_st) {
    FAIL();
    return;
  }

  coord_t *coord_dl = (*dl_create_coord)(dim);
  if (!coord_dl) {
    free_coord(coord_st);
    dlclose(dl_handle);
    FAIL();
    return;
  }

  EXPECT_EQ(coord_st->dim, coord_dl->dim);
  for (size_t coord_idx = 0; coord_idx < coord_st->dim; ++coord_idx) {
    EXPECT_FLOAT_EQ(coord_st->data[coord_idx], coord_dl->data[coord_idx]);
  }

  free_coord(coord_st);
  (*dl_free_coord)(coord_dl);
  dlclose(dl_handle);
}

TEST(static_seq_vs_dl_seq, create_coord_array_from_file) {
  void *dl_handle = dlopen(DL_PATH, RTLD_LAZY);
  if (!dl_handle) {
    fprintf(stderr, "%s\n", dlerror());
    FAIL();
    return;
  }

  coord_arrays_t *(*dl_create_coord_arrays_from_file)(FILE *) = NULL;
  dl_create_coord_arrays_from_file = (coord_arrays_t *( *)(FILE *))dlsym(dl_handle, "create_coord_arrays_from_file");
  if (!dlerror()) {
    fprintf(stderr, "%s\n", dlerror());
    dlclose(dl_handle);
    FAIL();
    return;
  }

  void (*dl_free_coord_arrays)(coord_arrays_t *) = NULL;
  dl_free_coord_arrays = (void (*)(coord_arrays_t *))dlsym(dl_handle, "free_coord_arrays");
  if (!dlerror()) {
    fprintf(stderr, "%s\n", dlerror());
    dlclose(dl_handle);
    FAIL();
    return;
  }

  FILE *file = fopen(TEST_1, "r");
  if (!file) {
    dlclose(dl_handle);
    FAIL();
    return;
  }

  coord_arrays_t *coord_arrays_st = create_coord_arrays_from_file(file);
  if (!coord_arrays_st) {
    fclose(file);
    FAIL();
    return;
  }

  rewind(file);
  coord_arrays_t *coord_arrays_dl = (*dl_create_coord_arrays_from_file)(file);
  if (!coord_arrays_dl) {
    fclose(file);
    free_coord_arrays(coord_arrays_st);
    dlclose(dl_handle);
    FAIL();
    return;
  }
  fclose(file);

  EXPECT_EQ(coord_arrays_st->dim, coord_arrays_dl->dim);
  EXPECT_EQ(coord_arrays_st->size, coord_arrays_dl->size);

  for (size_t coord_idx = 0; coord_idx < coord_arrays_st->dim; ++coord_idx) {
    for (size_t idx = 0; idx < coord_arrays_st->size; ++idx) {
      EXPECT_DOUBLE_EQ(coord_arrays_st->data[coord_idx][idx], coord_arrays_dl->data[coord_idx][idx]);
    }
  }

  free_coord_arrays(coord_arrays_st);
  (*dl_free_coord_arrays)(coord_arrays_dl);
  dlclose(dl_handle);
}

TEST(static_seq_vs_dl_seq, compare_compute_each_coordinate_mean) {
  void *dl_handle = dlopen(DL_PATH, RTLD_LAZY);
  if (!dl_handle) {
    fprintf(stderr, "%s\n", dlerror());
    FAIL();
    return;
  }

  coord_t *(*dl_create_coord)(size_t) = NULL;
  dl_create_coord = (coord_t *(*)(size_t))dlsym(dl_handle, "create_coord");
  if (!dl_create_coord) {
    fprintf(stderr, "%s\n", dlerror());
    dlclose(dl_handle);
    FAIL();
    return;
  }

  void (*dl_free_coord)(coord_t *) = NULL;
  dl_free_coord = (void (*)(coord_t *))dlsym(dl_handle, "free_coord");
  if (!dl_free_coord) {
    fprintf(stderr, "%s\n", dlerror());
    dlclose(dl_handle);
    FAIL();
    return;
  }

  coord_arrays_t *(*dl_create_coord_arrays_from_file)(FILE *) = NULL;
  dl_create_coord_arrays_from_file = (coord_arrays_t *(*)(FILE *))dlsym(dl_handle, "create_coord_arrays_from_file");
  if (!dl_create_coord_arrays_from_file) {
    fprintf(stderr, "%s\n", dlerror());
    dlclose(dl_handle);
    FAIL();
    return;
  }

  void (*dl_free_coord_arrays)(coord_arrays_t *) = NULL;
  dl_free_coord_arrays = (void (*)(coord_arrays_t *))dlsym(dl_handle, "free_coord_arrays");
  if (!dl_free_coord_arrays) {
    fprintf(stderr, "%s\n", dlerror());
    dlclose(dl_handle);
    FAIL();
    return;
  }

  int (*dl_compute_each_coordinate_mean)(const coord_arrays_t *const, coord_t *) = NULL;
  dl_compute_each_coordinate_mean
     = (int (*)(const coord_arrays_t *const, coord_t *))dlsym(dl_handle, "compute_each_coordinate_mean");

  FILE *file = fopen(TEST_2, "r");
  if (!file) {
    dlclose(dl_handle);
    FAIL();
    return;
  }

  coord_arrays_t *coord_arrays_st = create_coord_arrays_from_file(file);
  if (!coord_arrays_st) {
    fclose(file);
    dlclose(dl_handle);
    FAIL();
    return;
  }

  coord_t *each_coord_mean_st = create_coord(coord_arrays_st->dim);
  if (!each_coord_mean_st) {
    fclose(file);
    free_coord_arrays(coord_arrays_st);
    dlclose(dl_handle);
    FAIL();
    return;
  }

  if (compute_each_coordinate_mean(coord_arrays_st, each_coord_mean_st)) {
    fclose(file);
    free_coord_arrays(coord_arrays_st);
    free_coord(each_coord_mean_st);
    dlclose(dl_handle);
    FAIL();
    return;
  }
  free_coord_arrays(coord_arrays_st);

  rewind(file);
  coord_arrays_t *coord_arrays_dl = (*dl_create_coord_arrays_from_file)(file);
  if (!coord_arrays_dl) {
    fclose(file);
    free_coord(each_coord_mean_st);
    dlclose(dl_handle);
    FAIL();
    return;
  }
  fclose(file);

  coord_t *each_coord_mean_dl = (*dl_create_coord)(coord_arrays_dl->dim);
  if (!each_coord_mean_dl) {
    free_coord(each_coord_mean_st);
    (*dl_free_coord_arrays)(coord_arrays_dl);
    dlclose(dl_handle);
    FAIL();
    return;
  }

  if ((*dl_compute_each_coordinate_mean)(coord_arrays_dl, each_coord_mean_dl)) {
    free_coord(each_coord_mean_st);
    (*dl_free_coord_arrays)(coord_arrays_dl);
    (*dl_free_coord)(each_coord_mean_dl);
    dlclose(dl_handle);
    FAIL();
    return;
  }
  (*dl_free_coord_arrays)(coord_arrays_dl);

  EXPECT_EQ(each_coord_mean_st->dim, each_coord_mean_dl->dim);
  for (size_t coord_idx = 0; coord_idx < each_coord_mean_st->dim; ++coord_idx) {
    EXPECT_FLOAT_EQ(each_coord_mean_st->data[coord_idx], each_coord_mean_dl->data[coord_idx]);
  }

  free_coord(each_coord_mean_st);
  (*dl_free_coord)(each_coord_mean_dl);
  dlclose(dl_handle);
}

int main(int argc, char *argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
