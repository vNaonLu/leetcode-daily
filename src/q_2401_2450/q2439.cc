// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Minimize Maximum of Array
//
// https://leetcode.com/problems/minimize-maximum-of-array/
//
// Question ID: 2439
// Difficult  : Medium
// Solve Date : 2023/04/05 12:02

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2439. Minimize Maximum of Array|:
//
// You are given a 0-indexed array |nums| comprising of |n| non-negative
// integers. In one operation, you must:
//
//  • Choose an integer |i| such that |1 <= i < n| and |nums[i] > 0|.
//
//  • Decrease |nums[i]| by 1.
//
//  • Increase |nums[i - 1]| by 1.
// Return the minimum possible value of the maximum integer of |nums| after
// performing any number of operations.
//
//

LEETCODE_BEGIN_RESOLVING(2439, MinimizeMaximumOfArray, Solution);

class Solution {
public:
  int minimizeArrayValue(vector<int> &nums) {
    int64_t sum = 0;
    int64_t res = 0;
    for (int i = 0; i < nums.size(); ++i) {
      sum += nums[i];
      res = max(res, (sum + i) / (i + 1));
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |n == nums.length|
// * |2 <= n <= 10⁵|
// * |0 <= nums[i] <= 10⁹|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [3,7,1,6]
// Output: 5
//
// One set of optimal operations is as follows:
// 1. Choose i = 1, and nums becomes [4,6,1,6].
// 2. Choose i = 3, and nums becomes [4,6,2,5].
// 3. Choose i = 1, and nums becomes [5,5,2,5].
// The maximum integer of nums is 5. It can be shown that the maximum number
// cannot be less than 5. Therefore, we return 5.

LEETCODE_SOLUTION_UNITTEST(2439, MinimizeMaximumOfArray, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {3, 7, 1, 6};
  int         expect   = 5;
  int         actual   = solution->minimizeArrayValue(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [10,1]
// Output: 10
//
// It is optimal to leave nums as is, and since 10 is the maximum value, we
// return 10.

LEETCODE_SOLUTION_UNITTEST(2439, MinimizeMaximumOfArray, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {10, 1};
  int         expect   = 10;
  int         actual   = solution->minimizeArrayValue(nums);
  LCD_EXPECT_EQ(expect, actual);
}
