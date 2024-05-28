// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Find the XOR of Numbers Which Appear Twice
//
// https://leetcode.com/problems/find-the-xor-of-numbers-which-appear-twice/
//
// Question ID: 3158
// Difficult  : Easy
// Solve Date : 2024/05/27 22:05

#include <functional>
#include <iosfwd>
#include <numeric>
#include <unordered_set>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |3158. Find the XOR of Numbers Which Appear Twice|:
//
// You are given an array |nums|, where each number in the array appears either
// once or twice. Return the bitwise |XOR| of all the numbers that appear twice
// in the array, or 0 if no number appears twice.
//
//

LEETCODE_BEGIN_RESOLVING(3158, FindTheXOROfNumbersWhichAppearTwice, Solution);

class Solution {
public:
  int duplicateNumbersXOR(vector<int> &nums) {
    unordered_set<int> s(nums.begin(), nums.end());
    return accumulate(nums.begin(), nums.end(),
                      accumulate(s.begin(), s.end(), 0, bit_xor{}), bit_xor{});
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= nums.length <= 50|
// * |1 <= nums[i] <= 50|
// * Each number in |nums| appears either once or twice.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [1,2,1,3]
// Output: 1
//

LEETCODE_SOLUTION_UNITTEST(3158, FindTheXOROfNumbersWhichAppearTwice,
                           example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 2, 1, 3};
  int         expect   = 1;
  int         actual   = solution->duplicateNumbersXOR(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [1,2,3]
// Output: 0
//

LEETCODE_SOLUTION_UNITTEST(3158, FindTheXOROfNumbersWhichAppearTwice,
                           example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 2, 3};
  int         expect   = 0;
  int         actual   = solution->duplicateNumbersXOR(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: nums = [1,2,2,1]
// Output: 3
//

LEETCODE_SOLUTION_UNITTEST(3158, FindTheXOROfNumbersWhichAppearTwice,
                           example_3) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 2, 2, 1};
  int         expect   = 3;
  int         actual   = solution->duplicateNumbersXOR(nums);
  LCD_EXPECT_EQ(expect, actual);
}
