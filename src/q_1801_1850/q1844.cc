// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Replace All Digits with Characters
//
// https://leetcode.com/problems/replace-all-digits-with-characters/
//
// Question ID: 1844
// Difficult  : Easy
// Solve Date : 2022/12/31 13:18

#include <iosfwd>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1844. Replace All Digits with Characters|:
//
// You are given a 0-indexed string |s| that has lowercase English letters in
// its even indices and digits in its odd indices. There is a function |shift(c,
// x)|, where |c| is a character and |x| is a digit, that returns the |xᵗʰ|
// character after |c|.
//
//  • For example, |shift('a', 5) = 'f'| and |shift('x', 0) = 'x'|.
// For every oddindex |i|, you want to replace the digit |s[i]| with
// |shift(s[i-1], s[i])|. Return |s| after replacing all digits. It is
// guaranteed that |shift(s[i-1], s[i])| will never exceed |'z'|.
//

LEETCODE_BEGIN_RESOLVING(1844, ReplaceAllDigitsWithCharacters, Solution);

class Solution {
private:
  char shift(char x, char cnt) { return x + cnt - '0'; }

public:
  string replaceDigits(string s) {
    for (int i = 0; i < s.size(); ++i) {
      if (s[i] >= '0' && s[i] <= '9') {
        s[i] = shift(s[i - 1], s[i]);
      }
    }
    return s;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= s.length <= 100|
// * |s| consists only of lowercase English letters and digits.
// * |shift(s[i-1], s[i]) <= 'z'| for all odd indices |i|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: s = "a1c1e1"
// Output: "abcdef"
//
// The digits are replaced as follows:
// - s[1] -> shift('a',1) = 'b'
// - s[3] -> shift('c',1) = 'd'
// - s[5] -> shift('e',1) = 'f'

LEETCODE_SOLUTION_UNITTEST(1844, ReplaceAllDigitsWithCharacters, example_1) {
  auto   solution = MakeSolution();
  string s        = "a1c1e1";
  string expect   = "abcdef";
  string actual   = solution->replaceDigits(s);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: s = "a1b2c3d4e"
// Output: "abbdcfdhe"
//
// The digits are replaced as follows:
// - s[1] -> shift('a',1) = 'b'
// - s[3] -> shift('b',2) = 'd'
// - s[5] -> shift('c',3) = 'f'
// - s[7] -> shift('d',4) = 'h'

LEETCODE_SOLUTION_UNITTEST(1844, ReplaceAllDigitsWithCharacters, example_2) {
  auto   solution = MakeSolution();
  string s        = "a1b2c3d4e";
  string expect   = "abbdcfdhe";
  string actual   = solution->replaceDigits(s);
  LCD_EXPECT_EQ(expect, actual);
}
