// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Length of Last Word
//
// https://leetcode.com/problems/length-of-last-word/
//
// Question ID: 58
// Difficult  : Easy
// Solve Date : 2021/12/28 18:40

#include <iosfwd>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |58. Length of Last Word|:
//
// Given a string |s| consisting of words and spaces, return the length of the
// last word in the string. A word is a maximal substring consisting of
// non-space characters only.  
//

LEETCODE_BEGIN_RESOLVING(58, LengthOfLastWord, Solution);

class Solution {
public:
  int lengthOfLastWord(string s) {
    int res = 0;
    for (int i = 0; i < s.size(); ++i) {
      if (s[i] != ' ' && (i == 0 || s[i - 1] == ' '))
        res = 1;
      else if (s[i] != ' ')
        ++res;
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= s.length <= 10⁴|
// * |s| consists of only English letters and spaces |' '|.
// * There will be at least one word in |s|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: s = "Hello World"
// Output: 5
//
// The last word is "World" with length 5.

LEETCODE_SOLUTION_UNITTEST(58, LengthOfLastWord, example_1) {
  auto   solution = MakeSolution();
  string s        = "Hello World";
  int    expect   = 5;
  int    actual   = solution->lengthOfLastWord(s);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: s = " fly me to the moon "
// Output: 4
//
// The last word is "moon" with length 4.

LEETCODE_SOLUTION_UNITTEST(58, LengthOfLastWord, example_2) {
  auto   solution = MakeSolution();
  string s        = " fly me to the moon ";
  int    expect   = 4;
  int    actual   = solution->lengthOfLastWord(s);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: s = "luffy is still joyboy"
// Output: 6
//
// The last word is "joyboy" with length 6.

LEETCODE_SOLUTION_UNITTEST(58, LengthOfLastWord, example_3) {
  auto   solution = MakeSolution();
  string s        = "luffy is still joyboy";
  int    expect   = 6;
  int    actual   = solution->lengthOfLastWord(s);
  LCD_EXPECT_EQ(expect, actual);
}
