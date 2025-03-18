// Copyright 2025 Naon Lu
//
// This file describes the solution of
// Longest Nice Subarray
//
// https://leetcode.com/problems/longest-nice-subarray/
//
// Question ID: 2401
// Difficult  : Medium
// Solve Date : 2025/03/18 20:49

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2401. Longest Nice Subarray|:
//
// You are given an array |nums| consisting of positive integers.
// We call a subarray of |nums| nice if the bitwise AND of every pair of
// elements that are in different positions in the subarray is equal to |0|.
// Return the length of the longest nice subarray.
// A subarray is a contiguous part of an array.
// Note that subarrays of length |1| are always considered nice.
//
//

LEETCODE_BEGIN_RESOLVING(2401, LongestNiceSubarray, Solution);

class Solution {
public:
  int longestNiceSubarray(vector<int> &nums) {
    int n   = nums.size();
    int res = 1;
    int lo  = 0;
    int bit = 0;
    for (int hi = 0; hi < n; ++hi) {
      while ((bit & nums[hi]) != 0) {
        bit ^= nums[lo++];
      }

      bit |= nums[hi];
      res = max(res, hi - lo + 1);
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= nums.length <= 10⁵|
// * |1 <= nums[i] <= 10⁹|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [1,3,8,48,10]
// Output: 3
//

LEETCODE_SOLUTION_UNITTEST(2401, LongestNiceSubarray, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 3, 8, 48, 10};
  int         expect   = 3;
  int         actual   = solution->longestNiceSubarray(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [3,1,5,11,13]
// Output: 1
//

LEETCODE_SOLUTION_UNITTEST(2401, LongestNiceSubarray, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {3, 1, 5, 11, 13};
  int         expect   = 1;
  int         actual   = solution->longestNiceSubarray(nums);
  LCD_EXPECT_EQ(expect, actual);
}
