// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Longest Alternating Subarray
//
// https://leetcode.com/problems/longest-alternating-subarray/
//
// Question ID: 2765
// Difficult  : Easy
// Solve Date : 2023/12/27 19:05

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2765. Longest Alternating Subarray|:
//
// You are given a 0-indexed integer array |nums|. A subarray |s| of length |m|
// is called alternating if:
//
//  • |m| is greater than |1|.
//
//  • |s₁ = s₀ + 1|.
//
//  • The 0-indexed subarray |s| looks like |[s₀, s₁, s₀, s₁,...,s_{(m-1) %
//  2}]|. In other words, |s₁ - s₀ = 1|, |s₂ - s₁ = -1|, |s₃ - s₂ = 1|, |s₄ - s₃
//  = -1|, and so on up to |s[m - 1] - s[m - 2] = (-1)ᵐ|.
// Return the maximum length of all alternating subarrays present in |nums| or
// |-1| if no such subarray exists. A subarray is a contiguous non-empty
// sequence of elements within an array.
//
//

LEETCODE_BEGIN_RESOLVING(2765, LongestAlternatingSubarray, Solution);

class Solution {
public:
  int alternatingSubarray(vector<int> &nums) {
    int         n = nums.size();
    vector<int> inc(n, 1);
    vector<int> dec(n, 1);
    int         res = 1;
    for (int i = 1; i < n; ++i) {
      if (nums[i] == nums[i - 1] + 1) {
        inc[i] = dec[i - 1] + 1;
      } else if (nums[i] == nums[i - 1] - 1) {
        dec[i] = (inc[i - 1] > 1 ? inc[i - 1] + 1 : 1);
      }
      res = max({res, inc[i], dec[i]});
    }
    return res > 1 ? res : -1;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |2 <= nums.length <= 100|
// * |1 <= nums[i] <= 10⁴|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [2,3,4,3,4]
// Output: 4
//
// The alternating subarrays are [3,4], [3,4,3], and [3,4,3,4]. The longest of
// these is [3,4,3,4], which is of length 4.

LEETCODE_SOLUTION_UNITTEST(2765, LongestAlternatingSubarray, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {2, 3, 4, 3, 4};
  int         expect   = 4;
  int         actual   = solution->alternatingSubarray(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [4,5,6]
// Output: 2
//
// [4,5] and [5,6] are the only two alternating subarrays. They are both of
// length 2.

LEETCODE_SOLUTION_UNITTEST(2765, LongestAlternatingSubarray, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {4, 5, 6};
  int         expect   = 2;
  int         actual   = solution->alternatingSubarray(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Extra Testcase #1]
//  Input: [2,3,4,3,4]
// Output: 4
//

LEETCODE_SOLUTION_UNITTEST(2765, LongestAlternatingSubarray, extra_testcase_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {2, 3, 4, 3, 4};
  int         expect   = 4;
  int         actual   = solution->alternatingSubarray(nums);
  LCD_EXPECT_EQ(expect, actual);
}
