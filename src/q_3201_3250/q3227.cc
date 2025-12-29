// Copyright 2025 Naon Lu
//
// This file describes the solution of
// Vowels Game in a String
//
// https://leetcode.com/problems/vowels-game-in-a-string/
//
// Question ID: 3227
// Difficult  : Medium
// Solve Date : 2025/09/13 07:59

#include <algorithm>
#include <iosfwd>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |3227. Vowels Game in a String|:
//
// Alice and Bob are playing a game on a string.
// You are given a string |s|, Alice and Bob will take turns playing the
// following game where Alice starts first:
//
//  • On Alice's turn, she has to remove any non-empty substring from |s| that
//  contains an odd number of vowels.
//
//  • On Bob's turn, he has to remove any non-empty substring from |s| that
//  contains an even number of vowels.
// The first player who cannot make a move on their turn loses the game. We
// assume that both Alice and Bob play optimally. Return |true| if Alice wins
// the game, and |false| otherwise. The English vowels are: |a|, |e|, |i|, |o|,
// and |u|.
//
//

LEETCODE_BEGIN_RESOLVING(3227, VowelsGameInAString, Solution);

class Solution {
public:
  bool doesAliceWin(string s) {
    return any_of(s.begin(), s.end(), [](auto c) {
      return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
    });
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= s.length <= 10⁵|
// * |s| consists only of lowercase English letters.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: s = "leetcoder"
// Output: true
//

LEETCODE_SOLUTION_UNITTEST(3227, VowelsGameInAString, example_1) {
  auto   solution = MakeSolution();
  string s        = "leetcoder";
  bool   expect   = true;
  bool   actual   = solution->doesAliceWin(s);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: s = "bbcd"
// Output: false
//

LEETCODE_SOLUTION_UNITTEST(3227, VowelsGameInAString, example_2) {
  auto   solution = MakeSolution();
  string s        = "bbcd";
  bool   expect   = false;
  bool   actual   = solution->doesAliceWin(s);
  LCD_EXPECT_EQ(expect, actual);
}
