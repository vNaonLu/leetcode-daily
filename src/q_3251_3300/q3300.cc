// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Minimum Element After Replacement With Digit Sum
//
// https://leetcode.com/problems/minimum-element-after-replacement-with-digit-sum/
//
// Question ID: 3300
// Difficult  : Easy
// Solve Date : 2024/10/02 12:50

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |3300. Minimum Element After Replacement With Digit Sum|:
//
// You are given an integer array |nums|.
// You replace each element in |nums| with the sum of its digits.
// Return the minimum element in |nums| after all replacements.
//
//

LEETCODE_BEGIN_RESOLVING(3300, MinimumElementAfterReplacementWithDigitSum,
                         Solution);

class Solution {
public:
  int minElement(vector<int> &nums) {
    int res = nums.front();
    for (auto x : nums) {
      res = min(res, digitSum(x));
    }
    return res;
  }

private:
  int digitSum(int x) {
    int res = 0;
    while (x) {
      res += x % 10;
      x /= 10;
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= nums.length <= 100|
// * |1 <= nums[i] <= 10⁴|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [10,12,13,14]
// Output: 1
//

LEETCODE_SOLUTION_UNITTEST(3300, MinimumElementAfterReplacementWithDigitSum,
                           example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {10, 12, 13, 14};
  int         expect   = 1;
  int         actual   = solution->minElement(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [1,2,3,4]
// Output: 1
//

LEETCODE_SOLUTION_UNITTEST(3300, MinimumElementAfterReplacementWithDigitSum,
                           example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 2, 3, 4};
  int         expect   = 1;
  int         actual   = solution->minElement(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: nums = [999,19,199]
// Output: 10
//

LEETCODE_SOLUTION_UNITTEST(3300, MinimumElementAfterReplacementWithDigitSum,
                           example_3) {
  auto        solution = MakeSolution();
  vector<int> nums     = {999, 19, 199};
  int         expect   = 10;
  int         actual   = solution->minElement(nums);
  LCD_EXPECT_EQ(expect, actual);
}
