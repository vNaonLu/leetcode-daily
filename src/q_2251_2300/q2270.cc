// Copyright 2025 Naon Lu
//
// This file describes the solution of
// Number of Ways to Split Array
//
// https://leetcode.com/problems/number-of-ways-to-split-array/
//
// Question ID: 2270
// Difficult  : Medium
// Solve Date : 2025/01/03 22:13

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2270. Number of Ways to Split Array|:
//
// You are given a 0-indexed integer array |nums| of length |n|.
// |nums| contains a valid split at index |i| if the following are true:
//
//  • The sum of the first |i + 1| elements is greater than or equal to the sum
//  of the last |n - i - 1| elements.
//
//  • There is at least one element to the right of |i|. That is, |0 <= i < n -
//  1|.
// Return the number of valid splits in |nums|.
//
//

LEETCODE_BEGIN_RESOLVING(2270, NumberOfWaysToSplitArray, Solution);

class Solution {
public:
  int waysToSplitArray(vector<int> &nums) {
    vector<int64_t> pre(1);
    int             res = 0;

    for (auto x : nums) {
      pre.emplace_back(pre.back() + x);
    }

    for (int i = 1; i < nums.size(); ++i) {
      if (pre[i] - pre.front() >= pre.back() - pre[i]) {
        ++res;
      }
    }

    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |2 <= nums.length <= 10⁵|
// * |-10⁵ <= nums[i] <= 10⁵|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [10,4,-8,7]
// Output: 2
//

LEETCODE_SOLUTION_UNITTEST(2270, NumberOfWaysToSplitArray, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {10, 4, -8, 7};
  int         expect   = 2;
  int         actual   = solution->waysToSplitArray(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [2,3,1,0]
// Output: 2
//

LEETCODE_SOLUTION_UNITTEST(2270, NumberOfWaysToSplitArray, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {2, 3, 1, 0};
  int         expect   = 2;
  int         actual   = solution->waysToSplitArray(nums);
  LCD_EXPECT_EQ(expect, actual);
}
