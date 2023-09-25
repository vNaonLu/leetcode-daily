// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Minimum Moves to Convert String
//
// https://leetcode.com/problems/minimum-moves-to-convert-string/
//
// Question ID: 2027
// Difficult  : Easy
// Solve Date : 2023/09/22 20:53

#include <iosfwd>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2027. Minimum Moves to Convert String|:
//
// You are given a string |s| consisting of |n| characters which are either
// |'X'| or |'O'|. A move is defined as selecting three consecutive characters
// of |s| and converting them to |'O'|. Note that if a move is applied to the
// character |'O'|, it will stay the same. Return the minimum number of moves
// required so that all the characters of |s| are converted to |'O'|.
//
//

LEETCODE_BEGIN_RESOLVING(2027, MinimumMovesToConvertString, Solution);

class Solution {
public:
  int minimumMoves(string s) {
    int res = 0;
    for (int i = 0; i < s.size(); ++i) {
      if (s[i] == 'X') {
        ++res;
        i += 2;
      }
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |3 <= s.length <= 1000|
// * |s[i]| is either |'X'| or |'O'|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: s = "XXX"
// Output: 1
//
// XXX -> OOO
// We select all the 3 characters and convert them in one move.

LEETCODE_SOLUTION_UNITTEST(2027, MinimumMovesToConvertString, example_1) {
  auto   solution = MakeSolution();
  string s        = "XXX";
  int    expect   = 1;
  int    actual   = solution->minimumMoves(s);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: s = "XXOX"
// Output: 2
//
// XXOX -> OOOX -> OOOO
// We select the first 3 characters in the first move, and convert them to
// |'O'|. Then we select the last 3 characters and convert them so that the
// final string contains all |'O'|s.

LEETCODE_SOLUTION_UNITTEST(2027, MinimumMovesToConvertString, example_2) {
  auto   solution = MakeSolution();
  string s        = "XXOX";
  int    expect   = 2;
  int    actual   = solution->minimumMoves(s);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: s = "OOOO"
// Output: 0
//
// There are no |'X's| in |s| to convert.

LEETCODE_SOLUTION_UNITTEST(2027, MinimumMovesToConvertString, example_3) {
  auto   solution = MakeSolution();
  string s        = "OOOO";
  int    expect   = 0;
  int    actual   = solution->minimumMoves(s);
  LCD_EXPECT_EQ(expect, actual);
}
