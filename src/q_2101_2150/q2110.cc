// Copyright 2025 Naon Lu
//
// This file describes the solution of
// Number of Smooth Descent Periods of a Stock
//
// https://leetcode.com/problems/number-of-smooth-descent-periods-of-a-stock/
//
// Question ID: 2110
// Difficult  : Medium
// Solve Date : 2025/12/15 19:53

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2110. Number of Smooth Descent Periods of a Stock|:
//
// You are given an integer array |prices| representing the daily price history
// of a stock, where |prices[i]| is the stock price on the |iᵗʰ| day. A smooth
// descent period of a stock consists of one or more contiguous days such that
// the price on each day is lower than the price on the preceding day by exactly
// |1|. The first day of the period is exempted from this rule. Return the
// number of smooth descent periods.
//
//

LEETCODE_BEGIN_RESOLVING(2110, NumberOfSmoothDescentPeriodsOfAStock, Solution);

class Solution {
public:
  long long getDescentPeriods(vector<int> &prices) {
    int     n   = prices.size();
    int64_t res = 1;
    int64_t des = 1;
    for (int i = 1; i < n; ++i) {
      des = (prices[i] + 1 == prices[i - 1]) * des + 1;
      res += des;
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= prices.length <= 10⁵|
// * |1 <= prices[i] <= 10⁵|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: prices = [3,2,1,4]
// Output: 7
//

LEETCODE_SOLUTION_UNITTEST(2110, NumberOfSmoothDescentPeriodsOfAStock,
                           example_1) {
  auto        solution = MakeSolution();
  vector<int> prices   = {3, 2, 1, 4};
  long long   expect   = 7;
  long long   actual   = solution->getDescentPeriods(prices);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: prices = [8,6,7,7]
// Output: 4
//

LEETCODE_SOLUTION_UNITTEST(2110, NumberOfSmoothDescentPeriodsOfAStock,
                           example_2) {
  auto        solution = MakeSolution();
  vector<int> prices   = {8, 6, 7, 7};
  long long   expect   = 4;
  long long   actual   = solution->getDescentPeriods(prices);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: prices = [1]
// Output: 1
//

LEETCODE_SOLUTION_UNITTEST(2110, NumberOfSmoothDescentPeriodsOfAStock,
                           example_3) {
  auto        solution = MakeSolution();
  vector<int> prices   = {1};
  long long   expect   = 1;
  long long   actual   = solution->getDescentPeriods(prices);
  LCD_EXPECT_EQ(expect, actual);
}
