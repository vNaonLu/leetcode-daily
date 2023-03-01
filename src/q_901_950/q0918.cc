// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Maximum Sum Circular Subarray
//
// https://leetcode.com/problems/maximum-sum-circular-subarray/
//
// Question ID: 918
// Difficult  : Medium
// Solve Date : 2021/10/14 12:48

#include <array>
#include <iosfwd>
#include <numeric>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |918. Maximum Sum Circular Subarray|:
//
// Given a circular integer array |nums| of length |n|, return the maximum
// possible sum of a non-empty subarray of |nums|. A circular array means the
// end of the array connects to the beginning of the array. Formally, the next
// element of |nums[i]| is |nums[(i + 1) % n]| and the previous element of
// |nums[i]| is |nums[(i - 1 + n) % n]|. A subarray may only include each
// element of the fixed buffer |nums| at most once. Formally, for a subarray
// |nums[i], nums[i + 1], ..., nums[j]|, there does not exist |i <= k1|, |k2 <=
// j| with |k1 % n == k2 % n|.  
//

LEETCODE_BEGIN_RESOLVING(918, MaximumSumCircularSubarray, Solution);

class Solution {
private:
  int kadane(vector<int>::iterator beg, vector<int>::iterator end, int sign) {
    if (beg == end)
      return 0;
    int res = *beg * sign, lmx = *beg * sign;
    ++beg;
    while (beg != end) {
      lmx = *(beg++) * sign + max(0, lmx);
      res = max(res, lmx);
    }
    return res;
  }

public:
  int maxSubarraySumCircular(vector<int> &nums) {
    int sum = accumulate(nums.begin(), nums.end(), 0);
    return max({kadane(nums.begin(), nums.end(), 1),
                sum + kadane(nums.begin() + 1, nums.end(), -1),
                sum + kadane(nums.begin(), nums.end() - 1, -1)});
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |n == nums.length|
// * |1 <= n <= 3 * 10⁴|
// * |-3 * 10⁴ <= nums[i] <= 3 * 10⁴|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [1,-2,3,-2]
// Output: 3
//
// Subarray [3] has maximum sum 3.

LEETCODE_SOLUTION_UNITTEST(918, MaximumSumCircularSubarray, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, -2, 3, -2};
  int         expect   = 3;
  int         actual   = solution->maxSubarraySumCircular(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [5,-3,5]
// Output: 10
//
// Subarray [5,5] has maximum sum 5 + 5 = 10.

LEETCODE_SOLUTION_UNITTEST(918, MaximumSumCircularSubarray, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {5, -3, 5};
  int         expect   = 10;
  int         actual   = solution->maxSubarraySumCircular(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: nums = [-3,-2,-3]
// Output: -2
//
// Subarray [-2] has maximum sum -2.

LEETCODE_SOLUTION_UNITTEST(918, MaximumSumCircularSubarray, example_3) {
  auto        solution = MakeSolution();
  vector<int> nums     = {-3, -2, -3};
  int         expect   = -2;
  int         actual   = solution->maxSubarraySumCircular(nums);
  LCD_EXPECT_EQ(expect, actual);
}
