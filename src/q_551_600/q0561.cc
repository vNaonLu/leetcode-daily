// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Array Partition
//
// https://leetcode.com/problems/array-partition/
//
// Question ID: 561
// Difficult  : Easy
// Solve Date : 2021/10/26 14:26

#include <algorithm>
#include <array>
#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |561. Array Partition|:
//
// Given an integer array |nums| of |2n| integers, group these integers into |n|
// pairs |(a₁, b₁), (a₂, b₂), ..., (aₙ, bₙ)| such that the sum of |min(aᵢ, bᵢ)|
// for all |i| is maximized. Return the maximized sum.  
//

LEETCODE_BEGIN_RESOLVING(561, ArrayPartition, Solution);

class Solution {
public:
  int arrayPairSum(vector<int> &nums) {
    int res = 0;
    int i   = 0;
    sort(nums.begin(), nums.end());
    while (i < nums.size() - 1) {
      res += nums[i++];
      ++i;
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= n <= 10⁴|
// * |nums.length == 2 * n|
// * |-10⁴ <= nums[i] <= 10⁴|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [1,4,3,2]
// Output: 4
//
// All possible pairings (ignoring the ordering of elements) are:
// 1. (1, 4), (2, 3) -> min(1, 4) + min(2, 3) = 1 + 2 = 3
// 2. (1, 3), (2, 4) -> min(1, 3) + min(2, 4) = 1 + 2 = 3
// 3. (1, 2), (3, 4) -> min(1, 2) + min(3, 4) = 1 + 3 = 4
// So the maximum possible sum is 4.

LEETCODE_SOLUTION_UNITTEST(561, ArrayPartition, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 4, 3, 2};
  int         expect   = 4;
  int         actual   = solution->arrayPairSum(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [6,2,6,5,1,2]
// Output: 9
//
// The optimal pairing is (2, 1), (2, 5), (6, 6). min(2, 1) + min(2, 5) + min(6,
// 6) = 1 + 2 + 6 = 9.

LEETCODE_SOLUTION_UNITTEST(561, ArrayPartition, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {6, 2, 6, 5, 1, 2};
  int         expect   = 9;
  int         actual   = solution->arrayPairSum(nums);
  LCD_EXPECT_EQ(expect, actual);
}
