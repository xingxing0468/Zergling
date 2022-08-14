#include <vector>

#include "gtest/gtest.h"

using MatrixT = std::vector<std::vector<int>>;
extern int MinFallPathSum(const MatrixT& matrix);

TEST(MinFallPathSumTest, EmptyMatrix) {
  EXPECT_EQ(MinFallPathSum(MatrixT()), 0);
}

TEST(MinFallPathSumTest, OnlyOneElement) {
  const MatrixT matrix{{-48}};
  EXPECT_EQ(MinFallPathSum(matrix), -48);
}

TEST(MinFallPathSumTest, Typical) {
  // clang-format off
  const MatrixT matrix{
    {2, 1, 3},
    {6, 5, 4},
    {7, 8, 9}
  };
  // clang-format on

  EXPECT_EQ(MinFallPathSum(matrix), 13);
}