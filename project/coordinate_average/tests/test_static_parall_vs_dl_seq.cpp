#include <gtest/gtest.h>
#include <dlfcn.h>

extern "C" {
  #include "coord.h"
  #include "coord_arrays.h"
  #include "coord_mean.h"
  #include "coord_mean_parall.h"
}

#define DL_PATH "./build/lib_coord_mean_dl.so"
#define TEST_1  "test_data/test1.txt"         // dim = 3, size = 24        | 448B
#define TEST_2  "test_data/test2.txt"         // dim = 3, size = 262144    | 4.9M

// NOTE(vendroid): Too large test for sequential algortithm
// #define TEST_3  "test_data/test3.txt"         // dim = 3, size = 1048576  | 19M

typedef coord_t *(*dl_create_coord_t)(size_t);
typedef void (*dl_free_coord_t)(coord_t *);
typedef coord_arrays_t *(*dl_create_coord_arrays_from_file_t)(FILE *);
typedef void (*dl_free_coord_arrays_t)(coord_arrays_t *);
typedef int (*dl_compute_each_coordinate_mean_t)(const coord_arrays_t *const, coord_t *);

TEST(static_parall_vs_dl_seq, compare_each_coordinate_mean_test1) {
  void *dl_handle = dlopen(DL_PATH, RTLD_LAZY);
  if (!dl_handle) {
    fprintf(stderr, "%s\n", dlerror());
    FAIL();
  }

  char *error_msg = NULL;
  auto dl_create_coord = (dl_create_coord_t)dlsym(dl_handle, "create_coord");
  if ((error_msg = dlerror()) != NULL) {
    fprintf(stderr, "%s\n", error_msg);
    dlclose(dl_handle);
    FAIL();
    return;
  }

  auto dl_free_coord = (dl_free_coord_t)dlsym(dl_handle, "free_coord");
  if ((error_msg = dlerror()) != NULL) {
    fprintf(stderr, "%s\n", error_msg);
    dlclose(dl_handle);
    FAIL();
    return;
  }

  auto dl_create_coord_arrays_from_file
     = (dl_create_coord_arrays_from_file_t)dlsym(dl_handle, "create_coord_arrays_from_file");
  if ((error_msg = dlerror()) != NULL) {
    fprintf(stderr, "%s\n", error_msg);
    dlclose(dl_handle);
    FAIL();
    return;
  }

  auto dl_free_coord_arrays = (dl_free_coord_arrays_t)dlsym(dl_handle, "free_coord_arrays");
  if ((error_msg = dlerror()) != NULL) {
    fprintf(stderr, "%s\n", error_msg);
    dlclose(dl_handle);
    FAIL();
    return;
  }

  auto dl_compute_each_coordinate_mean
     = (dl_compute_each_coordinate_mean_t)dlsym(dl_handle, "compute_each_coordinate_mean");
  if ((error_msg = dlerror()) != NULL) {
    fprintf(stderr, "%s\n", error_msg);
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

  if (compute_each_coordinate_mean_parall(coord_arrays_st, each_coord_mean_st)) {
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

TEST(static_parall_vs_dl_seq, compare_each_coordinate_mean_test2) {
  void *dl_handle = dlopen(DL_PATH, RTLD_LAZY);
  if (!dl_handle) {
    fprintf(stderr, "%s\n", dlerror());
    FAIL();
  }

  char *error_msg = NULL;
  auto dl_create_coord = (dl_create_coord_t)dlsym(dl_handle, "create_coord");
  if ((error_msg = dlerror()) != NULL) {
    fprintf(stderr, "%s\n", error_msg);
    dlclose(dl_handle);
    FAIL();
    return;
  }

  auto dl_free_coord = (dl_free_coord_t)dlsym(dl_handle, "free_coord");
  if ((error_msg = dlerror()) != NULL) {
    fprintf(stderr, "%s\n", error_msg);
    dlclose(dl_handle);
    FAIL();
    return;
  }

  auto dl_create_coord_arrays_from_file
     = (dl_create_coord_arrays_from_file_t)dlsym(dl_handle, "create_coord_arrays_from_file");
  if ((error_msg = dlerror()) != NULL) {
    fprintf(stderr, "%s\n", error_msg);
    dlclose(dl_handle);
    FAIL();
    return;
  }

  auto dl_free_coord_arrays = (dl_free_coord_arrays_t)dlsym(dl_handle, "free_coord_arrays");
  if ((error_msg = dlerror()) != NULL) {
    fprintf(stderr, "%s\n", error_msg);
    dlclose(dl_handle);
    FAIL();
    return;
  }

  auto dl_compute_each_coordinate_mean
     = (dl_compute_each_coordinate_mean_t)dlsym(dl_handle, "compute_each_coordinate_mean");
  if ((error_msg = dlerror()) != NULL) {
    fprintf(stderr, "%s\n", error_msg);
    dlclose(dl_handle);
    FAIL();
    return;
  }

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

  if (compute_each_coordinate_mean_parall(coord_arrays_st, each_coord_mean_st)) {
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
