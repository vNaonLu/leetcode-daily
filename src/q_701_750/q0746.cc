// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Min Cost Climbing Stairs
//
// https://leetcode.com/problems/min-cost-climbing-stairs/
//
// Question ID: 746
// Difficult  : Easy
// Solve Date : 2021/10/11 15:07

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |746. Min Cost Climbing Stairs|:
//
// You are given an integer array |cost| where |cost[i]| is the cost of |iᵗʰ|
// step on a staircase. Once you pay the cost, you can either climb one or two
// steps. You can either start from the step with index |0|, or the step with
// index |1|. Return the minimum cost to reach the top of the floor.  
//

LEETCODE_BEGIN_RESOLVING(746, MinCostClimbingStairs, Solution);

class Solution {
public:
  int minCostClimbingStairs(vector<int> &cost) {
    vector<int> dp(cost.size() + 1, 0);
    for (int i = 2; i < dp.size(); ++i)
      dp[i] = min(dp[i - 1] + cost[i - 1], dp[i - 2] + cost[i - 2]);
    return dp.back();
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |2 <= cost.length <= 1000|
// * |0 <= cost[i] <= 999|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: cost = [10,15,20]
// Output: 15
//
// You will start at index 1.
// - Pay 15 and climb two steps to reach the top.
// The total cost is 15.

LEETCODE_SOLUTION_UNITTEST(746, MinCostClimbingStairs, example_1) {
  auto        solution = MakeSolution();
  vector<int> cost     = {10, 15, 20};
  int         expect   = 15;
  int         actual   = solution->minCostClimbingStairs(cost);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: cost = [1,100,1,1,1,100,1,1,100,1]
// Output: 6
//
// You will start at index 0.
// - Pay 1 and climb two steps to reach index 2.
// - Pay 1 and climb two steps to reach index 4.
// - Pay 1 and climb two steps to reach index 6.
// - Pay 1 and climb one step to reach index 7.
// - Pay 1 and climb two steps to reach index 9.
// - Pay 1 and climb one step to reach the top.
// The total cost is 6.

LEETCODE_SOLUTION_UNITTEST(746, MinCostClimbingStairs, example_2) {
  auto        solution = MakeSolution();
  vector<int> cost     = {1, 100, 1, 1, 1, 100, 1, 1, 100, 1};
  int         expect   = 6;
  int         actual   = solution->minCostClimbingStairs(cost);
  LCD_EXPECT_EQ(expect, actual);
}
