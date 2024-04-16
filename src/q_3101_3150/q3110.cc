// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Score of a String
//
// https://leetcode.com/problems/score-of-a-string/
//
// Question ID: 3110
// Difficult  : Easy
// Solve Date : 2024/04/14 10:35

#include <iosfwd>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |3110. Score of a String|:
//
// You are given a string |s|. The score of a string is defined as the sum of
// the absolute difference between the ASCII values of adjacent characters.
// Return the score of |s|.
//
//

LEETCODE_BEGIN_RESOLVING(3110, ScoreOfAString, Solution);

class Solution {
public:
  int scoreOfString(string s) {
    int res = 0;
    for (int i = 1; i < s.size(); ++i) {
      res += abs(s[i] - s[i - 1]);
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |2 <= s.length <= 100|
// * |s| consists only of lowercase English letters.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: s = "hello"
// Output: 13
//

LEETCODE_SOLUTION_UNITTEST(3110, ScoreOfAString, example_1) {
  auto   solution = MakeSolution();
  string s        = "hello";
  int    expect   = 13;
  int    actual   = solution->scoreOfString(s);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: s = "zaz"
// Output: 50
//

LEETCODE_SOLUTION_UNITTEST(3110, ScoreOfAString, example_2) {
  auto   solution = MakeSolution();
  string s        = "zaz";
  int    expect   = 50;
  int    actual   = solution->scoreOfString(s);
  LCD_EXPECT_EQ(expect, actual);
}
