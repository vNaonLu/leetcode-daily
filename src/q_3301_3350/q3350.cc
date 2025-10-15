// Copyright 2025 Naon Lu
//
// This file describes the solution of
// Adjacent Increasing Subarrays Detection II
//
// https://leetcode.com/problems/adjacent-increasing-subarrays-detection-ii/
//
// Question ID: 3350
// Difficult  : Medium
// Solve Date : 2025/10/15 19:21

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |3350. Adjacent Increasing Subarrays Detection II|:
//
// Given an array |nums| of |n| integers, your task is to find the maximum value
// of |k| for which there exist two adjacent subarrays of length |k| each, such
// that both subarrays are strictly increasing. Specifically, check if there are
// two subarrays of length |k| starting at indices |a| and |b| ( |a < b|),
// where:
//
//  • Both subarrays |nums[a..a + k - 1]| and |nums[b..b + k - 1]| are strictly
//  increasing.
//
//  • The subarrays must be adjacent, meaning |b = a + k|.
// Return the maximum possible value of |k|.
// A subarray is a contiguous non-empty sequence of elements within an array.
//
//

LEETCODE_BEGIN_RESOLVING(3350, AdjacentIncreasingSubarraysDetectionII,
                         Solution);

class Solution {
public:
  int maxIncreasingSubarrays(vector<int> &nums) {
    int len  = 1;
    int prev = 0;
    int k    = 0;
    int n    = nums.size();
    for (int i = 1; i < n; ++i) {
      if (nums[i] > nums[i - 1]) {
        ++len;
      } else {
        k    = max({k, len / 2, min(len, prev)});
        prev = len;
        len  = 1;
      }
    }
    return max({k, len / 2, min(len, prev)});
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |2 <= nums.length <= 2 * 10⁵|
// * |-10⁹ <= nums[i] <= 10⁹|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [2,5,7,8,9,2,3,4,3,1]
// Output: 3
//

LEETCODE_SOLUTION_UNITTEST(3350, AdjacentIncreasingSubarraysDetectionII,
                           example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {2, 5, 7, 8, 9, 2, 3, 4, 3, 1};
  int         expect   = 3;
  int         actual   = solution->maxIncreasingSubarrays(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [1,2,3,4,4,4,4,5,6,7]
// Output: 2
//

LEETCODE_SOLUTION_UNITTEST(3350, AdjacentIncreasingSubarraysDetectionII,
                           example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 2, 3, 4, 4, 4, 4, 5, 6, 7};
  int         expect   = 2;
  int         actual   = solution->maxIncreasingSubarrays(nums);
  LCD_EXPECT_EQ(expect, actual);
}
