// Copyright 2025 Naon Lu
//
// This file describes the solution of
// Count Partitions With Max-Min Difference at Most K
//
// https://leetcode.com/problems/count-partitions-with-max-min-difference-at-most-k/
//
// Question ID: 3578
// Difficult  : Medium
// Solve Date : 2025/12/06 21:46

#include <deque>
#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |3578. Count Partitions With Max-Min Difference at Most K|:
//
// You are given an integer array |nums| and an integer |k|. Your task is to
// partition |nums| into one or more non-empty contiguous segments such that in
// each segment, the difference between its maximum and minimum elements is at
// most |k|. Return the total number of ways to partition |nums| under this
// condition. Since the answer may be too large, return it modulo |10⁹ + 7|.
//
//

LEETCODE_BEGIN_RESOLVING(3578, CountPartitionsWithMaxMinDifferenceAtMostK,
                         Solution);

class Solution {
public:
  int countPartitions(vector<int> &nums, int k) {
    int       n    = nums.size();
    const int kMod = 1e9 + 7;

    vector<long long> dp(n + 1, 0);
    dp[0] = 1;

    deque<int> mx, mn;
    int        l   = 0;
    long long  sum = 0;

    for (int r = 0; r < n; r++) {
      while (!mx.empty() && nums[mx.back()] <= nums[r])
        mx.pop_back();
      while (!mn.empty() && nums[mn.back()] >= nums[r])
        mn.pop_back();
      mx.push_back(r);
      mn.push_back(r);

      while (nums[mx.front()] - nums[mn.front()] > k) {
        if (mx.front() == l)
          mx.pop_front();
        if (mn.front() == l)
          mn.pop_front();
        sum = (sum - dp[l] + kMod) % kMod;
        l++;
      }

      sum       = (sum + dp[r]) % kMod;
      dp[r + 1] = sum;
    }
    return dp[n];
  }
};
LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |2 <= nums.length <= 5 * 10⁴|
// * |1 <= nums[i] <= 10⁹|
// * |0 <= k <= 10⁹|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [9,4,1,3,7], k = 4
// Output: 6
//

LEETCODE_SOLUTION_UNITTEST(3578, CountPartitionsWithMaxMinDifferenceAtMostK,
                           example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {9, 4, 1, 3, 7};
  int         k        = 4;
  int         expect   = 6;
  int         actual   = solution->countPartitions(nums, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [3,3,4], k = 0
// Output: 2
//

LEETCODE_SOLUTION_UNITTEST(3578, CountPartitionsWithMaxMinDifferenceAtMostK,
                           example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {3, 3, 4};
  int         k        = 0;
  int         expect   = 2;
  int         actual   = solution->countPartitions(nums, k);
  LCD_EXPECT_EQ(expect, actual);
}
