#include <vector>

#include "gtest/gtest.h"

extern int FindKthLargestWithPartialInsertSort(const std::vector<int>& nums,
                                               int k);
extern int FindKthLargestWithHeapSort(std::vector<int>& nums, int k);

class FindKthLargestFixture : public ::testing::Test {
 protected:
  std::vector<int> typical_test_data{12, 3, 7, 5, 2, 7, 10, 7, 15, 16, 7, 18};
};

TEST_F(FindKthLargestFixture, KOutOfRange) {
  ASSERT_EQ(FindKthLargestWithPartialInsertSort(typical_test_data, k), -1);
  ASSERT_EQ(FindKthLargestWithHeapSort(typical_test_data, k), -1);

  k = 0;
  ASSERT_EQ(FindKthLargestWithPartialInsertSort(typical_test_data, k), -1);
  ASSERT_EQ(FindKthLargestWithHeapSort(typical_test_data, k), -1);
}

TEST_F(FindKthLargestFixture, Typical) {
  int k{1};

  EXPECT_EQ(FindKthLargestWithPartialInsertSort(typical_test_data, k), 18);
  EXPECT_EQ(FindKthLargestWithHeapSort(typical_test_data, k), 18);

  k = 12;
  EXPECT_EQ(FindKthLargestWithPartialInsertSort(typical_test_data, k), 2);
  EXPECT_EQ(FindKthLargestWithHeapSort(typical_test_data, k), 2);

  k = 4;
  EXPECT_EQ(FindKthLargestWithPartialInsertSort(typical_test_data, k), 12);
  EXPECT_EQ(FindKthLargestWithHeapSort(typical_test_data, k), 12);

  k = 6;
  EXPECT_EQ(FindKthLargestWithPartialInsertSort(typical_test_data, k), 7);
  EXPECT_EQ(FindKthLargestWithHeapSort(typical_test_data, k), 7);

  k = 8;
  EXPECT_EQ(FindKthLargestWithPartialInsertSort(typical_test_data, k), 7);
  EXPECT_EQ(FindKthLargestWithHeapSort(typical_test_data, k), 7);
}