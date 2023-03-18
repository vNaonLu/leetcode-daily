// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Find Greatest Common Divisor of Array
//
// https://leetcode.com/problems/find-greatest-common-divisor-of-array/
//
// Question ID: 1979
// Difficult  : Easy
// Solve Date : 2023/03/17 13:13

#include <iosfwd>
#include <numeric>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1979. Find Greatest Common Divisor of Array|:
//
// Given an integer array |nums|, return the greatest common divisor of the
// smallest number and largest number in |nums|. The greatest common divisor of
// two numbers is the largest positive integer that evenly divides both numbers.
//

LEETCODE_BEGIN_RESOLVING(1979, FindGreatestCommonDivisorOfArray, Solution);

class Solution {
public:
  int findGCD(vector<int> &nums) {
    int mx = *max_element(nums.begin(), nums.end());
    int mn = *min_element(nums.begin(), nums.end());
    return gcd(mx, mn);
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |2 <= nums.length <= 1000|
// * |1 <= nums[i] <= 1000|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [2,5,6,9,10]
// Output: 2
//
// The smallest number in nums is 2.
// The largest number in nums is 10.
// The greatest common divisor of 2 and 10 is 2.

LEETCODE_SOLUTION_UNITTEST(1979, FindGreatestCommonDivisorOfArray, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {2, 5, 6, 9, 10};
  int         expect   = 2;
  int         actual   = solution->findGCD(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [7,5,6,8,3]
// Output: 1
//
// The smallest number in nums is 3.
// The largest number in nums is 8.
// The greatest common divisor of 3 and 8 is 1.

LEETCODE_SOLUTION_UNITTEST(1979, FindGreatestCommonDivisorOfArray, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {7, 5, 6, 8, 3};
  int         expect   = 1;
  int         actual   = solution->findGCD(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: nums = [3,3]
// Output: 3
//
// The smallest number in nums is 3.
// The largest number in nums is 3.
// The greatest common divisor of 3 and 3 is 3.

LEETCODE_SOLUTION_UNITTEST(1979, FindGreatestCommonDivisorOfArray, example_3) {
  auto        solution = MakeSolution();
  vector<int> nums     = {3, 3};
  int         expect   = 3;
  int         actual   = solution->findGCD(nums);
  LCD_EXPECT_EQ(expect, actual);
}
