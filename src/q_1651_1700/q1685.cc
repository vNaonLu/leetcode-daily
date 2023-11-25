// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Sum of Absolute Differences in a Sorted Array
//
// https://leetcode.com/problems/sum-of-absolute-differences-in-a-sorted-array/
//
// Question ID: 1685
// Difficult  : Medium
// Solve Date : 2023/11/25 19:19

#include <cmath>
#include <iosfwd>
#include <numeric>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1685. Sum of Absolute Differences in a Sorted Array|:
//
// You are given an integer array |nums| sorted in non-decreasing order.
// Build and return an integer array |result| with the same length as |nums|
// such that |result[i]| is equal to the summation of absolute differences
// between |nums[i]| and all the other elements in the array. In other words,
// |result[i]| is equal to |sum(|nums[i]-nums[j]|)| where |0 <= j < nums.length|
// and |j != i| (0-indexed).
//
//

LEETCODE_BEGIN_RESOLVING(1685, SumOfAbsoluteDifferencesInASortedArray,
                         Solution);

class Solution {
public:
  vector<int> getSumAbsoluteDifferences(vector<int> &nums) {
    vector<int> pre(nums.size() + 1, 0);
    vector<int> res;
    for (int i = 0; i < nums.size(); ++i) {
      pre[i + 1] = pre[i] + nums[i];
    }
    for (int i = 1; i < pre.size(); ++i) {
      res.emplace_back((nums[i - 1] * (i - 1)) - pre[i] +
                       (pre.back() - pre[i]) -
                       (nums[i - 1] * (nums.size() - 1 - i)));
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |2 <= nums.length <= 10⁵|
// * |1 <= nums[i] <= nums[i + 1] <= 10⁴|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [2,3,5]
// Output: [4,3,5]
//
// Assuming the arrays are 0-indexed, then
// result[0] = |2-2| + |2-3| + |2-5| = 0 + 1 + 3 = 4,
// result[1] = |3-2| + |3-3| + |3-5| = 1 + 0 + 2 = 3,
// result[2] = |5-2| + |5-3| + |5-5| = 3 + 2 + 0 = 5.

LEETCODE_SOLUTION_UNITTEST(1685, SumOfAbsoluteDifferencesInASortedArray,
                           example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {2, 3, 5};
  vector<int> expect   = {4, 3, 5};
  vector<int> actual   = solution->getSumAbsoluteDifferences(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [1,4,6,8,10]
// Output: [24,15,13,15,21]
//

LEETCODE_SOLUTION_UNITTEST(1685, SumOfAbsoluteDifferencesInASortedArray,
                           example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 4, 6, 8, 10};
  vector<int> expect   = {24, 15, 13, 15, 21};
  vector<int> actual   = solution->getSumAbsoluteDifferences(nums);
  LCD_EXPECT_EQ(expect, actual);
}
