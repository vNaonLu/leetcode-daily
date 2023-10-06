// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Minimum Cost of Buying Candies With Discount
//
// https://leetcode.com/problems/minimum-cost-of-buying-candies-with-discount/
//
// Question ID: 2144
// Difficult  : Easy
// Solve Date : 2023/10/06 18:53

#include <algorithm>
#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2144. Minimum Cost of Buying Candies With Discount|:
//
// A shop is selling candies at a discount. For every two candies sold, the shop
// gives a third candy for free. The customer can choose any candy to take away
// for free as long as the cost of the chosen candy is less than or equal to the
// minimum cost of the two candies bought.
//
//  • For example, if there are |4| candies with costs |1|, |2|, |3|, and |4|,
//  and the customer buys candies with costs |2| and |3|, they can take the
//  candy with cost |1| for free, but not the candy with cost |4|.
// Given a 0-indexed integer array |cost|, where |cost[i]| denotes the cost of
// the |iᵗʰ| candy, return the minimum cost of buying all the candies.
//
//

LEETCODE_BEGIN_RESOLVING(2144, MinimumCostOfBuyingCandiesWithDiscount,
                         Solution);

class Solution {
public:
  int minimumCost(vector<int> &cost) {
    sort(cost.begin(), cost.end(), greater<int>{});
    int  res = 0;
    auto beg = cost.begin();
    while (beg != cost.end()) {
      res += *beg++;
      if (beg != cost.end()) {
        res += *beg++;
      }
      if (beg != cost.end()) {
        // free
        ++beg;
      }
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= cost.length <= 100|
// * |1 <= cost[i] <= 100|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: cost = [1,2,3]
// Output: 5
//
// We buy the candies with costs 2 and 3, and take the candy with cost 1 for
// free. The total cost of buying all candies is 2 + 3 = 5. This is the only way
// we can buy the candies. Note that we cannot buy candies with costs 1 and 3,
// and then take the candy with cost 2 for free. The cost of the free candy has
// to be less than or equal to the minimum cost of the purchased candies.

LEETCODE_SOLUTION_UNITTEST(2144, MinimumCostOfBuyingCandiesWithDiscount,
                           example_1) {
  auto        solution = MakeSolution();
  vector<int> cost     = {1, 2, 3};
  int         expect   = 5;
  int         actual   = solution->minimumCost(cost);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: cost = [6,5,7,9,2,2]
// Output: 23
//
// The way in which we can get the minimum cost is described below:
// - Buy candies with costs 9 and 7
// - Take the candy with cost 6 for free
// - We buy candies with costs 5 and 2
// - Take the last remaining candy with cost 2 for free
// Hence, the minimum cost to buy all candies is 9 + 7 + 5 + 2 = 23.

LEETCODE_SOLUTION_UNITTEST(2144, MinimumCostOfBuyingCandiesWithDiscount,
                           example_2) {
  auto        solution = MakeSolution();
  vector<int> cost     = {6, 5, 7, 9, 2, 2};
  int         expect   = 23;
  int         actual   = solution->minimumCost(cost);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: cost = [5,5]
// Output: 10
//
// Since there are only 2 candies, we buy both of them. There is not a third
// candy we can take for free. Hence, the minimum cost to buy all candies is 5 +
// 5 = 10.

LEETCODE_SOLUTION_UNITTEST(2144, MinimumCostOfBuyingCandiesWithDiscount,
                           example_3) {
  auto        solution = MakeSolution();
  vector<int> cost     = {5, 5};
  int         expect   = 10;
  int         actual   = solution->minimumCost(cost);
  LCD_EXPECT_EQ(expect, actual);
}
