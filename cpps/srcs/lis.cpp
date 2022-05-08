#include "cpps/includes/lis.h"

#include <assert.h>
#include <stdio.h>
// If only the count is required to return
// Then we can only have a table to store count
// Instead of store the whole sub sequence

// 100, 80, 50, 60, 70, 65, 20, 30, 10, 40, 15, 60, 90, 25
// sub_iss_table.size():
//   1,  1,  1,  2,  3,  3,  1,  2,  1,  3,  2,  4,  5,  3

// sub_iss_table:
// [..., 100] -> [100]
// [..., 80]  -> [80]
// [..., 50]  -> [50]
// [..., 60]  -> [50, 60]
// [..., 70]  -> [50, 60, 70]
// [..., 65]  -> [50, 60, 65]
// [..., 20]  -> [20]
// [..., 30]  -> [20, 30]
// [..., 10]  -> [10]
// [..., 40]  -> [20, 30, 40]
// [..., 15]  -> [10, 15]
// [..., 60]  -> [20, 30, 40, 60]
// [..., 90]  -> [20, 30, 40, 60, 90]
// [..., 25]  -> [10, 15, 25]

std::vector<int> FindLongestIncreasingSubSequence(
    const std::vector<int>& sequence) {
  // is end with each element in input seq
  std::vector<std::vector<int>> sub_iss_table{};
  sub_iss_table.resize(sequence.size());

  size_t max_length = 0;
  int lis_end_element_index = -1;

  for (size_t i = 0; i < sequence.size(); ++i) {  // loop whole sequence
    size_t curr_max_iss_length = 0;
    int curr_max_iss_length_end_element_index = -1;

    for (size_t j = 0; j < i;
         ++j) {  // loop sub-sequence, end to current element
      if (sequence[j] < sequence[i] &&
          sub_iss_table[j].size() > curr_max_iss_length) {
        curr_max_iss_length = sub_iss_table[j].size();
        curr_max_iss_length_end_element_index = j;
      }
    }

    if (curr_max_iss_length_end_element_index >=
        0)  // NOT min element until now
    {
      // first take the max iss
      sub_iss_table[i] = sub_iss_table[curr_max_iss_length_end_element_index];
    }

    sub_iss_table[i].push_back(sequence[i]);  // including current element

    if (sub_iss_table[i].size() >
        max_length) {  // update max_length and lis_end_element_index
      max_length = sub_iss_table[i].size();
      lis_end_element_index = i;
    }
  }

  // Debug trace
  //for (const auto& sub_iss : sub_iss_table) {
    // printf("sub iss: ");
    // for (const auto& element : sub_iss) {
    //  printf("%d ", element);
    // }
    // printf("\n");
  //}

  return lis_end_element_index < 0 ? std::vector<int>{}
                                   : sub_iss_table[lis_end_element_index];
}
