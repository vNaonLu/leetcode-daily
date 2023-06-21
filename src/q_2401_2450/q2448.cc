// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Minimum Cost to Make Array Equal
//
// https://leetcode.com/problems/minimum-cost-to-make-array-equal/
//
// Question ID: 2448
// Difficult  : Hard
// Solve Date : 2023/06/21 15:05

#include <algorithm>
#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2448. Minimum Cost to Make Array Equal|:
//
// You are given two 0-indexed arrays |nums| and |cost| consisting each of |n|
// positive integers. You can do the following operation any number of times:
//
//  • Increase or decrease any element of the array |nums| by |1|.
// The cost of doing one operation on the |iᵗʰ| element is |cost[i]|.
// Return the minimum total cost such that all the elements of the array |nums|
// become equal.
//
//

LEETCODE_BEGIN_RESOLVING(2448, MinimumCostToMakeArrayEqual, Solution);

class Solution {
public:
  long long minCost(vector<int> &nums, vector<int> &cost) {
    int64_t tot = 0;
    int64_t sum = 0;
    int     n   = nums.size();

    vector<pair<int, int>> v;
    for (int i = 0; i < n; ++i) {
      v.emplace_back(nums[i], cost[i]);
      sum += cost[i];
    }

    sort(v.begin(), v.end());
    int64_t median;
    int     i = 0;
    while (tot < (sum + 1) / 2 && i < n) {
      tot += (int64_t)v[i].second;
      median = v[i].first;
      ++i;
    }
    int64_t res = 0;
    for (int i = 0; i < n; ++i) {
      res += abs((int64_t)nums[i] - median) * (int64_t)cost[i];
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |n == nums.length == cost.length|
// * |1 <= n <= 10⁵|
// * |1 <= nums[i], cost[i] <= 10⁶|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [1,3,5,2], cost = [2,3,1,14]
// Output: 8
//
// We can make all the elements equal to 2 in the following way:
// - Increase the 0ᵗʰ element one time. The cost is 2.
// - Decrease the 1st element one time. The cost is 3.
// - Decrease the 2ⁿᵈ element three times. The cost is 1 + 1 + 1 = 3.
// The total cost is 2 + 3 + 3 = 8.
// It can be shown that we cannot make the array equal with a smaller cost.

LEETCODE_SOLUTION_UNITTEST(2448, MinimumCostToMakeArrayEqual, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 3, 5, 2};
  vector<int> cost     = {2, 3, 1, 14};
  long long   expect   = 8;
  long long   actual   = solution->minCost(nums, cost);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [2,2,2,2,2], cost = [4,2,8,1,3]
// Output: 0
//
// All the elements are already equal, so no operations are needed.

LEETCODE_SOLUTION_UNITTEST(2448, MinimumCostToMakeArrayEqual, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {2, 2, 2, 2, 2};
  vector<int> cost     = {4, 2, 8, 1, 3};
  long long   expect   = 0;
  long long   actual   = solution->minCost(nums, cost);
  LCD_EXPECT_EQ(expect, actual);
}
