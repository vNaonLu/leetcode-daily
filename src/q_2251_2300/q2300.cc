// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Successful Pairs of Spells and Potions
//
// https://leetcode.com/problems/successful-pairs-of-spells-and-potions/
//
// Question ID: 2300
// Difficult  : Medium
// Solve Date : 2023/04/02 14:53

#include <algorithm>
#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2300. Successful Pairs of Spells and Potions|:
//
// You are given two positive integer arrays |spells| and |potions|, of length
// |n| and |m| respectively, where |spells[i]| represents the strength of the
// |iᵗʰ| spell and |potions[j]| represents the strength of the |jᵗʰ| potion. You
// are also given an integer |success|. A spell and potion pair is considered
// successful if the product of their strengths is at least |success|. Return an
// integer array |pairs| of length |n| where |pairs[i]| is the number of potions
// that will form a successful pair with the |iᵗʰ| spell.
//
//

LEETCODE_BEGIN_RESOLVING(2300, SuccessfulPairsOfSpellsAndPotions, Solution);

class Solution {
public:
  vector<int> successfulPairs(vector<int> &spells, vector<int> &potions,
                              long long success) {
    vector<int> res;
    sort(potions.begin(), potions.end());
    for (auto x : spells) {
      auto factor = success / x;
      auto find   = potions.end();
      if (factor * x == success) {
        find = lower_bound(potions.begin(), potions.end(), success / x);
      } else {
        find = upper_bound(potions.begin(), potions.end(), success / x);
      }
      res.emplace_back(distance(find, potions.end()));
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |n == spells.length|
// * |m == potions.length|
// * |1 <= n, m <= 10⁵|
// * |1 <= spells[i], potions[i] <= 10⁵|
// * |1 <= success <= 10¹⁰|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: spells = [5,1,3], potions = [1,2,3,4,5], success = 7
// Output: [4,0,3]
//
// - 0ᵗʰ spell: 5 * [1,2,3,4,5] = [5,10,15,20,25]. 4 pairs are successful.
// - 1ˢᵗ spell: 1 * [1,2,3,4,5] = [1,2,3,4,5]. 0 pairs are successful.
// - 2ⁿᵈ spell: 3 * [1,2,3,4,5] = [3,6,9,12,15]. 3 pairs are successful.
// Thus, [4,0,3] is returned.

LEETCODE_SOLUTION_UNITTEST(2300, SuccessfulPairsOfSpellsAndPotions, example_1) {
  auto        solution = MakeSolution();
  vector<int> spells   = {5, 1, 3};
  vector<int> potions  = {1, 2, 3, 4, 5};
  long long   success  = 7;
  vector<int> expect   = {4, 0, 3};
  vector<int> actual   = solution->successfulPairs(spells, potions, success);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: spells = [3,1,2], potions = [8,5,8], success = 16
// Output: [2,0,2]
//
// - 0ᵗʰ spell: 3 * [8,5,8] = [24,15,24]. 2 pairs are successful.
// - 1ˢᵗ spell: 1 * [8,5,8] = [8,5,8]. 0 pairs are successful.
// - 2ⁿᵈ spell: 2 * [8,5,8] = [16,10,16]. 2 pairs are successful.
// Thus, [2,0,2] is returned.

LEETCODE_SOLUTION_UNITTEST(2300, SuccessfulPairsOfSpellsAndPotions, example_2) {
  auto        solution = MakeSolution();
  vector<int> spells   = {3, 1, 2};
  vector<int> potions  = {8, 5, 8};
  long long   success  = 16;
  vector<int> expect   = {2, 0, 2};
  vector<int> actual   = solution->successfulPairs(spells, potions, success);
  LCD_EXPECT_EQ(expect, actual);
}
