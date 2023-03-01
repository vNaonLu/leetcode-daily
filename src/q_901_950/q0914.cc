// Copyright 2023 Naon Lu
//
// This file describes the solution of
// X of a Kind in a Deck of Cards
//
// https://leetcode.com/problems/x-of-a-kind-in-a-deck-of-cards/
//
// Question ID: 914
// Difficult  : Easy
// Solve Date : 2022/11/23 19:15

#include <iosfwd>
#include <map>
#include <numeric>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |914. X of a Kind in a Deck of Cards|:
//
// You are given an integer array |deck| where |deck[i]| represents the number
// written on the |iᵗʰ| card. Partition the cards into one or more groups such
// that:
//
//  • Each group has exactly |x| cards where |x > 1|, and
//
//  • All the cards in one group have the same integer written on them.
// Return |true| if such partition is possible, or |false| otherwise.
//

LEETCODE_BEGIN_RESOLVING(914, XOfAKindInADeckOfCards, Solution);

class Solution {
public:
  bool hasGroupsSizeX(vector<int> &deck) {
    auto freq = unordered_map<int, int>();
    for (auto x : deck) {
      ++freq[x];
    }

    auto min_cnt = (int)deck.size();
    for (auto &x : freq) {
      min_cnt = min(min_cnt, x.second);
    }

    if (min_cnt < 2) {
      return false;
    }

    auto gcds = unordered_set<int>();
    for (auto &x : freq) {
      auto cur = gcd(x.second, min_cnt);
      if (cur == 1) {
        return false;
      }

      for (auto g : gcds) {
        if (gcd(g, cur) == 1) {
          return false;
        }
      }
      gcds.emplace(cur);
    }

    return true;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= deck.length <= 10⁴|
// * |0 <= deck[i] < 10⁴|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: deck = [1,2,3,4,4,3,2,1]
// Output: true
//
// : Possible partition [1,1],[2,2],[3,3],[4,4].

LEETCODE_SOLUTION_UNITTEST(914, XOfAKindInADeckOfCards, example_1) {
  auto        solution = MakeSolution();
  vector<int> deck     = {1, 2, 3, 4, 4, 3, 2, 1};
  bool        expect   = true;
  bool        actual   = solution->hasGroupsSizeX(deck);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: deck = [1,1,1,2,2,2,3,3]
// Output: false
//
// : No possible partition.

LEETCODE_SOLUTION_UNITTEST(914, XOfAKindInADeckOfCards, example_2) {
  auto        solution = MakeSolution();
  vector<int> deck     = {1, 1, 1, 2, 2, 2, 3, 3};
  bool        expect   = false;
  bool        actual   = solution->hasGroupsSizeX(deck);
  LCD_EXPECT_EQ(expect, actual);
}
