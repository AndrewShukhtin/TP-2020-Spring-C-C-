#include <gtest/gtest.h>
#include <stdio.h>
#include <stdlib.h>

#define TESTS_DIR "input_tests/"

extern "C" {
  #include "parse_input.h"
}

TEST(ParseInput, leetCodeEx1) {
  FILE *input_file = freopen(TESTS_DIR "leet_code_ex1.txt", "r", stdin);
  if (!input_file) {
    FAIL();
  }

  size_t size = 0;
  if (read_size_from_input(&size)) {
    FAIL();
  }

  int *arr = NULL;
  if (read_array_from_input(&arr, size)) {
    FAIL();
  }

  size_t expected_size = 4;
  EXPECT_EQ(expected_size, size);

  int expected_arr[] = {3, 6, 9, 12};
  for (size_t i = 0; i < size; ++i) {
    EXPECT_EQ(arr[i], expected_arr[i]);
  }
  free(arr);
  fclose(input_file);
}

TEST(ParseInput, invalidSize) {
  FILE *input_file = freopen(TESTS_DIR "invalid_size.txt", "r", stdin);
  if (!input_file) {
    FAIL();
  }

  size_t size = 0;
  int res = read_size_from_input(&size); 
  EXPECT_EQ(res, EXIT_FAILURE);

  fclose(input_file);
}

TEST(LongestArthSeq, corruptedData) {
  FILE *input_file = freopen(TESTS_DIR "corrupted_data.txt", "r", stdin);
  if (!input_file) {
    FAIL();
  }

  size_t size = 0;
  int res = read_size_from_input(&size); 
  EXPECT_EQ(res, EXIT_SUCCESS);

  int *arr = NULL;
  res = read_array_from_input(&arr, size);
  EXPECT_EQ(res, EXIT_FAILURE);

  free(arr);
  fclose(input_file);
}

int main(int argc, char *argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
