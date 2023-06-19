// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Buy Two Chocolates
//
// https://leetcode.com/problems/buy-two-chocolates/
//
// Question ID: 2706
// Difficult  : Easy
// Solve Date : 2023/06/14 20:04

#include <algorithm>
#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2706. Buy Two Chocolates|:
//
// You are given an integer array |prices| representing the prices of various
// chocolates in a store. You are also given a single integer |money|, which
// represents your initial amount of money. You must buy exactly two chocolates
// in such a way that you still have some non-negative leftover money. You would
// like to minimize the sum of the prices of the two chocolates you buy. Return
// the amount of money you will have leftover after buying the two chocolates.
// If there is no way for you to buy two chocolates without ending up in debt,
// return |money|. Note that the leftover must be non-negative.
//
//

LEETCODE_BEGIN_RESOLVING(2706, BuyTwoChocolates, Solution);

class Solution {
public:
  int buyChoco(vector<int> &prices, int money) {
    nth_element(prices.begin(), prices.begin(), prices.end());
    nth_element(prices.begin(), prices.begin() + 1, prices.end());
    int x = prices[0] + prices[1];
    return x > money ? money : (money - x);
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |2 <= prices.length <= 50|
// * |1 <= prices[i] <= 100|
// * |1 <= money <= 100|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: prices = [1,2,2], money = 3
// Output: 0
//
// Purchase the chocolates priced at 1 and 2 units respectively. You will have 3
// - 3 = 0 units of money afterwards. Thus, we return 0.

LEETCODE_SOLUTION_UNITTEST(2706, BuyTwoChocolates, example_1) {
  auto        solution = MakeSolution();
  vector<int> prices   = {1, 2, 2};
  int         money    = 3;
  int         expect   = 0;
  int         actual   = solution->buyChoco(prices, money);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: prices = [3,2,3], money = 3
// Output: 3
//
// You cannot buy 2 chocolates without going in debt, so we return 3.

LEETCODE_SOLUTION_UNITTEST(2706, BuyTwoChocolates, example_2) {
  auto        solution = MakeSolution();
  vector<int> prices   = {3, 2, 3};
  int         money    = 3;
  int         expect   = 3;
  int         actual   = solution->buyChoco(prices, money);
  LCD_EXPECT_EQ(expect, actual);
}

// [Extra Testcase #1]
//  Input: [98,54,6,34,66,63,52,39]
// 62
// Output: 22
//

LEETCODE_SOLUTION_UNITTEST(2706, BuyTwoChocolates, extra_testcase_1) {
  auto        solution = MakeSolution();
  vector<int> prices   = {98, 54, 6, 34, 66, 63, 52, 39};
  int         money    = 62;
  int         expect   = 22;
  int         actual   = solution->buyChoco(prices, money);
  LCD_EXPECT_EQ(expect, actual);
}
