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
  if (nums.size() < k) {
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

int FindKthLargest(const std::vector<int>& nums, int k) {
  return FindKthLargestWithPartialInsertSort(nums, k);
}
