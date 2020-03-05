#include <gtest/gtest.h>

extern "C" {
  #include "longest_arth_seq.h"
}

TEST(LongestArthSeq, leetCodeEx1) {
  const int size = 4;
  const int arr[size] = {3, 6, 9, 12};

  int *arth_seq = NULL;
  ASSERT_EQ(longest_arith_seq(arr, size, &arth_seq), size);

  for (size_t i = 0; i < size; ++i) {
    ASSERT_EQ(arr[i], arth_seq[i]);
  }

  free(arth_seq);
}

TEST(LongestArthSeq, leetCodeEx2) {
  const size_t size = 5;
  const int arr[size] = {9, 4, 7, 2, 10};

  const int exp_arth_len = 3;
  const int exp_arth_seq[exp_arth_len] = {4, 7, 10};

  int *arth_seq = NULL;
  const int arth_len = longest_arith_seq(arr, size, &arth_seq);
  ASSERT_EQ(arth_len, exp_arth_len);

  for (int i = 0; i < arth_len; ++i) {
    ASSERT_EQ(exp_arth_seq[i], arth_seq[i]);
  }
  free(arth_seq);
}

TEST(LongestArthSeq, InvalidLength) {
  const size_t size = 5;
  const int arr[size] = {9, 4, 7, 2, 10};

  const int arth_len = longest_arith_seq(arr, size, nullptr);
  ASSERT_EQ(arth_len, INVALID_LENGTH);
}

int main(int argc, char *argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
