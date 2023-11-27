// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Maximum Number of Coins You Can Get
//
// https://leetcode.com/problems/maximum-number-of-coins-you-can-get/
//
// Question ID: 1561
// Difficult  : Medium
// Solve Date : 2023/11/24 11:22

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1561. Maximum Number of Coins You Can Get|:
//
// There are |3n| piles of coins of varying size, you and your friends will take
// piles of coins as follows:
//
//  • In each step, you will choose any |3| piles of coins (not necessarily
//  consecutive).
//
//  • Of your choice, Alice will pick the pile with the maximum number of coins.
//
//  • You will pick the next pile with the maximum number of coins.
//
//  • Your friend Bob will pick the last pile.
//
//  • Repeat until there are no more piles of coins.
// Given an array of integers |piles| where |piles[i]| is the number of coins in
// the |iᵗʰ| pile. Return the maximum number of coins that you can have.
//
//

LEETCODE_BEGIN_RESOLVING(1561, MaximumNumberOfCoinsYouCanGet, Solution);

class Solution {
public:
  int maxCoins(vector<int> &piles) {
    int         n  = piles.size();
    int         mx = *max_element(piles.begin(), piles.end());
    vector<int> freq(mx + 1, 0);
    for (auto x : piles) {
      ++freq[x];
    }

    int res    = 0;
    int chance = n / 3;
    int turn   = 1;
    int i      = mx;
    while (chance != 0) {
      if (freq[i] > 0) {
        if (turn == 1) {
          turn = 0;
        } else {
          turn = 1;
          --chance;
          res += i;
        }
        --freq[i];
      } else {
        --i;
      }
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |3 <= piles.length <= 10⁵|
// * |piles.length % 3 == 0|
// * |1 <= piles[i] <= 10⁴|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: piles = [2,4,1,2,7,8]
// Output: 9
//
// Choose the triplet (2, 7, 8), Alice Pick the pile with 8 coins, you the pile
// with 7 coins and Bob the last one. Choose the triplet (1, 2, 4), Alice Pick
// the pile with 4 coins, you the pile with 2 coins and Bob the last one. The
// maximum number of coins which you can have are: 7 + 2 = 9. On the other hand
// if we choose this arrangement (1, 2, 8), (2, 4, 7) you only get 2 + 4 = 6
// coins which is not optimal.

LEETCODE_SOLUTION_UNITTEST(1561, MaximumNumberOfCoinsYouCanGet, example_1) {
  auto        solution = MakeSolution();
  vector<int> piles    = {2, 4, 1, 2, 7, 8};
  int         expect   = 9;
  int         actual   = solution->maxCoins(piles);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: piles = [2,4,5]
// Output: 4
//

LEETCODE_SOLUTION_UNITTEST(1561, MaximumNumberOfCoinsYouCanGet, example_2) {
  auto        solution = MakeSolution();
  vector<int> piles    = {2, 4, 5};
  int         expect   = 4;
  int         actual   = solution->maxCoins(piles);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: piles = [9,8,7,6,5,1,2,3,4]
// Output: 18
//

LEETCODE_SOLUTION_UNITTEST(1561, MaximumNumberOfCoinsYouCanGet, example_3) {
  auto        solution = MakeSolution();
  vector<int> piles    = {9, 8, 7, 6, 5, 1, 2, 3, 4};
  int         expect   = 18;
  int         actual   = solution->maxCoins(piles);
  LCD_EXPECT_EQ(expect, actual);
}
