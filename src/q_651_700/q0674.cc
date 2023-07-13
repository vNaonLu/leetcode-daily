// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Longest Continuous Increasing Subsequence
//
// https://leetcode.com/problems/longest-continuous-increasing-subsequence/
//
// Question ID: 674
// Difficult  : Easy
// Solve Date : 2023/07/13 14:34

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |674. Longest Continuous Increasing Subsequence|:
//
// Given an unsorted array of integers |nums|, return the length of the longest
// continuous increasing subsequence (i.e. subarray). The subsequence must be
// strictly increasing. A continuous increasing subsequence is defined by two
// indices |l| and |r| ( |l < r|) such that it is |[nums[l], nums[l + 1], ...,
// nums[r - 1], nums[r]]| and for each |l <= i < r|, |nums[i] < nums[i + 1]|.
//
//

LEETCODE_BEGIN_RESOLVING(674, LongestContinuousIncreasingSubsequence, Solution);

class Solution {
public:
  int findLengthOfLCIS(vector<int> &nums) {
    int res = 1;
    int len = 1;
    for (int i = 1; i < nums.size(); ++i) {
      if (nums[i] > nums[i - 1]) {
        ++len;
      } else {
        len = 1;
      }
      res = max(res, len);
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= nums.length <= 10⁴|
// * |-10⁹ <= nums[i] <= 10⁹|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [1,3,5,4,7]
// Output: 3
//
// The longest continuous increasing subsequence is [1,3,5] with length 3.
// Even though [1,3,5,7] is an increasing subsequence, it is not continuous as
// elements 5 and 7 are separated by element 4.

LEETCODE_SOLUTION_UNITTEST(674, LongestContinuousIncreasingSubsequence,
                           example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 3, 5, 4, 7};
  int         expect   = 3;
  int         actual   = solution->findLengthOfLCIS(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [2,2,2,2,2]
// Output: 1
//
// The longest continuous increasing subsequence is [2] with length 1. Note that
// it must be strictly increasing.

LEETCODE_SOLUTION_UNITTEST(674, LongestContinuousIncreasingSubsequence,
                           example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {2, 2, 2, 2, 2};
  int         expect   = 1;
  int         actual   = solution->findLengthOfLCIS(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Extra Testcase #1]
//  Input: [1]
// Output: 1
//

LEETCODE_SOLUTION_UNITTEST(674, LongestContinuousIncreasingSubsequence,
                           extra_testcase_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1};
  int         expect   = 1;
  int         actual   = solution->findLengthOfLCIS(nums);
  LCD_EXPECT_EQ(expect, actual);
}
