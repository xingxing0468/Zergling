#include <stdio.h>

#include <algorithm>

#include "cpps/includes/lis.h"
#include "gtest/gtest.h"

TEST(LIS, Typical) {
  std::vector<int> seq{100, 80, 50, 60, 70, 20, 30, 10, 40, 60, 90};
  std::vector<int> expected{20, 30, 40, 60, 90};
  auto ret = FindLongestIncreasingSubSequence(seq);
  printf("Sequence: \n");
  std::for_each(seq.begin(), seq.end(),
                [](const int& num) { printf("%d ", num); });
  printf("\n");
  EXPECT_EQ(expected, ret);
}