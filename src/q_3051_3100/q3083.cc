// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Existence of a Substring in a String and Its Reverse
//
// https://leetcode.com/problems/existence-of-a-substring-in-a-string-and-its-reverse/
//
// Question ID: 3083
// Difficult  : Easy
// Solve Date : 2024/03/19 22:04

#include <iosfwd>
#include <set>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |3083. Existence of a Substring in a String and Its Reverse|:
//
// Given a string |s|, find any substring of length |2| which is also present in
// the reverse of |s|. Return |true| if such a substring exists, and |false|
// otherwise.
//
//

LEETCODE_BEGIN_RESOLVING(3083, ExistenceOfASubstringInAStringAndItsReverse,
                         Solution);

class Solution {
public:
  bool isSubstringPresent(string s) {
    set<vector<char>> memo;
    for (int i = 1; i < s.size(); ++i) {
      memo.emplace(vector<char>{s[i], s[i - 1]});
      if (memo.count(vector<char>{s[i - 1], s[i]})) {
        return true;
      }
    }
    return false;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= s.length <= 100|
// * |s| consists only of lowercase English letters.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: s = "leetcode"
// Output: true
//

LEETCODE_SOLUTION_UNITTEST(3083, ExistenceOfASubstringInAStringAndItsReverse,
                           example_1) {
  auto   solution = MakeSolution();
  string s        = "leetcode";
  bool   expect   = true;
  bool   actual   = solution->isSubstringPresent(s);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: s = "abcba"
// Output: true
//

LEETCODE_SOLUTION_UNITTEST(3083, ExistenceOfASubstringInAStringAndItsReverse,
                           example_2) {
  auto   solution = MakeSolution();
  string s        = "abcba";
  bool   expect   = true;
  bool   actual   = solution->isSubstringPresent(s);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: s = "abcd"
// Output: false
//

LEETCODE_SOLUTION_UNITTEST(3083, ExistenceOfASubstringInAStringAndItsReverse,
                           example_3) {
  auto   solution = MakeSolution();
  string s        = "abcd";
  bool   expect   = false;
  bool   actual   = solution->isSubstringPresent(s);
  LCD_EXPECT_EQ(expect, actual);
}
