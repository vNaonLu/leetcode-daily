// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Maximum Difference by Remapping a Digit
//
// https://leetcode.com/problems/maximum-difference-by-remapping-a-digit/
//
// Question ID: 2566
// Difficult  : Easy
// Solve Date : 2023/12/02 17:09

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2566. Maximum Difference by Remapping a Digit|:
//
// You are given an integer |num|. You know that Danny Mittal will sneakily
// remap one of the |10| possible digits ( |0| to |9|) to another digit. Return
// the difference between the maximum and minimum values Danny can make by
// remapping exactly one digit in |num|. Notes:
//
//  • When Danny remaps a digit d1 to another digit d2, Danny replaces all
//  occurrences of |d1| in |num| with |d2|.
//
//  • Danny can remap a digit to itself, in which case |num| does not change.
//
//  • Danny can remap different digits for obtaining minimum and maximum values
//  respectively.
//
//  • The resulting number after remapping can contain leading zeroes.
//
//  • We mentioned "Danny Mittal" to congratulate him on being in the top 10 in
//  Weekly Contest 326.
//
//

LEETCODE_BEGIN_RESOLVING(2566, MaximumDifferenceByRemappingADigit, Solution);

class Solution {
public:
  int minMaxDifference(int num) {
    vector<int> v1;
    vector<int> v2;
    while (num) {
      v1.emplace_back(num % 10);
      num /= 10;
    }
    reverse(v1.begin(), v1.end());
    v2    = v1;
    int x = 0;
    int y = 0;
    int a = v1.front();
    int b = -1;
    for (int i = 0; i < v1.size(); ++i) {
      if (b == -1 && v1[i] != 9) {
        b = v1[i];
      }
      if (v1[i] == b) {
        v1[i] = 9;
      }
      if (v2[i] == a) {
        v2[i] = 0;
      }
      x = x * 10 + v1[i];
      y = y * 10 + v2[i];
    }
    return x - y;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= num <= 10⁸|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: num = 11891
// Output: 99009
//
// To achieve the maximum value, Danny can remap the digit 1 to the digit 9 to
// yield 99899. To achieve the minimum value, Danny can remap the digit 1 to the
// digit 0, yielding 890. The difference between these two numbers is 99009.

LEETCODE_SOLUTION_UNITTEST(2566, MaximumDifferenceByRemappingADigit,
                           example_1) {
  auto solution = MakeSolution();
  int  num      = 11891;
  int  expect   = 99009;
  int  actual   = solution->minMaxDifference(num);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: num = 90
// Output: 99
//
// The maximum value that can be returned by the function is 99 (if 0 is
// replaced by 9) and the minimum value that can be returned by the function is
// 0 (if 9 is replaced by 0). Thus, we return 99.

LEETCODE_SOLUTION_UNITTEST(2566, MaximumDifferenceByRemappingADigit,
                           example_2) {
  auto solution = MakeSolution();
  int  num      = 90;
  int  expect   = 99;
  int  actual   = solution->minMaxDifference(num);
  LCD_EXPECT_EQ(expect, actual);
}
