// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Calculate Money in Leetcode Bank
//
// https://leetcode.com/problems/calculate-money-in-leetcode-bank/
//
// Question ID: 1716
// Difficult  : Easy
// Solve Date : 2022/12/17 13:03

#include <iosfwd>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1716. Calculate Money in Leetcode Bank|:
//
// Hercy wants to save money for his first car. He puts money in the
// Leetcodebank every day. He starts by putting in |$1| on Monday, the first
// day. Every day from Tuesday to Sunday, he will put in |$1| more than the day
// before. On every subsequent Monday, he will put in |$1| more than the
// previous Monday. Given |n|, return the total amount of money he will have in
// the Leetcode bank at the end of the |nᵗʰ| day.
//

LEETCODE_BEGIN_RESOLVING(1716, CalculateMoneyInLeetcodeBank, Solution);

class Solution {
public:
  int totalMoney(int n) {
    auto m    = (n - 1) / 7;
    auto k    = (n - 1) % 7 + 1;
    int  sum1 = (28 + 28 + (m - 1) * 7) * m / 2;
    int  sum2 = (m + 1 + m + k) * k / 2;
    return sum1 + sum2;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= n <= 1000|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: n = 4
// Output: 10
//
// After the 4ᵗʰ day, the total is 1 + 2 + 3 + 4 = 10.

LEETCODE_SOLUTION_UNITTEST(1716, CalculateMoneyInLeetcodeBank, example_1) {
  auto solution = MakeSolution();
  int  n        = 4;
  int  expect   = 10;
  int  actual   = solution->totalMoney(n);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: n = 10
// Output: 37
//
// After the 10ᵗʰ day, the total is (1 + 2 + 3 + 4 + 5 + 6 + 7) + (2 + 3 + 4)
// = 37. Notice that on the 2ⁿᵈ Monday, Hercy only puts in $2.

LEETCODE_SOLUTION_UNITTEST(1716, CalculateMoneyInLeetcodeBank, example_2) {
  auto solution = MakeSolution();
  int  n        = 10;
  int  expect   = 37;
  int  actual   = solution->totalMoney(n);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: n = 20
// Output: 96
//
// After the 20ᵗʰ day, the total is (1 + 2 + 3 + 4 + 5 + 6 + 7) + (2 + 3 + 4 + 5
// + 6 + 7 + 8) + (3 + 4 + 5 + 6 + 7 + 8) = 96.

LEETCODE_SOLUTION_UNITTEST(1716, CalculateMoneyInLeetcodeBank, example_3) {
  auto solution = MakeSolution();
  int  n        = 20;
  int  expect   = 96;
  int  actual   = solution->totalMoney(n);
  LCD_EXPECT_EQ(expect, actual);
}
