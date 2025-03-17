// Copyright 2025 Naon Lu
//
// This file describes the solution of
// Maximum Absolute Sum of Any Subarray
//
// https://leetcode.com/problems/maximum-absolute-sum-of-any-subarray/
//
// Question ID: 1749
// Difficult  : Medium
// Solve Date : 2025/02/26 19:12

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1749. Maximum Absolute Sum of Any Subarray|:
//
// You are given an integer array |nums|. The absolute sum of a subarray
// |[numsₗ, numsₗ₊₁, ..., numsᵣ₋₁, numsᵣ]| is |abs(numsₗ + numsₗ₊₁ + ... +
// numsᵣ₋₁ + numsᵣ)|. Return the maximum absolute sum of any (possibly empty)
// subarray of |nums|. Note that |abs(x)| is defined as follows:
//
//  • If |x| is a negative integer, then |abs(x) = -x|.
//
//  • If |x| is a non-negative integer, then |abs(x) = x|.
//
//

LEETCODE_BEGIN_RESOLVING(1749, MaximumAbsoluteSumOfAnySubarray, Solution);

class Solution {
public:
  int maxAbsoluteSum(vector<int> &nums) {
    int mx = 0;
    int mn = 0;
    int c  = 0;
    for (auto x : nums) {
      c += x;
      mx = max(mx, c);
      mn = min(mn, c);
    }
    return abs(mx - mn);
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= nums.length <= 10⁵|
// * |-10⁴ <= nums[i] <= 10⁴|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [1,-3,2,3,-4]
// Output: 5
//

LEETCODE_SOLUTION_UNITTEST(1749, MaximumAbsoluteSumOfAnySubarray, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, -3, 2, 3, -4};
  int         expect   = 5;
  int         actual   = solution->maxAbsoluteSum(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [2,-5,1,-4,3,-2]
// Output: 8
//

LEETCODE_SOLUTION_UNITTEST(1749, MaximumAbsoluteSumOfAnySubarray, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {2, -5, 1, -4, 3, -2};
  int         expect   = 8;
  int         actual   = solution->maxAbsoluteSum(nums);
  LCD_EXPECT_EQ(expect, actual);
}
