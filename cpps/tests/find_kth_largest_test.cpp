#include <vector>

#include "gtest/gtest.h"

extern int FindKthLargest(const std::vector<int>& nums, int k);

class FindKthLargestFixture : public ::testing::Test {
 protected:
  const std::vector<int> typical_test_data{12, 3, 7,  5,  2, 7,
                                           10, 7, 15, 16, 7, 18};
};

TEST_F(FindKthLargestFixture, KOutOfRange) {
  int k{static_cast<int>(typical_test_data.size()) + 1};
  EXPECT_EQ(FindKthLargest(typical_test_data, k), -1);
}

TEST_F(FindKthLargestFixture, Typical) {
  int k{1};
  EXPECT_EQ(FindKthLargest(typical_test_data, k), 18);

  k = 12;
  EXPECT_EQ(FindKthLargest(typical_test_data, k), 2);

  k = 4;
  EXPECT_EQ(FindKthLargest(typical_test_data, k), 12);

  k = 6;
  EXPECT_EQ(FindKthLargest(typical_test_data, k), 7);

  k = 8;
  EXPECT_EQ(FindKthLargest(typical_test_data, k), 7);
}
