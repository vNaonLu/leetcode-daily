// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Average Value of Even Numbers That Are Divisible by Three
//
// https://leetcode.com/problems/average-value-of-even-numbers-that-are-divisible-by-three/
//
// Question ID: 2455
// Difficult  : Easy
// Solve Date : 2023/03/13 11:06

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2455. Average Value of Even Numbers That Are Divisible by
// Three|:
//
// Given an integer array |nums| of positive integers, return the average value
// of all even integers that are divisible by |3|. Note that the average of |n|
// elements is the sum of the |n| elements divided by |n| and rounded down to
// the nearest integer.
//

LEETCODE_BEGIN_RESOLVING(2455, AverageValueOfEvenNumbersThatAreDivisibleByThree,
                         Solution);

class Solution {
public:
  int averageValue(vector<int> &nums) {
    int cnt = 0;
    int res = 0;
    for (auto x : nums) {
      if (x % 6 == 0) {
        res += x;
        ++cnt;
      }
    }
    return cnt > 0 ? res / cnt : 0;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= nums.length <= 1000|
// * |1 <= nums[i] <= 1000|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [1,3,6,10,12,15]
// Output: 9
//
// 6 and 12 are even numbers that are divisible by 3. (6 + 12) / 2 = 9.

LEETCODE_SOLUTION_UNITTEST(2455,
                           AverageValueOfEvenNumbersThatAreDivisibleByThree,
                           example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 3, 6, 10, 12, 15};
  int         expect   = 9;
  int         actual   = solution->averageValue(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [1,2,4,7,10]
// Output: 0
//
// There is no single number that satisfies the requirement, so return 0.

LEETCODE_SOLUTION_UNITTEST(2455,
                           AverageValueOfEvenNumbersThatAreDivisibleByThree,
                           example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 2, 4, 7, 10};
  int         expect   = 0;
  int         actual   = solution->averageValue(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Extra Testcase #1]
//  Input: [1,2,4,7,10]
// Output: 0
//

LEETCODE_SOLUTION_UNITTEST(2455,
                           AverageValueOfEvenNumbersThatAreDivisibleByThree,
                           extra_testcase_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 2, 4, 7, 10};
  int         expect   = 0;
  int         actual   = solution->averageValue(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Extra Testcase #2]
//  Input: [4,4,9,10]
// Output: 0
//

LEETCODE_SOLUTION_UNITTEST(2455,
                           AverageValueOfEvenNumbersThatAreDivisibleByThree,
                           extra_testcase_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {4, 4, 9, 10};
  int         expect   = 0;
  int         actual   = solution->averageValue(nums);
  LCD_EXPECT_EQ(expect, actual);
}
