#include <set>

#include "gtest/gtest.h"

extern int GetMinCoinCountForAmount(const std::set<int>& coin_values,
                                    unsigned int amount);

TEST(CoinsCountTest, Base) {
  EXPECT_EQ(GetMinCoinCountForAmount({5, 2, 1}, 0), 0);
}

TEST(CoinsCountTest, Failed) {
  EXPECT_EQ(GetMinCoinCountForAmount({5, 2}, 1), -1);
  EXPECT_EQ(GetMinCoinCountForAmount({5, 2}, 3), -1);
}

TEST(CoinsCountTest, Typical) {
  EXPECT_EQ(GetMinCoinCountForAmount({5, 2, 1}, 1), 1);
  EXPECT_EQ(GetMinCoinCountForAmount({5, 2, 1}, 2), 1);
  EXPECT_EQ(GetMinCoinCountForAmount({5, 2, 1}, 5), 1);
  EXPECT_EQ(GetMinCoinCountForAmount({5, 2, 1}, 11), 3);
}