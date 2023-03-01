// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Split a String in Balanced Strings
//
// https://leetcode.com/problems/split-a-string-in-balanced-strings/
//
// Question ID: 1221
// Difficult  : Easy
// Solve Date : 2021/11/11 21:34

#include <iosfwd>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1221. Split a String in Balanced Strings|:
//
// Balanced strings are those that have an equal quantity of |'L'| and |'R'|
// characters. Given a balanced string |s|, split it into some number of
// substrings such that:
//
//  • Each substring is balanced.
// Return the maximum number of balanced strings you can obtain.
//  
//

LEETCODE_BEGIN_RESOLVING(1221, SplitAStringInBalancedStrings, Solution);

class Solution {
public:
  int balancedStringSplit(string s) {
    int res = 0, diff = 0;
    for (auto it = s.cbegin(); it != s.cend(); ++it) {
      diff += *it == 'L' ? 1 : -1;
      if (diff == 0)
        ++res;
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |2 <= s.length <= 1000|
// * |s[i]| is either |'L'| or |'R'|.
// * |s| is a balanced string.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: s = "RLRRLLRLRL"
// Output: 4
//
// s can be split into "RL", "RRLL", "RL", "RL", each substring contains same
// number of 'L' and 'R'.

LEETCODE_SOLUTION_UNITTEST(1221, SplitAStringInBalancedStrings, example_1) {
  auto   solution = MakeSolution();
  string s        = "RLRRLLRLRL";
  int    expect   = 4;
  int    actual   = solution->balancedStringSplit(s);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: s = "RLRRRLLRLL"
// Output: 2
//
// s can be split into "RL", "RRRLLRLL", each substring contains same number of
// 'L' and 'R'. Note that s cannot be split into "RL", "RR", "RL", "LR", "LL",
// because the 2ⁿᵈ and 5ᵗʰ substrings are not balanced.

LEETCODE_SOLUTION_UNITTEST(1221, SplitAStringInBalancedStrings, example_2) {
  auto   solution = MakeSolution();
  string s        = "RLRRRLLRLL";
  int    expect   = 2;
  int    actual   = solution->balancedStringSplit(s);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: s = "LLLLRRRR"
// Output: 1
//
// s can be split into "LLLLRRRR".

LEETCODE_SOLUTION_UNITTEST(1221, SplitAStringInBalancedStrings, example_3) {
  auto   solution = MakeSolution();
  string s        = "LLLLRRRR";
  int    expect   = 1;
  int    actual   = solution->balancedStringSplit(s);
  LCD_EXPECT_EQ(expect, actual);
}
