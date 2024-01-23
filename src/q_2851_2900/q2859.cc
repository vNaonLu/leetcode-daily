// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Sum of Values at Indices With K Set Bits
//
// https://leetcode.com/problems/sum-of-values-at-indices-with-k-set-bits/
//
// Question ID: 2859
// Difficult  : Easy
// Solve Date : 2024/01/19 20:53

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2859. Sum of Values at Indices With K Set Bits|:
//
// You are given a 0-indexed integer array |nums| and an integer |k|.
// Return an integer that denotes the sum of elements in |nums| whose
// corresponding indices have exactly |k| set bits in their binary
// representation. The set bits in an integer are the |1|'s present when it is
// written in binary.
//
//  • For example, the binary representation of |21| is |10101|, which has |3|
//  set bits.
//
//

LEETCODE_BEGIN_RESOLVING(2859, SumOfValuesAtIndicesWithKSetBits, Solution);

class Solution {
public:
  int sumIndicesWithKSetBits(vector<int> &nums, int k) {
    int res = 0;
    for (int i = 0; i < nums.size(); ++i) {
      if (__builtin_popcount(i) == k) {
        res += nums[i];
      }
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= nums.length <= 1000|
// * |1 <= nums[i] <= 10⁵|
// * |0 <= k <= 10|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [5,10,1,5,2], k = 1
// Output: 13
//
// The binary representation of the indices are:
// 0 = 000₂
// 1 = 001₂
// 2 = 010₂
// 3 = 011₂
// 4 = 100_{2
// }Indices 1, 2, and 4 have k = 1 set bits in their binary representation.
// Hence, the answer is nums[1] + nums[2] + nums[4] = 13.

LEETCODE_SOLUTION_UNITTEST(2859, SumOfValuesAtIndicesWithKSetBits, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {5, 10, 1, 5, 2};
  int         k        = 1;
  int         expect   = 13;
  int         actual   = solution->sumIndicesWithKSetBits(nums, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [4,3,2,1], k = 2
// Output: 1
//
// The binary representation of the indices are:
// 0 = 00₂
// 1 = 01₂
// 2 = 10₂
// 3 = 11_{2
// }Only index 3 has k = 2 set bits in its binary representation.
// Hence, the answer is nums[3] = 1.

LEETCODE_SOLUTION_UNITTEST(2859, SumOfValuesAtIndicesWithKSetBits, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {4, 3, 2, 1};
  int         k        = 2;
  int         expect   = 1;
  int         actual   = solution->sumIndicesWithKSetBits(nums, k);
  LCD_EXPECT_EQ(expect, actual);
}
