// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Tallest Billboard
//
// https://leetcode.com/problems/tallest-billboard/
//
// Question ID: 956
// Difficult  : Hard
// Solve Date : 2023/06/24 13:21

#include <iosfwd>
#include <numeric>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |956. Tallest Billboard|:
//
// You are installing a billboard and want it to have the largest height. The
// billboard will have two steel supports, one on each side. Each steel support
// must be an equal height. You are given a collection of |rods| that can be
// welded together. For example, if you have rods of lengths |1|, |2|, and |3|,
// you can weld them together to make a support of length |6|. Return the
// largest possible height of your billboard installation. If you cannot support
// the billboard, return |0|.
//
//

LEETCODE_BEGIN_RESOLVING(956, TallestBillboard, Solution);

class Solution {
public:
  int tallestBillboard(vector<int> &rods) {
    int         sum = accumulate(rods.begin(), rods.end(), 0);
    vector<int> dp(sum + 1, -1);
    dp.front() = 0;
    for (auto c : rods) {
      vector<int> dp2 = dp;
      for (int i = 0; i <= sum - c; ++i) {
        if (dp2[i] >= 0) {
          dp[i + c]      = max(dp[i + c], dp2[i]);
          dp[abs(i - c)] = max(dp[abs(i - c)], dp2[i] + min(i, c));
        }
      }
    }
    return dp.front();
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= rods.length <= 20|
// * |1 <= rods[i] <= 1000|
// * |sum(rods[i]) <= 5000|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: rods = [1,2,3,6]
// Output: 6
//
// We have two disjoint subsets {1,2,3} and {6}, which have the same sum = 6.

LEETCODE_SOLUTION_UNITTEST(956, TallestBillboard, example_1) {
  auto        solution = MakeSolution();
  vector<int> rods     = {1, 2, 3, 6};
  int         expect   = 6;
  int         actual   = solution->tallestBillboard(rods);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: rods = [1,2,3,4,5,6]
// Output: 10
//
// We have two disjoint subsets {2,3,5} and {4,6}, which have the same sum = 10.

LEETCODE_SOLUTION_UNITTEST(956, TallestBillboard, example_2) {
  auto        solution = MakeSolution();
  vector<int> rods     = {1, 2, 3, 4, 5, 6};
  int         expect   = 10;
  int         actual   = solution->tallestBillboard(rods);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: rods = [1,2]
// Output: 0
//
// The billboard cannot be supported, so we return 0.

LEETCODE_SOLUTION_UNITTEST(956, TallestBillboard, example_3) {
  auto        solution = MakeSolution();
  vector<int> rods     = {1, 2};
  int         expect   = 0;
  int         actual   = solution->tallestBillboard(rods);
  LCD_EXPECT_EQ(expect, actual);
}
