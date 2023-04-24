// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Profitable Schemes
//
// https://leetcode.com/problems/profitable-schemes/
//
// Question ID: 879
// Difficult  : Hard
// Solve Date : 2023/04/21 11:10

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |879. Profitable Schemes|:
//
// There is a group of |n| members, and a list of various crimes they could
// commit. The |iᵗʰ| crime generates a |profit[i]| and requires |group[i]|
// members to participate in it. If a member participates in one crime, that
// member can't participate in another crime. Let's call a profitable scheme any
// subset of these crimes that generates at least |minProfit| profit, and the
// total number of members participating in that subset of crimes is at most
// |n|. Return the number of schemes that can be chosen. Since the answer may be
// very large, return it modulo |10⁹ + 7|.
//
//

LEETCODE_BEGIN_RESOLVING(879, ProfitableSchemes, Solution);

class Solution {
public:
  int profitableSchemes(int n, int minProfit, vector<int> &group,
                        vector<int> &profit) {
    int                         m = group.size();
    vector<vector<vector<int>>> dp(
        m + 1, vector<vector<int>>(n + 1, vector<int>(minProfit + 1)));
    dp[0][0][0] = 1;
    for (int i = 1; i <= m; ++i) {
      int members = group[i - 1];
      int earn    = profit[i - 1];
      for (int j = 0; j <= n; ++j) {
        for (int k = 0; k <= minProfit; ++k) {
          if (j < members) {
            dp[i][j][k] = dp[i - 1][j][k];
          } else {
            dp[i][j][k] =
                (dp[i - 1][j][k] + dp[i - 1][j - members][max(0, k - earn)]) %
                kMod;
          }
        }
      }
    }
    int res = 0;
    for (int i = 0; i <= n; ++i) {
      res = (res + dp[m][i][minProfit]) % kMod;
    }
    return res;
  }

private:
  constexpr static int kMod = 1e9 + 7;
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= n <= 100|
// * |0 <= minProfit <= 100|
// * |1 <= group.length <= 100|
// * |1 <= group[i] <= 100|
// * |profit.length == group.length|
// * |0 <= profit[i] <= 100|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: n = 5, minProfit = 3, group = [2,2], profit = [2,3]
// Output: 2
//
// To make a profit of at least 3, the group could either commit crimes 0 and 1,
// or just crime 1. In total, there are 2 schemes.

LEETCODE_SOLUTION_UNITTEST(879, ProfitableSchemes, example_1) {
  auto        solution  = MakeSolution();
  int         n         = 5;
  int         minProfit = 3;
  vector<int> group     = {2, 2};
  vector<int> profit    = {2, 3};
  int         expect    = 2;
  int         actual = solution->profitableSchemes(n, minProfit, group, profit);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: n = 10, minProfit = 5, group = [2,3,5], profit = [6,7,8]
// Output: 7
//
// To make a profit of at least 5, the group could commit any crimes, as long as
// they commit one. There are 7 possible schemes: (0), (1), (2), (0,1), (0,2),
// (1,2), and (0,1,2).

LEETCODE_SOLUTION_UNITTEST(879, ProfitableSchemes, example_2) {
  auto        solution  = MakeSolution();
  int         n         = 10;
  int         minProfit = 5;
  vector<int> group     = {2, 3, 5};
  vector<int> profit    = {6, 7, 8};
  int         expect    = 7;
  int         actual = solution->profitableSchemes(n, minProfit, group, profit);
  LCD_EXPECT_EQ(expect, actual);
}
