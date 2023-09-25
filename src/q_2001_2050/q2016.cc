// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Maximum Difference Between Increasing Elements
//
// https://leetcode.com/problems/maximum-difference-between-increasing-elements/
//
// Question ID: 2016
// Difficult  : Easy
// Solve Date : 2023/09/21 19:00

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2016. Maximum Difference Between Increasing Elements|:
//
// Given a 0-indexed integer array |nums| of size |n|, find the maximum
// difference between |nums[i]| and |nums[j]| (i.e., |nums[j] - nums[i]|), such
// that |0 <= i < j < n| and |nums[i] < nums[j]|. Return the maximum difference.
// If no such |i| and |j| exists, return |-1|.
//
//

LEETCODE_BEGIN_RESOLVING(2016, MaximumDifferenceBetweenIncreasingElements,
                         Solution);

class Solution {
public:
  int maximumDifference(vector<int> &nums) {
    int res = -1;
    int mn  = nums.front();
    for (auto x : nums) {
      if (x > mn) {
        res = max(res, x - mn);
      } else {
        mn = min(x, mn);
      }
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |n == nums.length|
// * |2 <= n <= 1000|
// * |1 <= nums[i] <= 10⁹|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [7,1,5,4]
// Output: 4
//
// The maximum difference occurs with i = 1 and j = 2, nums[j] - nums[i] = 5 - 1
// = 4. Note that with i = 1 and j = 0, the difference nums[j] - nums[i] = 7 - 1
// = 6, but i > j, so it is not valid.

LEETCODE_SOLUTION_UNITTEST(2016, MaximumDifferenceBetweenIncreasingElements,
                           example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {7, 1, 5, 4};
  int         expect   = 4;
  int         actual   = solution->maximumDifference(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [9,4,3,2]
// Output: -1
//
// There is no i and j such that i < j and nums[i] < nums[j].

LEETCODE_SOLUTION_UNITTEST(2016, MaximumDifferenceBetweenIncreasingElements,
                           example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {9, 4, 3, 2};
  int         expect   = -1;
  int         actual   = solution->maximumDifference(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: nums = [1,5,2,10]
// Output: 9
//
// The maximum difference occurs with i = 0 and j = 3, nums[j] - nums[i] = 10 -
// 1 = 9.

LEETCODE_SOLUTION_UNITTEST(2016, MaximumDifferenceBetweenIncreasingElements,
                           example_3) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 5, 2, 10};
  int         expect   = 9;
  int         actual   = solution->maximumDifference(nums);
  LCD_EXPECT_EQ(expect, actual);
}
