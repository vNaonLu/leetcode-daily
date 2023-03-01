// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Numbers At Most N Given Digit Set
//
// https://leetcode.com/problems/numbers-at-most-n-given-digit-set/
//
// Question ID: 902
// Difficult  : Hard
// Solve Date : 2021/12/18 11:35

#include <cmath>
#include <iosfwd>
#include <string>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |902. Numbers At Most N Given Digit Set|:
//
// Given an array of |digits| which is sorted in non-decreasing order. You can
// write numbers using each |digits[i]| as many times as we want. For example,
// if |digits = ['1','3','5']|, we may write numbers such as |'13'|, |'551'|,
// and |'1351315'|. Return the number of positive integers that can be generated
// that are less than or equal to a given integer |n|.  
//

LEETCODE_BEGIN_RESOLVING(902, NumbersAtMostNGivenDigitSet, Solution);

class Solution {
public:
  int atMostNGivenDigitSet(vector<string> &digits, int n) {
    string      s = to_string(n);
    int         m = s.size();
    vector<int> dp(m + 1, 0);
    dp.back() = 1;
    for (int i = m - 1; i >= 0; --i) {
      int character = s[i] - '0';
      for (string d : digits) {
        if (stoi(d) < character)
          dp[i] += pow(digits.size(), m - i - 1);
        else if (stoi(d) == character)
          dp[i] += dp[i + 1];
      }
    }
    for (int i = 1; i < m; ++i)
      dp[0] += pow(digits.size(), i);
    return dp.front();
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= digits.length <= 9|
// * |digits[i].length == 1|
// * |digits[i]| is a digit from  |'1'| to |'9'|.
// * All the values in  |digits| are unique.
// * |digits| is sorted in non-decreasing order.
// * |1 <= n <= 10⁹|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: digits = ["1","3","5","7"], n = 100
// Output: 20
//
// The 20 numbers that can be written are:
// 1, 3, 5, 7, 11, 13, 15, 17, 31, 33, 35, 37, 51, 53, 55, 57, 71, 73, 75, 77.

LEETCODE_SOLUTION_UNITTEST(902, NumbersAtMostNGivenDigitSet, example_1) {
  auto           solution = MakeSolution();
  vector<string> digits   = {"1", "3", "5", "7"};
  int            n        = 100;
  int            expect   = 20;
  int            actual   = solution->atMostNGivenDigitSet(digits, n);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: digits = ["1","4","9"], n = 1000000000
// Output: 29523
//
// We can write 3 one digit numbers, 9 two digit numbers, 27 three digit
// numbers, 81 four digit numbers, 243 five digit numbers, 729 six digit
// numbers, 2187 seven digit numbers, 6561 eight digit numbers, and 19683 nine
// digit numbers. In total, this is 29523 integers that can be written using the
// digits array.

LEETCODE_SOLUTION_UNITTEST(902, NumbersAtMostNGivenDigitSet, example_2) {
  auto           solution = MakeSolution();
  vector<string> digits   = {"1", "4", "9"};
  int            n        = 1000000000;
  int            expect   = 29523;
  int            actual   = solution->atMostNGivenDigitSet(digits, n);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: digits = ["7"], n = 8
// Output: 1
//

LEETCODE_SOLUTION_UNITTEST(902, NumbersAtMostNGivenDigitSet, example_3) {
  auto           solution = MakeSolution();
  vector<string> digits   = {"7"};
  int            n        = 8;
  int            expect   = 1;
  int            actual   = solution->atMostNGivenDigitSet(digits, n);
  LCD_EXPECT_EQ(expect, actual);
}
