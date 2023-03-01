// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Minimum Average Difference
//
// https://leetcode.com/problems/minimum-average-difference/
//
// Question ID: 2256
// Difficult  : Medium
// Solve Date : 2022/12/04 13:55

#include <iosfwd>
#include <limits>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2256. Minimum Average Difference|:
//
// You are given a 0-indexed integer array |nums| of length |n|.
// The average difference of the index |i| is the absolute difference between
// the average of the first |i + 1| elements of |nums| and the average of the
// last |n - i - 1| elements. Both averages should be rounded down to the
// nearest integer. Return the index with the minimum average difference. If
// there are multiple such indices, return the smallest one. Note:
//
//  • The absolute difference of two numbers is the absolute value of their
//  difference.
//
//  • The average of |n| elements is the sum of the |n| elements divided
//  (integer division) by |n|.
//
//  • The average of |0| elements is considered to be |0|.
//

LEETCODE_BEGIN_RESOLVING(2256, MinimumAverageDifference, Solution);

class Solution {
public:
  int minimumAverageDifference(vector<int> &nums) {
    auto n      = nums.size();
    auto res    = (int64_t)-1;
    auto md     = numeric_limits<int64_t>::max();
    auto prefix = vector<int64_t>(n, 0);
    for (int i = 0; i < n; ++i) {
      prefix[i] = nums[i] + (i == 0 ? 0 : prefix[i - 1]);
    }
    for (int i = 0; i < n; ++i) {
      auto p1   = prefix[i];
      auto p2   = prefix[n - 1] - prefix[i];
      auto diff = abs(p1 / (int64_t)(i + 1) -
                      ((i == n - 1) ? 0 : p2 / (int64_t)(n - i - 1)));
      if (diff < md) {
        res = i;
        md  = diff;
      }
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= nums.length <= 10⁵|
// * |0 <= nums[i] <= 10⁵|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [2,5,3,9,5,3]
// Output: 3
//
// - The average difference of index 0 is: |2 / 1 - (5 + 3 + 9 + 5 + 3) / 5| =
// |2 / 1 - 25 / 5| = |2 - 5| = 3.
// - The average difference of index 1 is: |(2 + 5) / 2 - (3 + 9 + 5 + 3) / 4| =
// |7 / 2 - 20 / 4| = |3 - 5| = 2.
// - The average difference of index 2 is: |(2 + 5 + 3) / 3 - (9 + 5 + 3) / 3| =
// |10 / 3 - 17 / 3| = |3 - 5| = 2.
// - The average difference of index 3 is: |(2 + 5 + 3 + 9) / 4 - (5 + 3) / 2| =
// |19 / 4 - 8 / 2| = |4 - 4| = 0.
// - The average difference of index 4 is: |(2 + 5 + 3 + 9 + 5) / 5 - 3 / 1| =
// |24 / 5 - 3 / 1| = |4 - 3| = 1.
// - The average difference of index 5 is: |(2 + 5 + 3 + 9 + 5 + 3) / 6 - 0| =
// |27 / 6 - 0| = |4 - 0| = 4. The average difference of index 3 is the minimum
// average difference so return 3.

LEETCODE_SOLUTION_UNITTEST(2256, MinimumAverageDifference, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {2, 5, 3, 9, 5, 3};
  int         expect   = 3;
  int         actual   = solution->minimumAverageDifference(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [0]
// Output: 0
//
// The only index is 0 so return 0.
// The average difference of index 0 is: |0 / 1 - 0| = |0 - 0| = 0.

LEETCODE_SOLUTION_UNITTEST(2256, MinimumAverageDifference, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {0};
  int         expect   = 0;
  int         actual   = solution->minimumAverageDifference(nums);
  LCD_EXPECT_EQ(expect, actual);
}
