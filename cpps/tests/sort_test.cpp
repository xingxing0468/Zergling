#include <vector>

#include "gtest/gtest.h"

extern void MergeSort(std::vector<int>& nums);
extern void HeapSort(std::vector<int>& nums);
extern void SetupMinHeap(std::vector<int>& nums);

class SortTestFixture : public ::testing::Test {
 protected:
  std::vector<int> sorted_nums_{10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
  std::vector<int> typical_nums_{6, 5, 3, 1, 4, 7, 8, 0, 10, 9, 2};
};
TEST_F(SortTestFixture, TestSetupMinHeap) {
  std::vector<int> expect{1, 2, 5, 3, 6, 10, 8, 4, 7, 9};
  std::vector<int> data_to_be_tested{{10, 9, 8, 7, 6, 5, 4, 3, 2, 1}};
  SetupMinHeap(data_to_be_tested);

  EXPECT_EQ(data_to_be_tested, expect);
}

TEST_F(SortTestFixture, TypicalWithHeapSort) {
  std::vector<int> data_to_be_tested{typical_nums_};
  HeapSort(data_to_be_tested);

  EXPECT_EQ(data_to_be_tested, sorted_nums_);
}

TEST_F(SortTestFixture, AlreadySortedByNotMinHeapWithHeapSort) {
  std::vector<int> data_to_be_tested{sorted_nums_};
  std::vector<int> expect{10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
  HeapSort(data_to_be_tested);

  EXPECT_EQ(data_to_be_tested, sorted_nums_);
}

TEST_F(SortTestFixture, TypicalWithMergeSort) {
  std::vector<int> data_to_be_tested{typical_nums_};
  MergeSort(data_to_be_tested);

  EXPECT_EQ(data_to_be_tested, sorted_nums_);
}

TEST_F(SortTestFixture, AlreadySortedWithMergeSort) {
  std::vector<int> data_to_be_tested{sorted_nums_};
  std::vector<int> expect{10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
  MergeSort(data_to_be_tested);

  EXPECT_EQ(data_to_be_tested, sorted_nums_);
}