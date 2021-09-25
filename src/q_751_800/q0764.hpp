
#ifndef LEETCODE_Q764_H__
#define LEETCODE_Q764_H__
#include <iostream>
#include <vector>
#include <unordered_map>

namespace l764 {
using namespace std;
class Solution {
 public:
  int orderOfLargestPlusSign(int n, vector<vector<int>>& mines) {
    unordered_map<int, bool> banned;
    vector<vector<int>> dp(n, vector<int>(n));

    for (vector<int> mine : mines) {
      banned.insert({mine[0] * n + mine[1], true});
    }
    int res = 0, count;

    for (int i = 0; i < n; ++i) {
      count = 0;
      for (int j = 0; j < n; ++j) {
        count = banned.count(i * n + j) ? 0 : count + 1;
        dp[i][j] = count;
      }

      count = 0;
      for (int j = n - 1; j > -1; --j) {
        count = banned.count(i * n + j) ? 0 : count + 1;
        dp[i][j] = min(dp[i][j], count);
      }
    }

    for (int i = 0; i < n; ++i) {
      count = 0;
      for (int j = 0; j < n; ++j) {
        count = banned.count(j * n + i) ? 0 : count + 1;
        dp[j][i] = min(dp[j][i], count);
      }

      count = 0;
      for (int j = n - 1; j > -1; --j) {
        count = banned.count(j * n + i) ? 0 : count + 1;
        dp[j][i] = min(dp[j][i], count);
        res = max(res, dp[j][i]);
      }
    }

    return res;
  }
};
}  // namespace l763
#endif