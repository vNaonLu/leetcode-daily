// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Delete Characters to Make Fancy String
//
// https://leetcode.com/problems/delete-characters-to-make-fancy-string/
//
// Question ID: 1957
// Difficult  : Easy
// Solve Date : 2023/09/17 13:21

#include <iosfwd>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1957. Delete Characters to Make Fancy String|:
//
// A fancy string is a string where no three consecutive characters are equal.
// Given a string |s|, delete the minimum possible number of characters from |s|
// to make it fancy. Return the final string after the deletion. It can be shown
// that the answer will always be unique.
//
//

LEETCODE_BEGIN_RESOLVING(1957, DeleteCharactersToMakeFancyString, Solution);

class Solution {
public:
  string makeFancyString(string s) {
    string res = s.substr(0, 2);
    for (int i = 2; i < s.size(); ++i) {
      auto c = s[i];
      if (c != s[i - 1] || c != s[i - 2]) {
        res.push_back(c);
      }
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= s.length <= 10⁵|
// * |s| consists only of lowercase English letters.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: s = "leeetcode"
// Output: "leetcode"
//
// Remove an 'e' from the first group of 'e's to create "leetcode".
// No three consecutive characters are equal, so return "leetcode".

LEETCODE_SOLUTION_UNITTEST(1957, DeleteCharactersToMakeFancyString, example_1) {
  auto   solution = MakeSolution();
  string s        = "leeetcode";
  string expect   = "leetcode";
  string actual   = solution->makeFancyString(s);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: s = "aaabaaaa"
// Output: "aabaa"
//
// Remove an 'a' from the first group of 'a's to create "aabaaaa".
// Remove two 'a's from the second group of 'a's to create "aabaa".
// No three consecutive characters are equal, so return "aabaa".

LEETCODE_SOLUTION_UNITTEST(1957, DeleteCharactersToMakeFancyString, example_2) {
  auto   solution = MakeSolution();
  string s        = "aaabaaaa";
  string expect   = "aabaa";
  string actual   = solution->makeFancyString(s);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: s = "aab"
// Output: "aab"
//
// No three consecutive characters are equal, so return "aab".

LEETCODE_SOLUTION_UNITTEST(1957, DeleteCharactersToMakeFancyString, example_3) {
  auto   solution = MakeSolution();
  string s        = "aab";
  string expect   = "aab";
  string actual   = solution->makeFancyString(s);
  LCD_EXPECT_EQ(expect, actual);
}
