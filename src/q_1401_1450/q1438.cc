// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Longest Continuous Subarray With Absolute Diff Less Than or Equal to Limit
//
// https://leetcode.com/problems/longest-continuous-subarray-with-absolute-diff-less-than-or-equal-to-limit/
//
// Question ID: 1438
// Difficult  : Medium
// Solve Date : 2024/06/23 14:19

#include <deque>
#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1438. Longest Continuous Subarray With Absolute Diff Less
// Than or Equal to Limit|:
//
// Given an array of integers |nums| and an integer |limit|, return the size of
// the longest non-empty subarray such that the absolute difference between any
// two elements of this subarray is less than or equal to |limit|.
//
//

LEETCODE_BEGIN_RESOLVING(
    1438, LongestContinuousSubarrayWithAbsoluteDiffLessThanOrEqualToLimit,
    Solution);

class Solution {
public:
  int longestSubarray(vector<int> &nums, int limit) {
    deque<int> inc;
    deque<int> dec;
    int        res  = 0;
    int        left = 0;
    for (int right = 0; right < nums.size(); ++right) {
      while (!inc.empty() && nums[right] < inc.back()) {
        inc.pop_back();
      }
      inc.emplace_back(nums[right]);
      while (!dec.empty() && nums[right] > dec.back()) {
        dec.pop_back();
      }
      dec.emplace_back(nums[right]);
      while (dec.front() - inc.front() > limit) {
        if (nums[left] == dec.front()) {
          dec.pop_front();
        }
        if (nums[left] == inc.front()) {
          inc.pop_front();
        }
        ++left;
      }
      res = max(res, right - left + 1);
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= nums.length <= 10⁵|
// * |1 <= nums[i] <= 10⁹|
// * |0 <= limit <= 10⁹|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [8,2,4,7], limit = 4
// Output: 2
//

LEETCODE_SOLUTION_UNITTEST(
    1438, LongestContinuousSubarrayWithAbsoluteDiffLessThanOrEqualToLimit,
    example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {8, 2, 4, 7};
  int         limit    = 4;
  int         expect   = 2;
  int         actual   = solution->longestSubarray(nums, limit);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [10,1,2,4,7,2], limit = 5
// Output: 4
//

LEETCODE_SOLUTION_UNITTEST(
    1438, LongestContinuousSubarrayWithAbsoluteDiffLessThanOrEqualToLimit,
    example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {10, 1, 2, 4, 7, 2};
  int         limit    = 5;
  int         expect   = 4;
  int         actual   = solution->longestSubarray(nums, limit);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: nums = [4,2,2,2,4,4,2,2], limit = 0
// Output: 3
//

LEETCODE_SOLUTION_UNITTEST(
    1438, LongestContinuousSubarrayWithAbsoluteDiffLessThanOrEqualToLimit,
    example_3) {
  auto        solution = MakeSolution();
  vector<int> nums     = {4, 2, 2, 2, 4, 4, 2, 2};
  int         limit    = 0;
  int         expect   = 3;
  int         actual   = solution->longestSubarray(nums, limit);
  LCD_EXPECT_EQ(expect, actual);
}
