#include <algorithm>
#include <vector>

#include "stdio.h"

// -100 <= matrix[i][j] <= 100
// n = matrix.size() = matrix[i].size()
// 1 <= n <= 100
int MinFallPathSum(const std::vector<std::vector<int>>& matrix) {
  if (matrix.size() == 0) {
    return 0;
  }

  constexpr int max_possible_sum{10000};  // all element = 100, n = 100
  const auto row_count = matrix.size();

  // min_fall_path[row k] is the min of the min_fall_path to everynode in row k
  // to AVOID recursive in dp,
  // actually we just need another n*n matrix to store all the min path sum in
  // every layer.
  // But actually during the iteration we only need the previous row's result,
  // so here just store one row's sum for optimization.

  // To optimize(actually not so useful, tried on Leetcode):
  // we can operate on last row seperately out of the loop to directly get the
  // return value, instead of get it values and get the min one afterwards.
  // Then we have to also give the at least 2 * 2 matrix precondition.

  // construct it to
  // max_possible_sum, sum, sum, sum.... sum, max_possible_sum
  // to avoid index out of range
  // for first row, the sum is the element value its self
  std::vector<int> pre_row_min_fall_pathes_sums{max_possible_sum,
                                                max_possible_sum};
  pre_row_min_fall_pathes_sums.insert(pre_row_min_fall_pathes_sums.begin() + 1,
                                      matrix[0].begin(), matrix[0].end());
  std::vector<int> curr_row_max_fall_pathes_sums{pre_row_min_fall_pathes_sums};

  for (int i = 1; i < row_count; ++i)  // from row 1 to 2nd last row
  {
    for (int j = 0; j < matrix[i].size(); ++j) {
      // offset after curr_min_fall_pathes_sums expand is 1
      // so j - 1 + 1 = j, and same for j and j + 1
      curr_row_max_fall_pathes_sums[j + 1] =
          matrix[i][j] + std::min({pre_row_min_fall_pathes_sums[j],
                                   pre_row_min_fall_pathes_sums[j + 1],
                                   pre_row_min_fall_pathes_sums[j + 2]});
    }
    pre_row_min_fall_pathes_sums.swap(curr_row_max_fall_pathes_sums);
  }

  auto ret{max_possible_sum};
  for (const auto& value : pre_row_min_fall_pathes_sums) {
    ret = value < ret ? value : ret;
  }
  return ret;
}