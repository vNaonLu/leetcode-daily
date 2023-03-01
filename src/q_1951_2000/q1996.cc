// Copyright 2023 Naon Lu
//
// This file describes the solution of
// The Number of Weak Characters in the Game
//
// https://leetcode.com/problems/the-number-of-weak-characters-in-the-game/
//
// Question ID: 1996
// Difficult  : Medium
// Solve Date : 2022/09/09 15:43

#include <array>
#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1996. The Number of Weak Characters in the Game|:
//
// You are playing a game that contains multiple characters, and each of the
// characters has two main properties: attack and defense. You are given a 2D
// integer array |properties| where |properties[i] = [attackᵢ, defenseᵢ]|
// represents the properties of the |iᵗʰ| character in the game. A character is
// said to be weak if any other character has both attack and defense levels
// strictly greater than this character's attack and defense levels. More
// formally, a character |i| is said to be weak if there exists another
// character |j| where |attackⱼ > attackᵢ| and |defenseⱼ > defenseᵢ|. Return the
// number of weak characters.
//

LEETCODE_BEGIN_RESOLVING(1996, TheNumberOfWeakCharactersInTheGame, Solution);

class Solution {
public:
  int numberOfWeakCharacters(vector<vector<int>> &properties) {
    auto memo = array<int, 100002>();
    auto res  = (int)0;
    for (auto &p : properties) {
      memo[p[0]] = max(memo[p[0]], p[1]);
    }
    for (int i = 100000; i > 0; --i) {
      memo[i - 1] = max(memo[i - 1], memo[i]);
    }
    for (auto &p : properties) {
      res += memo[p[0] + 1] > p[1];
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |2 <= properties.length <= 10⁵|
// * |properties[i].length == 2|
// * |1 <= attackᵢ, defenseᵢ <= 10⁵|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: properties = [[5,5],[6,3],[3,6]]
// Output: 0
//
// No character has strictly greater attack and defense than the other.

LEETCODE_SOLUTION_UNITTEST(1996, TheNumberOfWeakCharactersInTheGame,
                           example_1) {
  auto                solution   = MakeSolution();
  vector<vector<int>> properties = {
      {5, 5},
      {6, 3},
      {3, 6}
  };
  int expect = 0;
  int actual = solution->numberOfWeakCharacters(properties);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: properties = [[2,2],[3,3]]
// Output: 1
//
// The first character is weak because the second character has a strictly
// greater attack and defense.

LEETCODE_SOLUTION_UNITTEST(1996, TheNumberOfWeakCharactersInTheGame,
                           example_2) {
  auto                solution   = MakeSolution();
  vector<vector<int>> properties = {
      {2, 2},
      {3, 3}
  };
  int expect = 1;
  int actual = solution->numberOfWeakCharacters(properties);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: properties = [[1,5],[10,4],[4,3]]
// Output: 1
//
// The third character is weak because the second character has a strictly
// greater attack and defense.

LEETCODE_SOLUTION_UNITTEST(1996, TheNumberOfWeakCharactersInTheGame,
                           example_3) {
  auto                solution   = MakeSolution();
  vector<vector<int>> properties = {
      { 1, 5},
      {10, 4},
      { 4, 3}
  };
  int expect = 1;
  int actual = solution->numberOfWeakCharacters(properties);
  LCD_EXPECT_EQ(expect, actual);
}
