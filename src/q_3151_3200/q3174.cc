// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Clear Digits
//
// https://leetcode.com/problems/clear-digits/
//
// Question ID: 3174
// Difficult  : Easy
// Solve Date : 2024/06/10 12:18

#include <cctype>
#include <iosfwd>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |3174. Clear Digits|:
//
// You are given a string |s|.
// Your task is to remove all digits by doing this operation repeatedly:
//
//  • Delete the first digit and the closest non-digit character to its left.
// Return the resulting string after removing all digits.
//
//

LEETCODE_BEGIN_RESOLVING(3174, ClearDigits, Solution);

class Solution {
public:
  string clearDigits(string s) {
    string res;
    int    pop = 0;
    for (auto it = s.rbegin(); it != s.rend(); ++it) {
      if (isdigit(*it)) {
        ++pop;
      } else {
        if (pop == 0) {
          res.push_back(*it);
        } else {
          --pop;
        }
      }
    }
    reverse(res.begin(), res.end());
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= s.length <= 100|
// * |s| consists only of lowercase English letters and digits.
// * The input is generated such that it is possible to delete all digits.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: s = "abc"
// Output: "abc"
//

LEETCODE_SOLUTION_UNITTEST(3174, ClearDigits, example_1) {
  auto   solution = MakeSolution();
  string s        = "abc";
  string expect   = "abc";
  string actual   = solution->clearDigits(s);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: s = "cb34"
// Output: ""
//

LEETCODE_SOLUTION_UNITTEST(3174, ClearDigits, example_2) {
  auto   solution = MakeSolution();
  string s        = "cb34";
  string expect   = "";
  string actual   = solution->clearDigits(s);
  LCD_EXPECT_EQ(expect, actual);
}
