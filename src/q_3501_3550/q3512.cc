// Copyright 2025 Naon Lu
//
// This file describes the solution of
// Minimum Operations to Make Array Sum Divisible by K
//
// https://leetcode.com/problems/minimum-operations-to-make-array-sum-divisible-by-k/
//
// Question ID: 3512
// Difficult  : Easy
// Solve Date : 2025/11/29 13:33

#include <iosfwd>
#include <numeric>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |3512. Minimum Operations to Make Array Sum Divisible by K|:
//
// You are given an integer array |nums| and an integer |k|. You can perform the
// following operation any number of times:
//
//  • Select an index |i| and replace |nums[i]| with |nums[i] - 1|.
// Return the minimum number of operations required to make the sum of the array
// divisible by |k|.
//
//

LEETCODE_BEGIN_RESOLVING(3512, MinimumOperationsToMakeArraySumDivisibleByK,
                         Solution);

class Solution {
public:
  int minOperations(vector<int> &nums, int k) {
    return accumulate(nums.begin(), nums.end(), 0) % k;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= nums.length <= 1000|
// * |1 <= nums[i] <= 1000|
// * |1 <= k <= 100|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [3,9,7], k = 5
// Output: 4
//

LEETCODE_SOLUTION_UNITTEST(3512, MinimumOperationsToMakeArraySumDivisibleByK,
                           example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {3, 9, 7};
  int         k        = 5;
  int         expect   = 4;
  int         actual   = solution->minOperations(nums, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [4,1,3], k = 4
// Output: 0
//

LEETCODE_SOLUTION_UNITTEST(3512, MinimumOperationsToMakeArraySumDivisibleByK,
                           example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {4, 1, 3};
  int         k        = 4;
  int         expect   = 0;
  int         actual   = solution->minOperations(nums, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: nums = [3,2], k = 6
// Output: 5
//

LEETCODE_SOLUTION_UNITTEST(3512, MinimumOperationsToMakeArraySumDivisibleByK,
                           example_3) {
  auto        solution = MakeSolution();
  vector<int> nums     = {3, 2};
  int         k        = 6;
  int         expect   = 5;
  int         actual   = solution->minOperations(nums, k);
  LCD_EXPECT_EQ(expect, actual);
}
