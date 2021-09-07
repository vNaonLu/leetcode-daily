
#ifndef LEETCODE_Q121_H__
#define LEETCODE_Q121_H__

#include <algorithm>
#include <iostream>
#include <vector>

namespace l121 {
using namespace std;
class Solution {
 public:
  int maxProfit(vector<int>& prices) {
    int ret = 0;
    if (prices.empty()) return 0;
    int current_profit = prices[0];
    for (int i = 1; i < prices.size(); i++) {
      if (current_profit > prices[i]) current_profit = prices[i];

      ret = max(ret, prices[i] - current_profit);
    }

    return ret;
  }
};
}  // namespace l121

#endif