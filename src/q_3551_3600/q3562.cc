// Copyright 2025 Naon Lu
//
// This file describes the solution of
// Maximum Profit from Trading Stocks with Discounts
//
// https://leetcode.com/problems/maximum-profit-from-trading-stocks-with-discounts/
//
// Question ID: 3562
// Difficult  : Hard
// Solve Date : 2025/12/16 10:39

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |3562. Maximum Profit from Trading Stocks with Discounts|:
//
//

LEETCODE_BEGIN_RESOLVING(3562, MaximumProfitFromTradingStocksWithDiscounts,
                         Solution);

class Solution {
public:
  int                         B;
  vector<vector<int>>         tree;
  vector<int>                 present, future;
  vector<vector<vector<int>>> dp;

  vector<int> merge(const vector<int> &A, const vector<int> &B2) {
    vector<int> C(B + 1, -1e9);
    for (int i = 0; i <= B; i++) {
      if (A[i] < 0)
        continue;
      for (int j = 0; i + j <= B; j++) {
        C[i + j] = max(C[i + j], A[i] + B2[j]);
      }
    }
    return C;
  }

  void dfs(int u) {
    dp[u][0] = vector<int>(B + 1, 0);
    dp[u][1] = vector<int>(B + 1, 0);

    for (int v : tree[u]) {
      dfs(v);
    }

    for (int parentBought = 0; parentBought <= 1; parentBought++) {
      int price  = parentBought ? present[u] / 2 : present[u];
      int profit = future[u] - price;

      vector<int> skip(B + 1, 0);
      for (int v : tree[u]) {
        skip = merge(skip, dp[v][0]);
      }

      vector<int> take(B + 1, -1e9);
      if (price <= B) {
        vector<int> base(B + 1, 0);
        for (int v : tree[u]) {
          base = merge(base, dp[v][1]);
        }
        for (int b = price; b <= B; b++) {
          take[b] = base[b - price] + profit;
        }
      }

      for (int b = 0; b <= B; b++) {
        dp[u][parentBought][b] = max(skip[b], take[b]);
      }
    }
  }

  int maxProfit(int n, vector<int> &p, vector<int> &f,
                vector<vector<int>> &hierarchy, int budget) {
    B       = budget;
    present = p;
    future  = f;

    tree.assign(n, {});
    for (auto &e : hierarchy)
      tree[e[0] - 1].push_back(e[1] - 1);

    dp.assign(n, vector<vector<int>>(2));
    dfs(0);

    int ans = 0;
    for (int b = 0; b <= B; b++)
      ans = max(ans, dp[0][0][b]);
    return ans;
  }
};
LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= n <= 160|
// * |present.length, future.length == n|
// * |1 <= present[i], future[i] <= 50|
// * |hierarchy.length == n - 1|
// * |hierarchy[i] == [uᵢ, vᵢ]|
// * |1 <= uᵢ, vᵢ <= n|
// * |uᵢ != vᵢ|
// * |1 <= budget <= 160|
// * There are no duplicate edges.
// * Employee 1 is the direct or indirect boss of every employee.
// * The input graph |hierarchy |is guaranteed to have no cycles.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: n = 2, present = [1,2], future = [4,3], hierarchy = [[1,2]], budget =
//  3
// Output: 5
//

LEETCODE_SOLUTION_UNITTEST(3562, MaximumProfitFromTradingStocksWithDiscounts,
                           example_1) {
  auto                solution  = MakeSolution();
  int                 n         = 2;
  vector<int>         present   = {1, 2};
  vector<int>         future    = {4, 3};
  vector<vector<int>> hierarchy = {
      {1, 2}
  };
  int budget = 3;
  int expect = 5;
  int actual = solution->maxProfit(n, present, future, hierarchy, budget);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: n = 2, present = [3,4], future = [5,8], hierarchy = [[1,2]], budget =
//  4
// Output: 4
//

LEETCODE_SOLUTION_UNITTEST(3562, MaximumProfitFromTradingStocksWithDiscounts,
                           example_2) {
  auto                solution  = MakeSolution();
  int                 n         = 2;
  vector<int>         present   = {3, 4};
  vector<int>         future    = {5, 8};
  vector<vector<int>> hierarchy = {
      {1, 2}
  };
  int budget = 4;
  int expect = 4;
  int actual = solution->maxProfit(n, present, future, hierarchy, budget);
  LCD_EXPECT_EQ(expect, actual);
}
