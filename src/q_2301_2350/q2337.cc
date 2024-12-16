// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Move Pieces to Obtain a String
//
// https://leetcode.com/problems/move-pieces-to-obtain-a-string/
//
// Question ID: 2337
// Difficult  : Medium
// Solve Date : 2024/12/05 15:26

#include <iosfwd>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2337. Move Pieces to Obtain a String|:
//
// You are given two strings |start| and |target|, both of length |n|. Each
// string consists only of the characters |'L'|, |'R'|, and |'_'| where:
//
//  • The characters |'L'| and |'R'| represent pieces, where a piece |'L'| can
//  move to the left only if there is a blank space directly to its left, and a
//  piece |'R'| can move to the right only if there is a blank space directly to
//  its right.
//
//  • The character |'_'| represents a blank space that can be occupied by any
//  of the |'L'| or |'R'| pieces.
// Return |true| if it is possible to obtain the string |target| by moving the
// pieces of the string |start| any number of times. Otherwise, return |false|.
//
//

LEETCODE_BEGIN_RESOLVING(2337, MovePiecesToObtainAString, Solution);

class Solution {
public:
  bool canChange(string start, string target) {
    int n = start.size();
    for (int i = 0, j = 0; i < n || j < n; ++i, ++j) {
      while (i < n && start[i] == '_') {
        ++i;
      }
      while (j < n && target[j] == '_') {
        ++j;
      }

      if (start[i] != target[j]) {
        return false;
      }
      if (start[i] == 'L' && i < j) {
        return false;
      }
      if (start[i] == 'R' && i > j) {
        return false;
      }
    }
    return true;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |n == start.length == target.length|
// * |1 <= n <= 10⁵|
// * |start| and |target| consist of the characters |'L'|, |'R'|, and |'_'|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: start = "_L__R__R_", target = "L______RR"
// Output: true
//

LEETCODE_SOLUTION_UNITTEST(2337, MovePiecesToObtainAString, example_1) {
  auto   solution = MakeSolution();
  string start    = "_L__R__R_";
  string target   = "L______RR";
  bool   expect   = true;
  bool   actual   = solution->canChange(start, target);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: start = "R_L_", target = "__LR"
// Output: false
//

LEETCODE_SOLUTION_UNITTEST(2337, MovePiecesToObtainAString, example_2) {
  auto   solution = MakeSolution();
  string start    = "R_L_";
  string target   = "__LR";
  bool   expect   = false;
  bool   actual   = solution->canChange(start, target);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: start = "_R", target = "R_"
// Output: false
//

LEETCODE_SOLUTION_UNITTEST(2337, MovePiecesToObtainAString, example_3) {
  auto   solution = MakeSolution();
  string start    = "_R";
  string target   = "R_";
  bool   expect   = false;
  bool   actual   = solution->canChange(start, target);
  LCD_EXPECT_EQ(expect, actual);
}
