// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Minimum Size Subarray Sum
//
// https://leetcode.com/problems/minimum-size-subarray-sum/
//
// Question ID: 209
// Difficult  : Medium
// Solve Date : 2021/09/23 08:00

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |209. Minimum Size Subarray Sum|:
//
// Given an array of positive integers |nums| and a positive integer |target|,
// return the minimal length of a subarray whose sum is greater than or equal to
// |target|. If there is no such subarray, return |0| instead.  
//

LEETCODE_BEGIN_RESOLVING(209, MinimumSizeSubarraySum, Solution);

class Solution {
public:
  int minSubArrayLen(int target, vector<int> &nums) {
    int res = nums.size() + 1;
    int r = 0, sum = 0;
    while (sum < target && r < nums.size()) {
      sum += nums[r++];
    }
    if (sum >= target)
      res = r;
    for (int i = 0; i < nums.size(); ++i) {
      sum -= nums[i];
      while (sum < target && r < nums.size())
        sum += nums[r++];
      if (sum >= target) {
        res = min(res, r - i - 1);
      }
    }
    return res > nums.size() ? 0 : res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= target <= 10⁹|
// * |1 <= nums.length <= 10⁵|
// * |1 <= nums[i] <= 10⁴|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: target = 7, nums = [2,3,1,2,4,3]
// Output: 2
//
// The subarray [4,3] has the minimal length under the problem constraint.

LEETCODE_SOLUTION_UNITTEST(209, MinimumSizeSubarraySum, example_1) {
  auto        solution = MakeSolution();
  int         target   = 7;
  vector<int> nums     = {2, 3, 1, 2, 4, 3};
  int         expect   = 2;
  int         actual   = solution->minSubArrayLen(target, nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: target = 4, nums = [1,4,4]
// Output: 1
//

LEETCODE_SOLUTION_UNITTEST(209, MinimumSizeSubarraySum, example_2) {
  auto        solution = MakeSolution();
  int         target   = 4;
  vector<int> nums     = {1, 4, 4};
  int         expect   = 1;
  int         actual   = solution->minSubArrayLen(target, nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: target = 11, nums = [1,1,1,1,1,1,1,1]
// Output: 0
//

LEETCODE_SOLUTION_UNITTEST(209, MinimumSizeSubarraySum, example_3) {
  auto        solution = MakeSolution();
  int         target   = 11;
  vector<int> nums     = {1, 1, 1, 1, 1, 1, 1, 1};
  int         expect   = 0;
  int         actual   = solution->minSubArrayLen(target, nums);
  LCD_EXPECT_EQ(expect, actual);
}
