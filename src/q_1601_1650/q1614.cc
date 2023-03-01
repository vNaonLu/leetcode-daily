// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Maximum Nesting Depth of the Parentheses
//
// https://leetcode.com/problems/maximum-nesting-depth-of-the-parentheses/
//
// Question ID: 1614
// Difficult  : Easy
// Solve Date : 2022/12/07 00:17

#include <iosfwd>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1614. Maximum Nesting Depth of the Parentheses|:
//
// A string is a valid parentheses string (denoted VPS) if it meets one of the
// following:
//
//  • It is an empty string |""|, or a single character not equal to |"("| or
//  |")"|,
//
//  • It can be written as |AB| ( |A| concatenated with |B|), where |A| and |B|
//  are VPS's, or
//
//  • It can be written as |(A)|, where |A| is a VPS.
// We can similarly define the nesting depth |depth(S)| of any VPS |S| as
// follows:
//
//  • |depth("") = 0|
//
//  • |depth(C) = 0|, where |C| is a string with a single character not equal to
//  |"("| or |")"|.
//
//  • |depth(A + B) = max(depth(A), depth(B))|, where |A| and |B| are VPS's.
//
//  • |depth("(" + A + ")") = 1 + depth(A)|, where |A| is a VPS.
// For example, |""|, |"()()"|, and |"()(()())"| are VPS's (with nesting depths
// 0, 1, and 2), and |")("| and |"(()"| are not VPS's. Given a VPS represented
// as string |s|, return the nesting depth of |s|.
//

LEETCODE_BEGIN_RESOLVING(1614, MaximumNestingDepthOfTheParentheses, Solution);

class Solution {
public:
  int maxDepth(string s) {
    auto res   = (int)0;
    auto depth = (int)0;
    for (auto c : s) {
      if (c == '(') {
        res = max(res, ++depth);
      } else if (c == ')') {
        --depth;
      }
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= s.length <= 100|
// * |s| consists of digits |0-9| and characters |'+'|, |'-'|, |'*'|, |'/'|,
// |'('|, and |')'|.
// * It is guaranteed that parentheses expression |s| is a VPS.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: s = "(1+(2*3)+((8)/4))+1"
// Output: 3
//
// Digit 8 is inside of 3 nested parentheses in the string.

LEETCODE_SOLUTION_UNITTEST(1614, MaximumNestingDepthOfTheParentheses,
                           example_1) {
  auto   solution = MakeSolution();
  string s        = "(1+(2*3)+((8)/4))+1";
  int    expect   = 3;
  int    actual   = solution->maxDepth(s);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: s = "(1)+((2))+(((3)))"
// Output: 3
//

LEETCODE_SOLUTION_UNITTEST(1614, MaximumNestingDepthOfTheParentheses,
                           example_2) {
  auto   solution = MakeSolution();
  string s        = "(1)+((2))+(((3)))";
  int    expect   = 3;
  int    actual   = solution->maxDepth(s);
  LCD_EXPECT_EQ(expect, actual);
}
