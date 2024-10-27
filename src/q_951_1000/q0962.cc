// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Maximum Width Ramp
//
// https://leetcode.com/problems/maximum-width-ramp/
//
// Question ID: 962
// Difficult  : Medium
// Solve Date : 2024/10/10 22:28

#include <iosfwd>
#include <stack>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |962. Maximum Width Ramp|:
//
// A ramp in an integer array |nums| is a pair |(i, j)| for which |i < j| and
// |nums[i] <= nums[j]|. The width of such a ramp is |j - i|. Given an integer
// array |nums|, return the maximum width of a ramp in |nums|. If there is no
// ramp in |nums|, return |0|.
//
//

LEETCODE_BEGIN_RESOLVING(962, MaximumWidthRamp, Solution);

class Solution {
public:
  int maxWidthRamp(vector<int> &nums) {
    stack<int> stk;
    int        n   = nums.size();
    int        res = 0;
    for (int i = 0; i < n; ++i) {
      if (stk.empty() || nums[stk.top()] > nums[i]) {
        stk.push(i);
      }
    }
    for (int j = n - 1; j >= 0; --j) {
      while (!stk.empty() && nums[j] >= nums[stk.top()]) {
        res = max(res, j - stk.top());
        stk.pop();
      }
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |2 <= nums.length <= 5 * 10⁴|
// * |0 <= nums[i] <= 5 * 10⁴|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [6,0,8,2,1,5]
// Output: 4
//

LEETCODE_SOLUTION_UNITTEST(962, MaximumWidthRamp, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {6, 0, 8, 2, 1, 5};
  int         expect   = 4;
  int         actual   = solution->maxWidthRamp(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [9,8,1,0,1,9,4,0,4,1]
// Output: 7
//

LEETCODE_SOLUTION_UNITTEST(962, MaximumWidthRamp, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {9, 8, 1, 0, 1, 9, 4, 0, 4, 1};
  int         expect   = 7;
  int         actual   = solution->maxWidthRamp(nums);
  LCD_EXPECT_EQ(expect, actual);
}
