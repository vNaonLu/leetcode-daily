// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Find the Original Typed String I
//
// https://leetcode.com/problems/find-the-original-typed-string-i/
//
// Question ID: 3330
// Difficult  : Easy
// Solve Date : 2024/11/02 00:39

#include <iosfwd>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |3330. Find the Original Typed String I|:
//
// Alice is attempting to type a specific string on her computer. However, she
// tends to be clumsy and may press a key for too long, resulting in a character
// being typed multiple times. Although Alice tried to focus on her typing, she
// is aware that she may still have done this at most once. You are given a
// string |word|, which represents the final output displayed on Alice's screen.
// Return the total number of possible original strings that Alice might have
// intended to type.
//
//

LEETCODE_BEGIN_RESOLVING(3330, FindTheOriginalTypedStringI, Solution);

class Solution {
public:
  int possibleStringCount(string word) {
    char prev = ' ';
    int  res  = 1;
    for (auto c : word) {
      if (prev == c) {
        ++res;
      }
      prev = c;
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= word.length <= 100|
// * |word| consists only of lowercase English letters.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: word = "abbcccc"
// Output: 5
//

LEETCODE_SOLUTION_UNITTEST(3330, FindTheOriginalTypedStringI, example_1) {
  auto   solution = MakeSolution();
  string word     = "abbcccc";
  int    expect   = 5;
  int    actual   = solution->possibleStringCount(word);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: word = "abcd"
// Output: 1
//

LEETCODE_SOLUTION_UNITTEST(3330, FindTheOriginalTypedStringI, example_2) {
  auto   solution = MakeSolution();
  string word     = "abcd";
  int    expect   = 1;
  int    actual   = solution->possibleStringCount(word);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: word = "aaaa"
// Output: 4
//

LEETCODE_SOLUTION_UNITTEST(3330, FindTheOriginalTypedStringI, example_3) {
  auto   solution = MakeSolution();
  string word     = "aaaa";
  int    expect   = 4;
  int    actual   = solution->possibleStringCount(word);
  LCD_EXPECT_EQ(expect, actual);
}

// [Extra Testcase #1]
//  Input: "ere"
// Output: 1
//

LEETCODE_SOLUTION_UNITTEST(3330, FindTheOriginalTypedStringI,
                           extra_testcase_1) {
  auto   solution = MakeSolution();
  string word     = "ere";
  int    expect   = 1;
  int    actual   = solution->possibleStringCount(word);
  LCD_EXPECT_EQ(expect, actual);
}
