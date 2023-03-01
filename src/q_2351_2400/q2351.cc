// Copyright 2023 Naon Lu
//
// This file describes the solution of
// First Letter to Appear Twice
//
// https://leetcode.com/problems/first-letter-to-appear-twice/
//
// Question ID: 2351
// Difficult  : Easy
// Solve Date : 2023/02/15 19:45

#include <iosfwd>
#include <set>
#include <string>
#include <unordered_set>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2351. First Letter to Appear Twice|:
//
// Given a string |s| consisting of lowercase English letters, return the first
// letter to appear twice. Note:
//
//  • A letter |a| appears twice before another letter |b| if the second
//  occurrence of |a| is before the second occurrence of |b|.
//
//  • |s| will contain at least one letter that appears twice.
//

LEETCODE_BEGIN_RESOLVING(2351, FirstLetterToAppearTwice, Solution);

class Solution {
public:
  char repeatedCharacter(string s) {
    unordered_set<char> memo;
    for (auto c : s) {
      if (!memo.emplace(c).second) {
        return c;
      }
    }
    return ' ';
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |2 <= s.length <= 100|
// * |s| consists of lowercase English letters.
// * |s| has at least one repeated letter.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: s = "abccbaacz"
// Output: "c"
//
// The letter 'a' appears on the indexes 0, 5 and 6.
// The letter 'b' appears on the indexes 1 and 4.
// The letter 'c' appears on the indexes 2, 3 and 7.
// The letter 'z' appears on the index 8.
// The letter 'c' is the first letter to appear twice, because out of all the
// letters the index of its second occurrence is the smallest.

LEETCODE_SOLUTION_UNITTEST(2351, FirstLetterToAppearTwice, example_1) {
  auto   solution = MakeSolution();
  string s        = "abccbaacz";
  char   expect   = 'c';
  char   actual   = solution->repeatedCharacter(s);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: s = "abcdd"
// Output: "d"
//
// The only letter that appears twice is 'd' so we return 'd'.

LEETCODE_SOLUTION_UNITTEST(2351, FirstLetterToAppearTwice, example_2) {
  auto   solution = MakeSolution();
  string s        = "abcdd";
  char   expect   = 'd';
  char   actual   = solution->repeatedCharacter(s);
  LCD_EXPECT_EQ(expect, actual);
}
