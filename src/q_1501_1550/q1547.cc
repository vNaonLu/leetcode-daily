// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Minimum Cost to Cut a Stick
//
// https://leetcode.com/problems/minimum-cost-to-cut-a-stick/
//
// Question ID: 1547
// Difficult  : Hard
// Solve Date : 2023/05/28 14:33

#include <algorithm>
#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1547. Minimum Cost to Cut a Stick|:
//
// Given a wooden stick of length |n| units. The stick is labelled from |0| to
// |n|. For example, a stick of length 6 is labelled as follows:
// ![img](https://assets.leetcode.com/uploads/2020/07/21/statement.jpg)
// Given an integer array |cuts| where |cuts[i]| denotes a position you should
// perform a cut at. You should perform the cuts in order, you can change the
// order of the cuts as you wish. The cost of one cut is the length of the stick
// to be cut, the total cost is the sum of costs of all cuts. When you cut a
// stick, it will be split into two smaller sticks (i.e. the sum of their
// lengths is the length of the stick before the cut). Please refer to the first
// example for a better explanation. Return the minimum total cost of the cuts.
//
//

LEETCODE_BEGIN_RESOLVING(1547, MinimumCostToCutAStick, Solution);

class Solution {
public:
  int minCost(int n, vector<int> &cuts) {
    cuts.emplace_back(n);
    cuts.insert(cuts.begin(), 0);
    sort(cuts.begin(), cuts.end());
    vector<vector<int>> dp(cuts.size(), vector<int>(cuts.size(), -1));
    return solve(1, cuts.size() - 2, cuts, dp);
  }

private:
  int solve(int i, int j, vector<int> &cut, vector<vector<int>> &dp) {
    if (i > j) {
      return 0;
    }
    if (dp[i][j] != -1) {
      return dp[i][j];
    }
    int res = numeric_limits<int>::max();
    for (int k = i; k <= j; ++k) {
      int h = cut[j + 1] - cut[i - 1] + solve(i, k - 1, cut, dp) +
              solve(k + 1, j, cut, dp);
      res = min(res, h);
    }
    return dp[i][j] = res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |2 <= n <= 10⁶|
// * |1 <= cuts.length <= min(n - 1, 100)|
// * |1 <= cuts[i] <= n - 1|
// * All the integers in |cuts| array are distinct.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: n = 7, cuts = [1,3,4,5]
// Output: 16
//
// Using cuts order = [1, 3, 4, 5] as in the input leads to the following
// scenario:
// ![img](https://assets.leetcode.com/uploads/2020/07/21/e11.jpg)
// The first cut is done to a rod of length 7 so the cost is 7. The second cut
// is done to a rod of length 6 (i.e. the second part of the first cut), the
// third is done to a rod of length 4 and the last cut is to a rod of length 3.
// The total cost is 7 + 6 + 4 + 3 = 20. Rearranging the cuts to be [3, 5, 1, 4]
// for example will lead to a scenario with total cost = 16 (as shown in the
// example photo 7 + 4 + 3 + 2 = 16).

LEETCODE_SOLUTION_UNITTEST(1547, MinimumCostToCutAStick, example_1) {
  auto        solution = MakeSolution();
  int         n        = 7;
  vector<int> cuts     = {1, 3, 4, 5};
  int         expect   = 16;
  int         actual   = solution->minCost(n, cuts);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: n = 9, cuts = [5,6,1,4,2]
// Output: 22
//
// If you try the given cuts ordering the cost will be 25.
// There are much ordering with total cost <= 25, for example, the order [4, 6,
// 5, 2, 1] has total cost = 22 which is the minimum possible.

LEETCODE_SOLUTION_UNITTEST(1547, MinimumCostToCutAStick, example_2) {
  auto        solution = MakeSolution();
  int         n        = 9;
  vector<int> cuts     = {5, 6, 1, 4, 2};
  int         expect   = 22;
  int         actual   = solution->minCost(n, cuts);
  LCD_EXPECT_EQ(expect, actual);
}

// [Extra Testcase #1]
//  Input: 361854
// [189669,19764,186974,266684,308618,191043,93845,63299,301226,240305,193004,263010,96073,46256,158102,339050,126229,84452,194933,156037,108468,280630,331189,68099,113690,226890,72364,61761,27058,45026,312309,254439,45520,352784,146420,184754,4940,337288,139892,245863,121428,129668,235331,169793,303858,17980,82103,173929,153859,346349,212767,34686,292509,277623,229869,179551,109328,277635,90272,161893,231118,234035,197316,55569,145427,331347,273905,99093,897,236085,178546,57071,164600,73468,238137,183884,273592,67280,163749,239833,212549,312876,126574,255182,68843,357516,103654,114507,317125,264970]
// Output: 2252276
//

LEETCODE_SOLUTION_UNITTEST(1547, MinimumCostToCutAStick, extra_testcase_1) {
  auto        solution = MakeSolution();
  int         n        = 361854;
  vector<int> cuts     = {
      189669, 19764,  186974, 266684, 308618, 191043, 93845,  63299,  301226,
      240305, 193004, 263010, 96073,  46256,  158102, 339050, 126229, 84452,
      194933, 156037, 108468, 280630, 331189, 68099,  113690, 226890, 72364,
      61761,  27058,  45026,  312309, 254439, 45520,  352784, 146420, 184754,
      4940,   337288, 139892, 245863, 121428, 129668, 235331, 169793, 303858,
      17980,  82103,  173929, 153859, 346349, 212767, 34686,  292509, 277623,
      229869, 179551, 109328, 277635, 90272,  161893, 231118, 234035, 197316,
      55569,  145427, 331347, 273905, 99093,  897,    236085, 178546, 57071,
      164600, 73468,  238137, 183884, 273592, 67280,  163749, 239833, 212549,
      312876, 126574, 255182, 68843,  357516, 103654, 114507, 317125, 264970};
  int expect = 2252276;
  int actual = solution->minCost(n, cuts);
  LCD_EXPECT_EQ(expect, actual);
}
