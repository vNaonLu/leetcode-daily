// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Goal Parser Interpretation
//
// https://leetcode.com/problems/goal-parser-interpretation/
//
// Question ID: 1678
// Difficult  : Easy
// Solve Date : 2022/04/21 09:06

#include <iosfwd>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1678. Goal Parser Interpretation|:
//
// You own a Goal Parser that can interpret a string |command|. The |command|
// consists of an alphabet of |"G"|, |"()"| and/or |"(al)"| in some order. The
// Goal Parser will interpret |"G"| as the string |"G"|, |"()"| as the string
// |"o"|, and |"(al)"| as the string |"al"|. The interpreted strings are then
// concatenated in the original order. Given the string |command|, return the
// Goal Parser's interpretation of |command|.  
//

LEETCODE_BEGIN_RESOLVING(1678, GoalParserInterpretation, Solution);

class Solution {
public:
  string interpret(string command) {
    string res, sub;
    auto   it = command.begin();
    while (it != command.end()) {
      if (*it == '(' && *(it + 1) == ')') {
        res.push_back('o');
        ++it;
      } else if (*it != '(' && *it != ')') {
        res.push_back(*it);
      }
      ++it;
    }

    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= command.length <= 100|
// * |command| consists of |"G"|, |"()"|, and/or |"(al)"| in some order.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: command = "G()(al)"
// Output: "Goal"
//
//  The Goal Parser interprets the command as follows:
// G -> G
// () -> o
// (al) -> al
// The final concatenated result is "Goal".

LEETCODE_SOLUTION_UNITTEST(1678, GoalParserInterpretation, example_1) {
  auto   solution = MakeSolution();
  string command  = "G()(al)";
  string expect   = "Goal";
  string actual   = solution->interpret(command);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: command = "G()()()()(al)"
// Output: "Gooooal"
//

LEETCODE_SOLUTION_UNITTEST(1678, GoalParserInterpretation, example_2) {
  auto   solution = MakeSolution();
  string command  = "G()()()()(al)";
  string expect   = "Gooooal";
  string actual   = solution->interpret(command);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: command = "(al)G(al)()()G"
// Output: "alGalooG"
//

LEETCODE_SOLUTION_UNITTEST(1678, GoalParserInterpretation, example_3) {
  auto   solution = MakeSolution();
  string command  = "(al)G(al)()()G";
  string expect   = "alGalooG";
  string actual   = solution->interpret(command);
  LCD_EXPECT_EQ(expect, actual);
}
