// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Subarray Sums Divisible by K
//
// https://leetcode.com/problems/subarray-sums-divisible-by-k/
//
// Question ID: 974
// Difficult  : Medium
// Solve Date : 2023/01/19 12:04

#include <array>
#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |974. Subarray Sums Divisible by K|:
//
// Given an integer array |nums| and an integer |k|, return the number of
// non-empty subarrays that have a sum divisible by |k|. A subarray is a
// contiguous part of an array.
//

LEETCODE_BEGIN_RESOLVING(974, SubarraySumsDivisibleByK, Solution);

class Solution {
public:
  int subarraysDivByK(vector<int> &nums, int k) {
    int         n = nums.size();
    vector<int> sums(k, 0);
    int         res  = 0;
    int         curr = 0;
    ++sums[0];
    for (int i = 0; i < n; ++i) {
      curr = (curr + nums[i] % k + k) % k;
      res += sums[curr];
      ++sums[curr];
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= nums.length <= 3 * 10⁴|
// * |-10⁴ <= nums[i] <= 10⁴|
// * |2 <= k <= 10⁴|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [4,5,0,-2,-3,1], k = 5
// Output: 7
//
// There are 7 subarrays with a sum divisible by k = 5:
// [4, 5, 0, -2, -3, 1], [5], [5, 0], [5, 0, -2, -3], [0], [0, -2, -3], [-2, -3]

LEETCODE_SOLUTION_UNITTEST(974, SubarraySumsDivisibleByK, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {4, 5, 0, -2, -3, 1};
  int         k        = 5;
  int         expect   = 7;
  int         actual   = solution->subarraysDivByK(nums, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [5], k = 9
// Output: 0
//

LEETCODE_SOLUTION_UNITTEST(974, SubarraySumsDivisibleByK, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {5};
  int         k        = 9;
  int         expect   = 0;
  int         actual   = solution->subarraysDivByK(nums, k);
  LCD_EXPECT_EQ(expect, actual);
}
