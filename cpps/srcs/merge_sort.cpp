#include <iostream>
#include <vector>

#include "memory.h"

// merge 2 sorted array
// [low, mid), [mid, high)
void merge(std::vector<int>& nums, int low, int mid, int high,
           std::vector<int>& buffer) {
  buffer.clear();
  int low_iter{low};
  int high_iter(mid);
  while (1) {
    if (low_iter >= mid) {
      // no available element any more in the 1st
      // insert all the rest element in 2nd array into buffer
      buffer.insert(buffer.end(), nums.begin() + high_iter,
                    nums.begin() + high);
      break;
    } else if (high_iter >= high) {
      // no available element any more in the 2nd array
      // insert all the rest element in 1st array into buffer
      buffer.insert(buffer.end(), nums.begin() + low_iter, nums.begin() + mid);
      break;
    } else if (nums[low_iter] > nums[high_iter]) {
      buffer.push_back(nums[low_iter]);
      ++low_iter;
    } else {
      buffer.push_back(nums[high_iter]);
      ++high_iter;
    }
  }
  memcpy(nums.data() + low, buffer.data(), sizeof(int) * buffer.size());
}

// to follow the iter definiion, its [start_idx, end_idx)
void sort(std::vector<int>& nums, int start_idx, int end_idx,
          std::vector<int>& buffer) {  // buffer to avoid alloc/release
                                       // frequently during recursive call
  if (start_idx >= nums.size()) {
    std::cerr << "Invalid start_idx, input size: " << nums.size()
              << " start index: " << start_idx << std::endl;
    return;
  }

  if (start_idx >= end_idx) {
    std::cerr << "Invalid start_idx, end_idx: " << start_idx << " " << end_idx
              << std::endl;
    return;
  }
  if (start_idx == end_idx - 1) {  // Only 1 element to sort, recursive ends
    return;
  }

  int mid = (start_idx + end_idx + 1) / 2;  // to get the ceil of the mid index
  sort(nums, start_idx, mid, buffer);
  sort(nums, mid, end_idx, buffer);
  merge(nums, start_idx, mid, end_idx, buffer);
}

void MergeSort(std::vector<int>& nums) {
  std::vector<int> buffer;
  buffer.reserve(nums.size());
  return sort(nums, 0, nums.size(), buffer);
}