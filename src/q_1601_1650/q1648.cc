// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Sell Diminishing-Valued Colored Balls
//
// https://leetcode.com/problems/sell-diminishing-valued-colored-balls/
//
// Question ID: 1648
// Difficult  : Medium
// Solve Date : 2022/08/01 18:48

#include <algorithm>
#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1648. Sell Diminishing-Valued Colored Balls|:
//
// You have an |inventory| of different colored balls, and there is a customer
// that wants |orders| balls of any color. The customer weirdly values the
// colored balls. Each colored ball's value is the number of balls of that
// coloryou currently have in your |inventory|. For example, if you own |6|
// yellow balls, the customer would pay |6| for the first yellow ball. After the
// transaction, there are only |5| yellow balls left, so the next yellow ball is
// then valued at |5| (i.e., the value of the balls decreases as you sell more
// to the customer). You are given an integer array, |inventory|, where
// |inventory[i]| represents the number of balls of the |iᵗʰ| color that you
// initially own. You are also given an integer |orders|, which represents the
// total number of balls that the customer wants. You can sell the balls in any
// order. Return the maximum total value that you can attain after selling
// |orders| colored balls. As the answer may be too large, return it modulo
// |10^{9 }+ 7|.
//

LEETCODE_BEGIN_RESOLVING(1648, SellDiminishingValuedColoredBalls, Solution);

class Solution {
private:
  inline constexpr static int kMod = 1e9 + 7;

public:
  int maxProfit(vector<int> &inventory, int orders) {
    inventory.emplace_back(0);
    sort(inventory.begin(), inventory.end());
    int     hi = inventory.size() - 1, nondecreasing = 1;
    int64_t res = 0;
    while (orders > 0) {
      while (inventory[hi] == inventory[hi - 1]) {
        ++nondecreasing;
        --hi;
      }

      auto d = inventory[hi] - inventory[hi - 1];
      auto c = (orders - 1) / nondecreasing;
      auto r = (orders - 1) % nondecreasing;
      if (c >= d) {
        c = d - 1;
        r = nondecreasing - 1;
      }

      res += ((int64_t)(inventory[hi] + inventory[hi] - c) * (c + 1)) / 2 *
             nondecreasing;
      res -= (int64_t)(nondecreasing - 1 - r) * (inventory[hi] - c);
      res %= kMod;
      orders -= (c + 1) * nondecreasing;
      --hi;
      ++nondecreasing;
    }

    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= inventory.length <= 10⁵|
// * |1 <= inventory[i] <= 10⁹|
// * |1 <= orders <= min(sum(inventory[i]), 10⁹)|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: inventory = [2,5], orders = 4
// Output: 14
//
// Sell the 1st color 1 time (2) and the 2nd color 3 times (5 + 4 + 3).
// The maximum total value is 2 + 5 + 4 + 3 = 14.

LEETCODE_SOLUTION_UNITTEST(1648, SellDiminishingValuedColoredBalls, example_1) {
  auto        solution  = MakeSolution();
  vector<int> inventory = {2, 5};
  int         orders    = 4;
  int         expect    = 14;
  int         actual    = solution->maxProfit(inventory, orders);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: inventory = [3,5], orders = 6
// Output: 19
//
// Sell the 1st color 2 times (3 + 2) and the 2nd color 4 times (5 + 4 + 3 + 2).
// The maximum total value is 3 + 2 + 5 + 4 + 3 + 2 = 19.

LEETCODE_SOLUTION_UNITTEST(1648, SellDiminishingValuedColoredBalls, example_2) {
  auto        solution  = MakeSolution();
  vector<int> inventory = {3, 5};
  int         orders    = 6;
  int         expect    = 19;
  int         actual    = solution->maxProfit(inventory, orders);
  LCD_EXPECT_EQ(expect, actual);
}
