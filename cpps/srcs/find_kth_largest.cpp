#include <algorithm>
#include <list>
#include <random>
#include <set>
#include <vector>

#include "memory.h"

// TO BE optimized with binary insert?
void insert_element_following_order(std::list<int>& collection, int value) {
  bool bInserted{false};
  for (auto iter = collection.begin(); iter != collection.end(); ++iter) {
    if (value > *iter) {
      collection.insert(iter, value);
      bInserted = true;
      break;
    }
  }

  if (!bInserted) {
    collection.push_back(value);
  }
}

int FindKthLargestWithPartialInsertSort(const std::vector<int>& nums, int k) {
  if (nums.size() < k || k < 1) {
    return -1;
  }
  std::list<int> target_list{};

  for (const auto& v : nums) {
    if (target_list.size() < k) {
      insert_element_following_order(target_list, v);
    } else {
      if (v > target_list.back()) {
        insert_element_following_order(target_list, v);
        target_list.pop_back();
      }
    }
  }
  return target_list.back();
}

void AdjustToKeepMaxHeapBelow(std::vector<int>& nums, int end_idx,
                              int sub_max_heap_root_idx) {
  // interate all the sub heap below to ensure parent is smallest
  // Ensure after the swap the parent value is smaller in every sub heap
  while (2 * sub_max_heap_root_idx + 1 < end_idx) {  // no left child
    auto max_child_idx =
        2 * sub_max_heap_root_idx + 2 >= end_idx  // has right child ?
            ? 2 * sub_max_heap_root_idx + 1
            : (nums[2 * sub_max_heap_root_idx + 1] >
                       nums[2 * sub_max_heap_root_idx + 2]
                   ? (2 * sub_max_heap_root_idx + 1)
                   : (2 * sub_max_heap_root_idx + 2));
    if (nums[max_child_idx] > nums[sub_max_heap_root_idx])  // current swap
    {
      auto tmp = nums[sub_max_heap_root_idx];
      nums[sub_max_heap_root_idx] = nums[max_child_idx];
      nums[max_child_idx] = tmp;
      sub_max_heap_root_idx = max_child_idx;
    } else {
      break;
    }
  }  // end of while
}

void SetupMaxHeap(std::vector<int>& nums) {
  for (int i = nums.size() - 1; i > 0; --i) {
    int parent_value = nums[(i - 1) / 2];
    if (parent_value < nums[i]) {
      // swap, move smaller one to parent pos
      nums[(i - 1) / 2] = nums[i];
      nums[i] = parent_value;
      AdjustToKeepMaxHeapBelow(nums, nums.size(), i);
    }
  }
}

int FindKthLargestWithHeapSort(std::vector<int>& input, int order) {
  if (order <= 0 || order > input.size()) {
    return -1;
  }
  SetupMaxHeap(input);

  // only need the max kth, so its enough just loop to input.size()) - order
  for (int i = input.size() - 1; i >= static_cast<int>(input.size()) - order;
       --i) {
    // first swap the input[0] and input[i]
    // to make the input[i] the max in [input[0], input[i]]
    auto tmp = input[i];
    input[i] = input[0];
    input[0] = tmp;

    // Have to adjust after swap to keep the min heap
    AdjustToKeepMaxHeapBelow(input, i, 0);
  }
  return input[input.size() - order];
}

int FindKthLergetWithMinHeapOfKSize(std::vector<int>& nums, int k) {
  if (k <= 0 || k > nums.size()) {
    return -1;
  }

  std::multiset<int> min_heap_of_k_elements;
  for (const auto value : nums) {
    if (min_heap_of_k_elements.size() < k) {
      min_heap_of_k_elements.insert(value);  // no enough element in the heap
    } else {  // kick the smallest out, because we only need to give max kth
      if (value > *min_heap_of_k_elements.begin()) {
        min_heap_of_k_elements.erase(min_heap_of_k_elements.begin());
        min_heap_of_k_elements.insert(value);
      }
    }
  }

  // the root element is the smallest one in the heap,
  // and all the elements in the heap are larger than anyone in the rest of the
  // heap
  return *min_heap_of_k_elements.begin();
}

// For quick sort
// in [lo_index, high_index] return the index of pivot which
// Ensures [lo_index, pivot) >= pivot >= (pivot, high_index]
int GetPartitionIndex(std::vector<int>& nums, int lo_index, int high_index) {
  auto pivot_index = lo_index;
  auto pivot_value = nums[pivot_index];

  // consecuctive values < pivot_value and have to been moved together with the
  // pivot_value
  int values_to_be_moved_count = 0;
  for (auto i = lo_index + 1; i <= high_index; ++i) {
    if (nums[i] < pivot_value) {
      ++values_to_be_moved_count;
    } else {  // swap, order: nums[i] > pivot_value > values_to_be_moved
      nums[pivot_index] = nums[i];

      ++pivot_index;
      if (values_to_be_moved_count > 0) {
        // Some compiler forbidden copy the memory if there is overlap
        // between dst and src(Error: memcpy-param-overlap)
        // so we have to allocate another container to cache the values
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

int FindKthLergetWithQuickSelection(std::vector<int>& nums, int k) {
  if (k <= 0 || k > nums.size()) {
    return -1;
  }

  // shuffle the input to make the average complexy to O(2N)
  std::random_device rd;
  std::default_random_engine rng(rd());
  std::shuffle(nums.begin(), nums.end(), rng);

  auto expected_index = k - 1;  // convert k to index
  int lo_index = 0;
  int high_index = static_cast<int>(nums.size()) - 1;

  auto current_pivot_idx = GetPartitionIndex(nums, lo_index, high_index);

  while (1) {
    if (current_pivot_idx == expected_index) {
      break;
    }
    // exist in [lo_index, current_pivot_idx)
    else if (current_pivot_idx > expected_index) {
      high_index = current_pivot_idx - 1;
    }
    // exist in [current_pivot_idx, high_index)
    else {
      lo_index = current_pivot_idx + 1;
    }
    current_pivot_idx = GetPartitionIndex(nums, lo_index, high_index);
  }
  return nums[current_pivot_idx];
}