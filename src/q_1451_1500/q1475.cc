// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Final Prices With a Special Discount in a Shop
//
// https://leetcode.com/problems/final-prices-with-a-special-discount-in-a-shop/
//
// Question ID: 1475
// Difficult  : Easy
// Solve Date : 2023/08/21 19:05

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1475. Final Prices With a Special Discount in a Shop|:
//
// You are given an integer array |prices| where |prices[i]| is the price of the
// |iᵗʰ| item in a shop. There is a special discount for items in the shop. If
// you buy the |iᵗʰ| item, then you will receive a discount equivalent to
// |prices[j]| where |j| is the minimum index such that |j > i| and |prices[j]
// <= prices[i]|. Otherwise, you will not receive any discount at all. Return an
// integer array |answer| where |answer[i]| is the final price you will pay for
// the |iᵗʰ| item of the shop, considering the special discount.
//
//

LEETCODE_BEGIN_RESOLVING(1475, FinalPricesWithASpecialDiscountInAShop,
                         Solution);

class Solution {
public:
  vector<int> finalPrices(vector<int> &prices) {
    vector<int> stk;
    int         n = prices.size();
    for (int i = 0; i < n; ++i) {
      while (!stk.empty() && prices[stk.back()] >= prices[i]) {
        prices[stk.back()] -= prices[i];
        stk.pop_back();
      }
      stk.emplace_back(i);
    }
    return prices;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= prices.length <= 500|
// * |1 <= prices[i] <= 1000|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: prices = [8,4,6,2,3]
// Output: [4,2,4,2,3]
//
// For item 0 with price[0]=8 you will receive a discount equivalent to
// prices[1]=4, therefore, the final price you will pay is 8 - 4 = 4. For item 1
// with price[1]=4 you will receive a discount equivalent to prices[3]=2,
// therefore, the final price you will pay is 4 - 2 = 2. For item 2 with
// price[2]=6 you will receive a discount equivalent to prices[3]=2, therefore,
// the final price you will pay is 6 - 2 = 4. For items 3 and 4 you will not
// receive any discount at all.

LEETCODE_SOLUTION_UNITTEST(1475, FinalPricesWithASpecialDiscountInAShop,
                           example_1) {
  auto        solution = MakeSolution();
  vector<int> prices   = {8, 4, 6, 2, 3};
  vector<int> expect   = {4, 2, 4, 2, 3};
  vector<int> actual   = solution->finalPrices(prices);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: prices = [1,2,3,4,5]
// Output: [1,2,3,4,5]
//
// In this case, for all items, you will not receive any discount at all.

LEETCODE_SOLUTION_UNITTEST(1475, FinalPricesWithASpecialDiscountInAShop,
                           example_2) {
  auto        solution = MakeSolution();
  vector<int> prices   = {1, 2, 3, 4, 5};
  vector<int> expect   = {1, 2, 3, 4, 5};
  vector<int> actual   = solution->finalPrices(prices);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: prices = [10,1,1,6]
// Output: [9,0,1,6]
//

LEETCODE_SOLUTION_UNITTEST(1475, FinalPricesWithASpecialDiscountInAShop,
                           example_3) {
  auto        solution = MakeSolution();
  vector<int> prices   = {10, 1, 1, 6};
  vector<int> expect   = {9, 0, 1, 6};
  vector<int> actual   = solution->finalPrices(prices);
  LCD_EXPECT_EQ(expect, actual);
}
