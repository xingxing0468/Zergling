#include <vector>

#include "gtest/gtest.h"

extern void HeapSort(std::vector<int>& nums);
extern void SetupMinHeap(std::vector<int>& nums);

TEST(HeapSort, TestSetupMinHeap) {
  std::vector<int> nums{10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
  std::vector<int> expect{1, 2, 5, 3, 6, 10, 8, 4, 7, 9};
  SetupMinHeap(nums);

  EXPECT_EQ(nums, expect);
}

TEST(HeapSort, Typical) {
  std::vector<int> nums{6, 5, 3, 1, 4, 7, 8, 0, 10, 9, 2};
  std::vector<int> expect{10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
  HeapSort(nums);

  EXPECT_EQ(nums, expect);
}

TEST(HeapSort, AlreadySortedByNotMinHeap) {
  std::vector<int> nums{10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
  std::vector<int> expect{10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
  HeapSort(nums);

  EXPECT_EQ(nums, expect);
}