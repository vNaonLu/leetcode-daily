// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Longest Strictly Increasing or Strictly Decreasing Subarray
//
// https://leetcode.com/problems/longest-strictly-increasing-or-strictly-decreasing-subarray/
//
// Question ID: 3105
// Difficult  : Easy
// Solve Date : 2024/04/08 22:46

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |3105. Longest Strictly Increasing or Strictly Decreasing
// Subarray|:
//
// You are given an array of integers |nums|. Return the length of the longest
// subarray of |nums| which is either strictly increasing or strictly
// decreasing.
//
//

LEETCODE_BEGIN_RESOLVING(3105,
                         LongestStrictlyIncreasingOrStrictlyDecreasingSubarray,
                         Solution);

class Solution {
public:
  int longestMonotonicSubarray(vector<int> &nums) {
    return max(longestStrictlyIncreasing(nums.begin(), nums.end()),
               longestStrictlyIncreasing(nums.rbegin(), nums.rend()));
  }

private:
  template <typename It>
  int longestStrictlyIncreasing(It beg, It end) {
    if (end == beg) {
      return 0;
    }
    int  res = 1;
    auto it  = beg + 1;
    while (it != end) {
      if (*(it - 1) >= *it) {
        beg = it;
      }
      res = max<int>(res, distance(beg, ++it));
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= nums.length <= 50|
// * |1 <= nums[i] <= 50|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [1,4,3,3,2]
// Output: 2
//

LEETCODE_SOLUTION_UNITTEST(
    3105, LongestStrictlyIncreasingOrStrictlyDecreasingSubarray, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 4, 3, 3, 2};
  int         expect   = 2;
  int         actual   = solution->longestMonotonicSubarray(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [3,3,3,3]
// Output: 1
//

LEETCODE_SOLUTION_UNITTEST(
    3105, LongestStrictlyIncreasingOrStrictlyDecreasingSubarray, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {3, 3, 3, 3};
  int         expect   = 1;
  int         actual   = solution->longestMonotonicSubarray(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: nums = [3,2,1]
// Output: 3
//

LEETCODE_SOLUTION_UNITTEST(
    3105, LongestStrictlyIncreasingOrStrictlyDecreasingSubarray, example_3) {
  auto        solution = MakeSolution();
  vector<int> nums     = {3, 2, 1};
  int         expect   = 3;
  int         actual   = solution->longestMonotonicSubarray(nums);
  LCD_EXPECT_EQ(expect, actual);
}
