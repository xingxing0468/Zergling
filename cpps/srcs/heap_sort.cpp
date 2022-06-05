#include <vector>

// parent index = i ->
// left child index = 2i + 1
// right child index = 2i + 2
// then if left/right index = j ->
// parent index = (j - 1) / 2
// proof:
// level = n (starts from 0)
// index i = 2^n - 1 + k (k belongs [0, 2^n - 1])
// left/right child in next level n + 1:
// index j = 2^(n + 1) - 1 + l (l = 2k + 0or1) = 2 * 2^n - 1 + 2k + 0/1
// = 2(2^n - 1 + k) + 1 + 0 or 1 = 2i + 1 or 2i + 2

// Support take end index as param to just take the subset of the nums
// as the min heap, e.g. when select step during heap sort
void AdjustToKeepMinHeapBelow(std::vector<int>& nums, int end_idx,
                              int sub_min_heap_root_idx) {
  // interate all the sub heap below to ensure parent is smallest
  // Ensure after the swap the parent value is smaller in every sub heap
  while (2 * sub_min_heap_root_idx + 1 < end_idx) {  // no left child
    auto min_child_idx =
        2 * sub_min_heap_root_idx + 2 >= end_idx  // has right child ?
            ? 2 * sub_min_heap_root_idx + 1
            : (nums[2 * sub_min_heap_root_idx + 1] <
                       nums[2 * sub_min_heap_root_idx + 2]
                   ? (2 * sub_min_heap_root_idx + 1)
                   : (2 * sub_min_heap_root_idx + 2));
    if (nums[min_child_idx] < nums[sub_min_heap_root_idx])  // current swap
    {
      auto tmp = nums[sub_min_heap_root_idx];
      nums[sub_min_heap_root_idx] = nums[min_child_idx];
      nums[min_child_idx] = tmp;

      // iterate next swapped sub heap
      sub_min_heap_root_idx = min_child_idx;
    } else {
      break;
    }
  }  // end of while
}

// Setup minum heap
//         10
//        /   \
//      9       8
//    /   \   /   \
//   7     6 5     4
//  / \   /
// 3   2 1
//         ->
//          1
//        /   \
//      2       5
//    /   \   /   \
//   3     6 10     8
//  / \   /
// 4   7 9

void SetupMinHeap(std::vector<int>& nums) {
  for (int i = nums.size() - 1; i > 0; --i) {
    int parent_value = nums[(i - 1) / 2];
    if (parent_value > nums[i]) {
      // swap, move smaller one to parent pos
      nums[(i - 1) / 2] = nums[i];
      nums[i] = parent_value;

      // Adjust is mandatory to keep the min heap after any swap
      AdjustToKeepMinHeapBelow(nums, nums.size(), i);
    }
  }
}

void HeapSort(std::vector<int>& nums) {
  SetupMinHeap(nums);

  for (int i = nums.size() - 1; i > 0; --i) {
    // first swap the nums[0] and nums[i]
    // to make the nums[i] the minum in [nums[0], nums[i]]
    auto tmp = nums[i];
    nums[i] = nums[0];
    nums[0] = tmp;

    // Have to adjust after swap to keep the min heap
    AdjustToKeepMinHeapBelow(nums, i, 0);
  }
  return;
}