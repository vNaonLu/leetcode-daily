// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Longest Subarray With Maximum Bitwise AND
//
// https://leetcode.com/problems/longest-subarray-with-maximum-bitwise-and/
//
// Question ID: 2419
// Difficult  : Medium
// Solve Date : 2024/09/14 14:19

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2419. Longest Subarray With Maximum Bitwise AND|:
//
// You are given an integer array |nums| of size |n|.
// Consider a non-empty subarray from |nums| that has the maximum possible
// bitwise AND.
//
//  • In other words, let |k| be the maximum value of the bitwise AND of any
//  subarray of |nums|. Then, only subarrays with a bitwise AND equal to |k|
//  should be considered.
// Return the length of the longest such subarray.
// The bitwise AND of an array is the bitwise AND of all the numbers in it.
// A subarray is a contiguous sequence of elements within an array.
//
//

LEETCODE_BEGIN_RESOLVING(2419, LongestSubarrayWithMaximumBitwiseAND, Solution);

class Solution {
public:
  int longestSubarray(vector<int> &nums) {
    int  mx  = *max_element(nums.begin(), nums.end());
    int  res = 1;
    int  cnt = 0;
    auto beg = nums.begin();
    while (beg != nums.end()) {
      if (*beg == mx) {
        while (beg != nums.end() && *beg == mx) {
          ++cnt;
          ++beg;
        }
        res = max(res, cnt);
        cnt = 0;
      } else {
        ++beg;
      }
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= nums.length <= 10⁵|
// * |1 <= nums[i] <= 10⁶|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [1,2,3,3,2,2]
// Output: 2
//

LEETCODE_SOLUTION_UNITTEST(2419, LongestSubarrayWithMaximumBitwiseAND,
                           example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 2, 3, 3, 2, 2};
  int         expect   = 2;
  int         actual   = solution->longestSubarray(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [1,2,3,4]
// Output: 1
//

LEETCODE_SOLUTION_UNITTEST(2419, LongestSubarrayWithMaximumBitwiseAND,
                           example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 2, 3, 4};
  int         expect   = 1;
  int         actual   = solution->longestSubarray(nums);
  LCD_EXPECT_EQ(expect, actual);
}
