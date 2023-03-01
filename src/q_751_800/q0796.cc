// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Rotate String
//
// https://leetcode.com/problems/rotate-string/
//
// Question ID: 796
// Difficult  : Easy
// Solve Date : 2022/10/30 12:26

#include <iosfwd>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |796. Rotate String|:
//
// Given two strings |s| and |goal|, return |true| if and only if |s| can become
// |goal| after some number of shifts on |s|. A shift on |s| consists of moving
// the leftmost character of |s| to the rightmost position.
//
//  • For example, if |s = "abcde"|, then it will be |"bcdea"| after one shift.
//

LEETCODE_BEGIN_RESOLVING(796, RotateString, Solution);

class Solution {
public:
  bool rotateString(string s, string goal) {
    return s.size() == goal.size() && (s + s).find(goal) != string::npos;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= s.length, goal.length <= 100|
// * |s| and |goal| consist of lowercase English letters.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: s = "abcde", goal = "cdeab"
// Output: true
//

LEETCODE_SOLUTION_UNITTEST(796, RotateString, example_1) {
  auto   solution = MakeSolution();
  string s        = "abcde";
  string goal     = "cdeab";
  bool   expect   = true;
  bool   actual   = solution->rotateString(s, goal);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: s = "abcde", goal = "abced"
// Output: false
//

LEETCODE_SOLUTION_UNITTEST(796, RotateString, example_2) {
  auto   solution = MakeSolution();
  string s        = "abcde";
  string goal     = "abced";
  bool   expect   = false;
  bool   actual   = solution->rotateString(s, goal);
  LCD_EXPECT_EQ(expect, actual);
}
