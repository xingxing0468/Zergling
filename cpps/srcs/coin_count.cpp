#include <set>
#include <vector>

int FillCoinCountTable(const std::set<int>& coin_values, unsigned int amount,
                       std::vector<int>& coin_min_count_table) {
  if (amount == 0) {
    return 0;
  }
  if (coin_min_count_table[amount] != -666) {  // calculated before
    return coin_min_count_table[amount];
  }

  int init_min_coin_count = amount + 1;  // Has to be the max possible value
  int min_coin_count = init_min_coin_count;
  for (const auto& v : coin_values) {
    if (amount < v) {
      continue;  // NOT possible add 1 coin of this coin value, e.g. amount 2
                 // with a coin of value 5
    }
    auto coin_count_with_amount_without_current_coin_value =
        FillCoinCountTable(coin_values, amount - v, coin_min_count_table);
    if (coin_count_with_amount_without_current_coin_value ==
        -1)  // NOT possilbe to construct the value without current coin value
    {
      continue;
    }
    min_coin_count =
        min_coin_count < coin_count_with_amount_without_current_coin_value + 1
            ? min_coin_count
            : coin_count_with_amount_without_current_coin_value + 1;
  }
  if (min_coin_count == init_min_coin_count)  // NOT possible to find the
                                              // combination for this value
  {
    min_coin_count = -1;
  }
  coin_min_count_table[amount] = min_coin_count;
  return min_coin_count;
}

int GetMinCoinCountForAmount(const std::set<int>& coin_values,
                             unsigned int amount) {
  std::vector<int> coin_min_count_table{0};
  coin_min_count_table.insert(coin_min_count_table.begin() + 1, amount + 1,
                              -666);

  for (const auto& v : coin_values) {
    if (amount >= v) {
      coin_min_count_table[v] = 1;
    }
  }
  FillCoinCountTable(coin_values, amount, coin_min_count_table);
  return coin_min_count_table[amount];
}