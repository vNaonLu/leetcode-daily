// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Longest Subarray of 1's After Deleting One Element
//
// https://leetcode.com/problems/longest-subarray-of-1s-after-deleting-one-element/
//
// Question ID: 1493
// Difficult  : Medium
// Solve Date : 2023/07/05 14:18

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1493. Longest Subarray of 1's After Deleting One Element|:
//
// Given a binary array |nums|, you should delete one element from it.
// Return the size of the longest non-empty subarray containing only |1|'s in
// the resulting array. Return |0| if there is no such subarray.
//
//

LEETCODE_BEGIN_RESOLVING(1493, LongestSubarrayOf1SAfterDeletingOneElement,
                         Solution);

class Solution {
public:
  int longestSubarray(vector<int> &nums) {
    auto lo    = nums.begin();
    auto hi    = nums.begin();
    int  zeros = 0;
    int  res   = 0;

    while (hi != nums.end()) {
      if (*hi == 0) {
        ++zeros;
      }

      while (zeros > 1) {
        if (*lo++ == 0) {
          --zeros;
        }
      }

      res = max<int>(res, distance(lo, hi) + 1 - zeros);
      ++hi;
    }

    return res == nums.size() ? res - 1 : res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= nums.length <= 10⁵|
// * |nums[i]| is either |0| or |1|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [1,1,0,1]
// Output: 3
//
// After deleting the number in position 2, [1,1,1] contains 3 numbers with
// value of 1's.

LEETCODE_SOLUTION_UNITTEST(1493, LongestSubarrayOf1SAfterDeletingOneElement,
                           example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 1, 0, 1};
  int         expect   = 3;
  int         actual   = solution->longestSubarray(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [0,1,1,1,0,1,1,0,1]
// Output: 5
//
// After deleting the number in position 4, [0,1,1,1,1,1,0,1] longest subarray
// with value of 1's is [1,1,1,1,1].

LEETCODE_SOLUTION_UNITTEST(1493, LongestSubarrayOf1SAfterDeletingOneElement,
                           example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {0, 1, 1, 1, 0, 1, 1, 0, 1};
  int         expect   = 5;
  int         actual   = solution->longestSubarray(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: nums = [1,1,1]
// Output: 2
//
// You must delete one element.

LEETCODE_SOLUTION_UNITTEST(1493, LongestSubarrayOf1SAfterDeletingOneElement,
                           example_3) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 1, 1};
  int         expect   = 2;
  int         actual   = solution->longestSubarray(nums);
  LCD_EXPECT_EQ(expect, actual);
}
