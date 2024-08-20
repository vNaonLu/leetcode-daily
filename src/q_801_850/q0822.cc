// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Card Flipping Game
//
// https://leetcode.com/problems/card-flipping-game/
//
// Question ID: 822
// Difficult  : Medium
// Solve Date : 2024/08/15 22:24

#include <iosfwd>
#include <unordered_map>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |822. Card Flipping Game|:
//
// You are given two 0-indexed integer arrays |fronts| and |backs| of length
// |n|, where the |iᵗʰ| card has the positive integer |fronts[i]| printed on the
// front and |backs[i]| printed on the back. Initially, each card is placed on a
// table such that the front number is facing up and the other is facing down.
// You may flip over any number of cards (possibly zero). After flipping the
// cards, an integer is considered good if it is facing down on some card and
// not facing up on any card. Return the minimum possible good integer after
// flipping the cards. If there are no good integers, return |0|.
//
//

LEETCODE_BEGIN_RESOLVING(822, CardFlippingGame, Solution);

class Solution {
public:
  int flipgame(vector<int> &fronts, vector<int> &backs) {
    int                     n   = fronts.size();
    int                     res = numeric_limits<int>::max();
    unordered_map<int, int> mp;
    for (int i = 0; i < n; ++i) {
      if (fronts[i] == backs[i]) {
        ++mp[fronts[i]];
      }
    }

    for (int i = 0; i < n; ++i) {
      if (!mp.count(fronts[i])) {
        res = min(res, fronts[i]);
        ++mp[fronts[i]];
      }
      if (!mp.count(backs[i])) {
        res = min(res, backs[i]);
        ++mp[backs[i]];
      }
    }
    return res == numeric_limits<int>::max() ? 0 : res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |n == fronts.length == backs.length|
// * |1 <= n <= 1000|
// * |1 <= fronts[i], backs[i] <= 2000|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: fronts = [1,2,4,4,7], backs = [1,3,4,1,3]
// Output: 2
//

LEETCODE_SOLUTION_UNITTEST(822, CardFlippingGame, example_1) {
  auto        solution = MakeSolution();
  vector<int> fronts   = {1, 2, 4, 4, 7};
  vector<int> backs    = {1, 3, 4, 1, 3};
  int         expect   = 2;
  int         actual   = solution->flipgame(fronts, backs);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: fronts = [1], backs = [1]
// Output: 0
//

LEETCODE_SOLUTION_UNITTEST(822, CardFlippingGame, example_2) {
  auto        solution = MakeSolution();
  vector<int> fronts   = {1};
  vector<int> backs    = {1};
  int         expect   = 0;
  int         actual   = solution->flipgame(fronts, backs);
  LCD_EXPECT_EQ(expect, actual);
}
