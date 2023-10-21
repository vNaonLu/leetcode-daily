// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Constrained Subsequence Sum
//
// https://leetcode.com/problems/constrained-subsequence-sum/
//
// Question ID: 1425
// Difficult  : Hard
// Solve Date : 2023/10/21 13:59

#include <iosfwd>
#include <queue>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1425. Constrained Subsequence Sum|:
//
// Given an integer array |nums| and an integer |k|, return the maximum sum of a
// non-empty subsequence of that array such that for every two consecutive
// integers in the subsequence, |nums[i]| and |nums[j]|, where |i < j|, the
// condition |j - i <= k| is satisfied. A subsequence of an array is obtained by
// deleting some number of elements (can be zero) from the array, leaving the
// remaining elements in their original order.
//
//

LEETCODE_BEGIN_RESOLVING(1425, ConstrainedSubsequenceSum, Solution);

class Solution {
public:
  int constrainedSubsetSum(vector<int> &nums, int k) {
    int                            n = nums.size();
    priority_queue<pair<int, int>> pq;
    pq.emplace(nums.front(), 0);
    vector<int> dp(n, 0);
    dp.front() = nums.front();

    int res = nums.front();
    for (int i = 1; i < n; ++i) {
      while (!pq.empty()) {
        auto p = pq.top();
        if (i - p.second > k) {
          pq.pop();
        } else {
          break;
        }
      }
      dp[i] = max(nums[i], nums[i] + pq.top().first);
      res   = max(res, dp[i]);
      pq.emplace(dp[i], i);
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= k <= nums.length <= 10⁵|
// * |-10⁴ <= nums[i] <= 10⁴|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [10,2,-10,5,20], k = 2
// Output: 37
//
// The subsequence is [10, 2, 5, 20].

LEETCODE_SOLUTION_UNITTEST(1425, ConstrainedSubsequenceSum, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {10, 2, -10, 5, 20};
  int         k        = 2;
  int         expect   = 37;
  int         actual   = solution->constrainedSubsetSum(nums, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [-1,-2,-3], k = 1
// Output: -1
//
// The subsequence must be non-empty, so we choose the largest number.

LEETCODE_SOLUTION_UNITTEST(1425, ConstrainedSubsequenceSum, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {-1, -2, -3};
  int         k        = 1;
  int         expect   = -1;
  int         actual   = solution->constrainedSubsetSum(nums, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: nums = [10,-2,-10,-5,20], k = 2
// Output: 23
//
// The subsequence is [10, -2, -5, 20].

LEETCODE_SOLUTION_UNITTEST(1425, ConstrainedSubsequenceSum, example_3) {
  auto        solution = MakeSolution();
  vector<int> nums     = {10, -2, -10, -5, 20};
  int         k        = 2;
  int         expect   = 23;
  int         actual   = solution->constrainedSubsetSum(nums, k);
  LCD_EXPECT_EQ(expect, actual);
}
