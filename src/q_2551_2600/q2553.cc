// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Separate the Digits in an Array
//
// https://leetcode.com/problems/separate-the-digits-in-an-array/
//
// Question ID: 2553
// Difficult  : Easy
// Solve Date : 2023/03/15 15:44

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2553. Separate the Digits in an Array|:
//
// Given an array of positive integers |nums|, return an array |answer| that
// consists of the digits of each integer in |nums| after separating them in the
// same order they appear in |nums|. To separate the digits of an integer is to
// get all the digits it has in the same order.
//
//  • For example, for the integer |10921|, the separation of its digits is
//  |[1,0,9,2,1]|.
//

LEETCODE_BEGIN_RESOLVING(2553, SeparateTheDigitsInAnArray, Solution);

class Solution {
public:
  vector<int> separateDigits(vector<int> &nums) {
    vector<int> res;
    for (auto x : nums) {
      vector<int> digit;
      while (x > 0) {
        digit.emplace_back(x % 10);
        x /= 10;
      }
      res.insert(res.end(), digit.rbegin(), digit.rend());
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= nums.length <= 1000|
// * |1 <= nums[i] <= 10⁵|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [13,25,83,77]
// Output: [1,3,2,5,8,3,7,7]
//
// - The separation of 13 is [1,3].
// - The separation of 25 is [2,5].
// - The separation of 83 is [8,3].
// - The separation of 77 is [7,7].
// answer = [1,3,2,5,8,3,7,7]. Note that answer contains the separations in the
// same order.

LEETCODE_SOLUTION_UNITTEST(2553, SeparateTheDigitsInAnArray, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {13, 25, 83, 77};
  vector<int> expect   = {1, 3, 2, 5, 8, 3, 7, 7};
  vector<int> actual   = solution->separateDigits(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [7,1,3,9]
// Output: [7,1,3,9]
//
// The separation of each integer in nums is itself.
// answer = [7,1,3,9].

LEETCODE_SOLUTION_UNITTEST(2553, SeparateTheDigitsInAnArray, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {7, 1, 3, 9};
  vector<int> expect   = {7, 1, 3, 9};
  vector<int> actual   = solution->separateDigits(nums);
  LCD_EXPECT_EQ(expect, actual);
}
