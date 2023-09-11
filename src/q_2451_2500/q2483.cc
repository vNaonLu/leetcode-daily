// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Minimum Penalty for a Shop
//
// https://leetcode.com/problems/minimum-penalty-for-a-shop/
//
// Question ID: 2483
// Difficult  : Medium
// Solve Date : 2023/08/29 19:15

#include <iosfwd>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2483. Minimum Penalty for a Shop|:
//
// You are given the customer visit log of a shop represented by a 0-indexed
// string |customers| consisting only of characters |'N'| and |'Y'|:
//
//  • if the |iᵗʰ| character is |'Y'|, it means that customers come at the |iᵗʰ|
//  hour
//
//  • whereas |'N'| indicates that no customers come at the |iᵗʰ| hour.
// If the shop closes at the |jᵗʰ| hour ( |0 <= j <= n|), the penalty is
// calculated as follows:
//
//  • For every hour when the shop is open and no customers come, the penalty
//  increases by |1|.
//
//  • For every hour when the shop is closed and customers come, the penalty
//  increases by |1|.
// Return the earliest hour at which the shop must be closed to incur a minimum
// penalty. Note that if a shop closes at the |jᵗʰ| hour, it means the shop is
// closed at the hour |j|.
//
//

LEETCODE_BEGIN_RESOLVING(2483, MinimumPenaltyForAShop, Solution);

class Solution {
public:
  int bestClosingTime(string customers) {
    int y   = count_if(customers.begin(), customers.end(),
                       [](char c) { return c == 'Y'; });
    int n   = 0;
    int res = 0;
    int mn  = numeric_limits<int>::max();
    int penalty;
    for (int i = 0; i < customers.size(); ++i) {
      penalty = y + n;
      if (penalty < mn) {
        res = i;
        mn  = penalty;
      }
      if (customers[i] == 'Y') {
        --y;
      } else {
        ++n;
      }
    }
    penalty = y + n;
    if (penalty < mn) {
      res = customers.size();
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= customers.length <= 10⁵|
// * |customers| consists only of characters |'Y'| and |'N'|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: customers = "YYNY"
// Output: 2
//
// - Closing the shop at the 0ᵗʰ hour incurs in 1+1+0+1 = 3 penalty.
// - Closing the shop at the 1ˢᵗ hour incurs in 0+1+0+1 = 2 penalty.
// - Closing the shop at the 2ⁿᵈ hour incurs in 0+0+0+1 = 1 penalty.
// - Closing the shop at the 3ʳᵈ hour incurs in 0+0+1+1 = 2 penalty.
// - Closing the shop at the 4ᵗʰ hour incurs in 0+0+1+0 = 1 penalty.
// Closing the shop at 2ⁿᵈ or 4ᵗʰ hour gives a minimum penalty. Since 2 is
// earlier, the optimal closing time is 2.

LEETCODE_SOLUTION_UNITTEST(2483, MinimumPenaltyForAShop, example_1) {
  auto   solution  = MakeSolution();
  string customers = "YYNY";
  int    expect    = 2;
  int    actual    = solution->bestClosingTime(customers);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: customers = "NNNNN"
// Output: 0
//
// It is best to close the shop at the 0ᵗʰ hour as no customers arrive.

LEETCODE_SOLUTION_UNITTEST(2483, MinimumPenaltyForAShop, example_2) {
  auto   solution  = MakeSolution();
  string customers = "NNNNN";
  int    expect    = 0;
  int    actual    = solution->bestClosingTime(customers);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: customers = "YYYY"
// Output: 4
//
// It is best to close the shop at the 4ᵗʰ hour as customers arrive at each
// hour.

LEETCODE_SOLUTION_UNITTEST(2483, MinimumPenaltyForAShop, example_3) {
  auto   solution  = MakeSolution();
  string customers = "YYYY";
  int    expect    = 4;
  int    actual    = solution->bestClosingTime(customers);
  LCD_EXPECT_EQ(expect, actual);
}
