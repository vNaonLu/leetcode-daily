// Copyright 2025 Naon Lu
//
// This file describes the solution of
// Find the Maximum Length of Valid Subsequence I
//
// https://leetcode.com/problems/find-the-maximum-length-of-valid-subsequence-i/
//
// Question ID: 3201
// Difficult  : Medium
// Solve Date : 2025/07/16 19:23

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |3201. Find the Maximum Length of Valid Subsequence I|:
//
//

LEETCODE_BEGIN_RESOLVING(3201, FindTheMaximumLengthOfValidSubsequenceI,
                         Solution);

class Solution {
public:
  int maximumLength(vector<int> &nums) {
    int odd = 0;
    int eve = 0;
    for (auto x : nums) {
      if (x & 1) {
        ++odd;
      } else {
        ++eve;
      }
    }

    int odd_dp = 0;
    int eve_dp = 0;
    for (auto x : nums) {
      if (x & 1) {
        odd_dp = max(odd_dp, eve_dp + 1);
      } else {
        eve_dp = max(eve_dp, odd_dp + 1);
      }
    }
    return max({odd, eve, odd_dp, eve_dp});
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |2 <= nums.length <= 2 * 10⁵|
// * |1 <= nums[i] <= 10⁷|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [1,2,3,4]
// Output: 4
//

LEETCODE_SOLUTION_UNITTEST(3201, FindTheMaximumLengthOfValidSubsequenceI,
                           example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 2, 3, 4};
  int         expect   = 4;
  int         actual   = solution->maximumLength(nums);
  LCD_EXPECT_EQ(expect, actual);
}
