// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Calculate Amount Paid in Taxes
//
// https://leetcode.com/problems/calculate-amount-paid-in-taxes/
//
// Question ID: 2303
// Difficult  : Easy
// Solve Date : 2023/10/20 21:43

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2303. Calculate Amount Paid in Taxes|:
//
// You are given a 0-indexed 2D integer array |brackets| where |brackets[i] =
// [upperᵢ, percentᵢ]| means that the |iᵗʰ| tax bracket has an upper bound of
// |upperᵢ| and is taxed at a rate of |percentᵢ|. The brackets are sorted by
// upper bound (i.e. |upperᵢ₋₁ < upperᵢ| for |0 < i < brackets.length|). Tax is
// calculated as follows:
//
//  • The first |upper₀| dollars earned are taxed at a rate of |percent₀|.
//
//  • The next |upper₁ - upper₀| dollars earned are taxed at a rate of
//  |percent₁|.
//
//  • The next |upper₂ - upper₁| dollars earned are taxed at a rate of
//  |percent₂|.
//
//  • And so on.
// You are given an integer |income| representing the amount of money you
// earned. Return the amount of money that you have to pay in taxes. Answers
// within |10⁻⁵| of the actual answer will be accepted.
//
//

LEETCODE_BEGIN_RESOLVING(2303, CalculateAmountPaidInTaxes, Solution);

class Solution {
public:
  double calculateTax(vector<vector<int>> &brackets, int income) {
    double res = 0;
    if (income == 0) {
      return res;
    }
    int prev = 0;
    for (int i = 0; i < brackets.size(); ++i) {
      int actual = min(brackets[i][0], income);
      res += ((actual - prev) * brackets[i][1] * 1.0) / 100.0;
      if (brackets[i][0] >= income) {
        break;
      }
      prev = brackets[i][0];
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= brackets.length <= 100|
// * |1 <= upperᵢ <= 1000|
// * |0 <= percentᵢ <= 100|
// * |0 <= income <= 1000|
// * |upperᵢ| is sorted in ascending order.
// * All the values of |upperᵢ| are unique.
// * The upper bound of the last tax bracket is greater than or equal to
// |income|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: brackets = [[3,50],[7,10],[12,25]], income = 10
// Output: 2.65000
//
// Based on your income, you have 3 dollars in the 1ˢᵗ tax bracket, 4 dollars in
// the 2ⁿᵈ tax bracket, and 3 dollars in the 3ʳᵈ tax bracket. The tax rate for
// the three tax brackets is 50%, 10%, and 25%, respectively. In total, you pay
// $3 * 50% + $4 * 10% + $3 * 25% = $2.65 in taxes.

LEETCODE_SOLUTION_UNITTEST(2303, CalculateAmountPaidInTaxes, example_1) {
  auto                solution = MakeSolution();
  vector<vector<int>> brackets = {
      { 3, 50},
      { 7, 10},
      {12, 25}
  };
  int    income = 10;
  double expect = 2.65000;
  double actual = solution->calculateTax(brackets, income);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: brackets = [[1,0],[4,25],[5,50]], income = 2
// Output: 0.25000
//
// Based on your income, you have 1 dollar in the 1ˢᵗ tax bracket and 1 dollar
// in the 2ⁿᵈ tax bracket. The tax rate for the two tax brackets is 0% and 25%,
// respectively. In total, you pay $1 * 0% + $1 * 25% = $0.25 in taxes.

LEETCODE_SOLUTION_UNITTEST(2303, CalculateAmountPaidInTaxes, example_2) {
  auto                solution = MakeSolution();
  vector<vector<int>> brackets = {
      {1,  0},
      {4, 25},
      {5, 50}
  };
  int    income = 2;
  double expect = 0.25000;
  double actual = solution->calculateTax(brackets, income);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: brackets = [[2,50]], income = 0
// Output: 0.00000
//
// You have no income to tax, so you have to pay a total of $0 in taxes.

LEETCODE_SOLUTION_UNITTEST(2303, CalculateAmountPaidInTaxes, example_3) {
  auto                solution = MakeSolution();
  vector<vector<int>> brackets = {
      {2, 50}
  };
  int    income = 0;
  double expect = 0.00000;
  double actual = solution->calculateTax(brackets, income);
  LCD_EXPECT_EQ(expect, actual);
}
