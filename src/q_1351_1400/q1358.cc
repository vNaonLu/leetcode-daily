// Copyright 2025 Naon Lu
//
// This file describes the solution of
// Number of Substrings Containing All Three Characters
//
// https://leetcode.com/problems/number-of-substrings-containing-all-three-characters/
//
// Question ID: 1358
// Difficult  : Medium
// Solve Date : 2025/03/11 19:39

#include <iosfwd>
#include <string>
#include <unordered_map>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1358. Number of Substrings Containing All Three Characters|:
//
// Given a string |s| consisting only of characters a, b and c.
// Return the number of substrings containing at least one occurrence of all
// these characters a, b and c.
//
//

LEETCODE_BEGIN_RESOLVING(1358, NumberOfSubstringsContainingAllThreeCharacters,
                         Solution);

class Solution {
public:
  int numberOfSubstrings(string s) {
    int                      res = 0;
    int                      lo  = 0;
    unordered_map<char, int> cnt{
        {'a', 0},
        {'b', 0},
        {'c', 0}
    };

    for (int hi = 0; hi < s.size(); ++hi) {
      ++cnt[s[hi]];
      while (cnt['a'] > 0 && cnt['b'] > 0 && cnt['c'] > 0) {
        res += s.size() - hi;
        --cnt[s[lo++]];
      }
    }

    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |3 <= s.length <= 5 x 10^4|
// * |s| only consists of a, b or c characters.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: s = "abcabc"
// Output: 10
//

LEETCODE_SOLUTION_UNITTEST(1358, NumberOfSubstringsContainingAllThreeCharacters,
                           example_1) {
  auto   solution = MakeSolution();
  string s        = "abcabc";
  int    expect   = 10;
  int    actual   = solution->numberOfSubstrings(s);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: s = "aaacb"
// Output: 3
//

LEETCODE_SOLUTION_UNITTEST(1358, NumberOfSubstringsContainingAllThreeCharacters,
                           example_2) {
  auto   solution = MakeSolution();
  string s        = "aaacb";
  int    expect   = 3;
  int    actual   = solution->numberOfSubstrings(s);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: s = "abc"
// Output: 1
//

LEETCODE_SOLUTION_UNITTEST(1358, NumberOfSubstringsContainingAllThreeCharacters,
                           example_3) {
  auto   solution = MakeSolution();
  string s        = "abc";
  int    expect   = 1;
  int    actual   = solution->numberOfSubstrings(s);
  LCD_EXPECT_EQ(expect, actual);
}
