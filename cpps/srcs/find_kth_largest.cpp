#include <list>
#include <vector>

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