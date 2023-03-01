// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Maximum Sum of Two Non-Overlapping Subarrays
//
// https://leetcode.com/problems/maximum-sum-of-two-non-overlapping-subarrays/
//
// Question ID: 1031
// Difficult  : Medium
// Solve Date : 2022/02/17 18:37

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1031. Maximum Sum of Two Non-Overlapping Subarrays|:
//
// Given an integer array |nums| and two integers |firstLen| and |secondLen|,
// return the maximum sum of elements in two non-overlapping subarrays with
// lengths |firstLen| and |secondLen|. The array with length |firstLen| could
// occur before or after the array with length |secondLen|, but they have to be
// non-overlapping. A subarray is a contiguous part of an array.  
//

LEETCODE_BEGIN_RESOLVING(1031, MaximumSumOfTwoNonOverlappingSubarrays,
                         Solution);

class Solution {
private:
  int impl(vector<int> &nums, int f, int s) noexcept {
    int res = 0, first_window = 0;
    for (int i = 0; (i + f + s - 1) < nums.size(); ++i) {
      int second_window =
          nums[i + f + s - 1] - (i + f - 1 >= 0 ? nums[i + f - 1] : 0);
      first_window =
          max(first_window, nums[i + f - 1] - (i - 1 >= 0 ? nums[i - 1] : 0));
      res = max(res, first_window + second_window);
    }
    return res;
  }

public:
  int maxSumTwoNoOverlap(vector<int> &nums, int firstLen, int secondLen) {
    for (int i = 1; i < nums.size(); ++i)
      nums[i] += nums[i - 1];
    return max(impl(nums, firstLen, secondLen),
               impl(nums, secondLen, firstLen));
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= firstLen, secondLen <= 1000|
// * |2 <= firstLen + secondLen <= 1000|
// * |firstLen + secondLen <= nums.length <= 1000|
// * |0 <= nums[i] <= 1000|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [0,6,5,2,2,5,1,9,4], firstLen = 1, secondLen = 2
// Output: 20
//
// One choice of subarrays is [9] with length 1, and [6,5] with length 2.

LEETCODE_SOLUTION_UNITTEST(1031, MaximumSumOfTwoNonOverlappingSubarrays,
                           example_1) {
  auto        solution  = MakeSolution();
  vector<int> nums      = {0, 6, 5, 2, 2, 5, 1, 9, 4};
  int         firstLen  = 1;
  int         secondLen = 2;
  int         expect    = 20;
  int         actual = solution->maxSumTwoNoOverlap(nums, firstLen, secondLen);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [3,8,1,3,2,1,8,9,0], firstLen = 3, secondLen = 2
// Output: 29
//
// One choice of subarrays is [3,8,1] with length 3, and [8,9] with length 2.

LEETCODE_SOLUTION_UNITTEST(1031, MaximumSumOfTwoNonOverlappingSubarrays,
                           example_2) {
  auto        solution  = MakeSolution();
  vector<int> nums      = {3, 8, 1, 3, 2, 1, 8, 9, 0};
  int         firstLen  = 3;
  int         secondLen = 2;
  int         expect    = 29;
  int         actual = solution->maxSumTwoNoOverlap(nums, firstLen, secondLen);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: nums = [2,1,5,6,0,9,5,0,3,8], firstLen = 4, secondLen = 3
// Output: 31
//
// One choice of subarrays is [5,6,0,9] with length 4, and [0,3,8] with
// length 3.

LEETCODE_SOLUTION_UNITTEST(1031, MaximumSumOfTwoNonOverlappingSubarrays,
                           example_3) {
  auto        solution  = MakeSolution();
  vector<int> nums      = {2, 1, 5, 6, 0, 9, 5, 0, 3, 8};
  int         firstLen  = 4;
  int         secondLen = 3;
  int         expect    = 31;
  int         actual = solution->maxSumTwoNoOverlap(nums, firstLen, secondLen);
  LCD_EXPECT_EQ(expect, actual);
}
