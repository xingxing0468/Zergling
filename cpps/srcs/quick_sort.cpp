#include <vector>

#include "memory.h"

// For quick sort
// in [lo_index, high_index] return the index of pivot which
// Ensures [lo_index, pivot) >= pivot >= (pivot, high_index]
int GetPartitionIndex(std::vector<int>& nums, int lo_index, int high_index) {
  auto pivot_index = lo_index;
  auto pivot_value = nums[pivot_index];

  // consecuctive values < pivot_value and have to been moved together with the
  // pivot_value
  int values_to_be_moved_count = 0;
  // int values_to_be_moved_start_idx = -1;
  for (auto i = lo_index + 1; i <= high_index; ++i) {
    if (nums[i] < pivot_value) {
      ++values_to_be_moved_count;
    } else {  // swap, order: nums[i] > pivot_value > values_to_be_moved
      nums[pivot_index] = nums[i];

      ++pivot_index;
      if (values_to_be_moved_count > 0) {
        std::vector<int> tmp;
        tmp.reserve(values_to_be_moved_count);
        tmp.insert(tmp.begin(), nums.begin() + pivot_index,
                   nums.begin() + pivot_index + values_to_be_moved_count);
        memcpy(nums.data() + pivot_index + 1, tmp.data(),
               values_to_be_moved_count * sizeof(int));
      }
      nums[pivot_index] = pivot_value;
    }
  }
  return pivot_index;
}

void quick_sort_with_index(std::vector<int>& nums, int low_index,
                           int high_index) {
  if (low_index >= high_index) {
    return;
  }
  auto pivot_index = GetPartitionIndex(nums, low_index, high_index);
  quick_sort_with_index(nums, low_index, pivot_index - 1);
  quick_sort_with_index(nums, pivot_index + 1, high_index);
}

void QuickSort(std::vector<int>& nums) {
  return quick_sort_with_index(nums, 0, nums.size() - 1);
}