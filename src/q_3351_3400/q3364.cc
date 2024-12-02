// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Minimum Positive Sum Subarray
//
// https://leetcode.com/problems/minimum-positive-sum-subarray/
//
// Question ID: 3364
// Difficult  : Easy
// Solve Date : 2024/12/02 18:49

#include <iosfwd>
#include <numeric>
#include <optional>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |3364. Minimum Positive Sum Subarray |:
//
// You are given an integer array |nums| and two integers |l| and |r|. Your task
// is to find the minimum sum of a subarray whose size is between |l| and |r|
// (inclusive) and whose sum is greater than 0. Return the minimum sum of such a
// subarray. If no such subarray exists, return -1. A subarray is a contiguous
// non-empty sequence of elements within an array.
//
//

LEETCODE_BEGIN_RESOLVING(3364, MinimumPositiveSumSubarray, Solution);

class Solution {
public:
  int minimumSumSubarray(vector<int> &nums, int l, int r) {
    optional<int> res;
    auto          lo = nums.begin();
    while (lo != nums.end() && distance(lo, nums.end()) >= l) {
      auto hi  = lo + l - 1;
      int  sum = accumulate(lo, hi, 0);
      while (hi != lo + r && hi != nums.end()) {
        sum += *hi;
        if (sum > 0) {
          res = min(res.value_or(sum), sum);
        }
        ++hi;
      }
      ++lo;
    }
    return res.value_or(-1);
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= nums.length <= 100|
// * |1 <= l <= r <= nums.length|
// * |-1000 <= nums[i] <= 1000|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [3, -2, 1, 4], l = 2, r = 3
// Output: 1
//

LEETCODE_SOLUTION_UNITTEST(3364, MinimumPositiveSumSubarray, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {3, -2, 1, 4};
  int         l        = 2;
  int         r        = 3;
  int         expect   = 1;
  int         actual   = solution->minimumSumSubarray(nums, l, r);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [-2, 2, -3, 1], l = 2, r = 3
// Output: -1
//

LEETCODE_SOLUTION_UNITTEST(3364, MinimumPositiveSumSubarray, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {-2, 2, -3, 1};
  int         l        = 2;
  int         r        = 3;
  int         expect   = -1;
  int         actual   = solution->minimumSumSubarray(nums, l, r);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: nums = [1, 2, 3, 4], l = 2, r = 4
// Output: 3
//

LEETCODE_SOLUTION_UNITTEST(3364, MinimumPositiveSumSubarray, example_3) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 2, 3, 4};
  int         l        = 2;
  int         r        = 4;
  int         expect   = 3;
  int         actual   = solution->minimumSumSubarray(nums, l, r);
  LCD_EXPECT_EQ(expect, actual);
}

// [Extra Testcase #1]
//  Input: [-11,-7,-19]
// 3
// 3
// Output: -1
//

LEETCODE_SOLUTION_UNITTEST(3364, MinimumPositiveSumSubarray, extra_testcase_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {-11, -7, -19};
  int         l        = 3;
  int         r        = 3;
  int         expect   = -1;
  int         actual   = solution->minimumSumSubarray(nums, l, r);
  LCD_EXPECT_EQ(expect, actual);
}
