// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Binary Prefix Divisible By 5
//
// https://leetcode.com/problems/binary-prefix-divisible-by-5/
//
// Question ID: 1018
// Difficult  : Easy
// Solve Date : 2022/10/28 12:14

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1018. Binary Prefix Divisible By 5|:
//
// You are given a binary array |nums| (0-indexed).
// We define |xᵢ| as the number whose binary representation is the subarray
// |nums[0..i]| (from most-significant-bit to least-significant-bit).
//
//  • For example, if |nums = [1,0,1]|, then |x₀ = 1|, |x₁ = 2|, and |x₂ = 5|.
// Return an array of booleans |answer| where |answer[i]| is |true| if |xᵢ| is
// divisible by |5|.
//

LEETCODE_BEGIN_RESOLVING(1018, BinaryPrefixDivisibleBy5, Solution);

class Solution {
public:
  vector<bool> prefixesDivBy5(vector<int> &nums) {
    auto res = vector<bool>(nums.size(), false);
    auto beg = nums.begin();
    auto rbg = res.begin();
    auto x   = 0;
    while (beg != nums.end()) {
      x    = ((x << 1) | *beg) % 5;
      *rbg = x == 0;
      ++rbg;
      ++beg;
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= nums.length <= 10⁵|
// * |nums[i]| is either |0| or |1|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [0,1,1]
// Output: [true,false,false]
//
// The input numbers in binary are 0, 01, 011; which are 0, 1, and 3 in base-10.
// Only the first number is divisible by 5, so answer[0] is true.

LEETCODE_SOLUTION_UNITTEST(1018, BinaryPrefixDivisibleBy5, example_1) {
  auto         solution = MakeSolution();
  vector<int>  nums     = {0, 1, 1};
  vector<bool> expect   = {true, false, false};
  vector<bool> actual   = solution->prefixesDivBy5(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [1,1,1]
// Output: [false,false,false]
//

LEETCODE_SOLUTION_UNITTEST(1018, BinaryPrefixDivisibleBy5, example_2) {
  auto         solution = MakeSolution();
  vector<int>  nums     = {1, 1, 1};
  vector<bool> expect   = {false, false, false};
  vector<bool> actual   = solution->prefixesDivBy5(nums);
  LCD_EXPECT_EQ(expect, actual);
}
