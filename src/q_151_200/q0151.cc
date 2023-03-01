// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Reverse Words in a String
//
// https://leetcode.com/problems/reverse-words-in-a-string/
//
// Question ID: 151
// Difficult  : Medium
// Solve Date : 2021/10/20 13:17

#include <iosfwd>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |151. Reverse Words in a String|:
//
// Given an input string |s|, reverse the order of the words.
// A word is defined as a sequence of non-space characters. The words in |s|
// will be separated by at least one space. Return a string of the words in
// reverse order concatenated by a single space. Note that |s| may contain
// leading or trailing spaces or multiple spaces between two words. The returned
// string should only have a single space separating the words. Do not include
// any extra spaces.  
//

LEETCODE_BEGIN_RESOLVING(151, ReverseWordsInAString, Solution);

class Solution {
public:
  string reverseWords(string s) {
    string res;
    int    length = 0;
    for (int i = s.size() - 1; i >= 0; --i) {
      if (s[i] != ' ')
        ++length;
      if (length > 0 && (s[i] == ' ' || i == 0)) {
        if (!res.empty())
          res.push_back(' ');
        res += s.substr(s[i] == ' ' ? i + 1 : i, length);
        length = 0;
      }
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= s.length <= 10⁴|
// * |s| contains English letters (upper-case and lower-case), digits, and
// spaces |' '|.
// * There is at least one word in |s|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: s = "the sky is blue"
// Output: "blue is sky the"
//

LEETCODE_SOLUTION_UNITTEST(151, ReverseWordsInAString, example_1) {
  auto   solution = MakeSolution();
  string s        = "the sky is blue";
  string expect   = "blue is sky the";
  string actual   = solution->reverseWords(s);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: s = " hello world "
// Output: "world hello"
//
// Your reversed string should not contain leading or trailing spaces.

LEETCODE_SOLUTION_UNITTEST(151, ReverseWordsInAString, example_2) {
  auto   solution = MakeSolution();
  string s        = " hello world ";
  string expect   = "world hello";
  string actual   = solution->reverseWords(s);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: s = "a good example"
// Output: "example good a"
//
// You need to reduce multiple spaces between two words to a single space in the
// reversed string.

LEETCODE_SOLUTION_UNITTEST(151, ReverseWordsInAString, example_3) {
  auto   solution = MakeSolution();
  string s        = "a good example";
  string expect   = "example good a";
  string actual   = solution->reverseWords(s);
  LCD_EXPECT_EQ(expect, actual);
}
