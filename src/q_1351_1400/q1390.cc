// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Four Divisors
//
// https://leetcode.com/problems/four-divisors/
//
// Question ID: 1390
// Difficult  : Medium
// Solve Date : 2022/02/12 16:48

#include <iosfwd>
#include <cmath>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1390. Four Divisors|:
//
// Given an integer array |nums|, return the sum of divisors of the integers in
// that array that have exactly four divisors. If there is no such integer in
// the array, return |0|.  
//

LEETCODE_BEGIN_RESOLVING(1390, FourDivisors, Solution);

class Solution {
private:
  int fillSum(int x) {
    int count = 0, local = 0;
    for (int i = 1; i <= sqrt(x); ++i) {
      if (x % i == 0) {
        ++count;
        local += i;
        if (x / i != i) {
          ++count;
          local += x / i;
        }
      }
    }
    return count == 4 ? local : 0;
  }

public:
  int sumFourDivisors(vector<int> &nums) {
    vector<int> table(*max_element(nums.begin(), nums.end()) + 1, -1);
    int         res = 0;
    for (const auto &x : nums) {
      if (table[x] == -1) {
        table[x] = fillSum(x);
      }
      res += table[x];
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= nums.length <= 10⁴|
// * |1 <= nums[i] <= 10⁵|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [21,4,7]
// Output: 32
//
// 21 has 4 divisors: 1, 3, 7, 21
// 4 has 3 divisors: 1, 2, 4
// 7 has 2 divisors: 1, 7
// The answer is the sum of divisors of 21 only.

LEETCODE_SOLUTION_UNITTEST(1390, FourDivisors, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {21, 4, 7};
  int         expect   = 32;
  int         actual   = solution->sumFourDivisors(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [21,21]
// Output: 64
//

LEETCODE_SOLUTION_UNITTEST(1390, FourDivisors, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {21, 21};
  int         expect   = 64;
  int         actual   = solution->sumFourDivisors(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: nums = [1,2,3,4,5]
// Output: 0
//

LEETCODE_SOLUTION_UNITTEST(1390, FourDivisors, example_3) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 2, 3, 4, 5};
  int         expect   = 0;
  int         actual   = solution->sumFourDivisors(nums);
  LCD_EXPECT_EQ(expect, actual);
}
