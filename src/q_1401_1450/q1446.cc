// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Consecutive Characters
//
// https://leetcode.com/problems/consecutive-characters/
//
// Question ID: 1446
// Difficult  : Easy
// Solve Date : 2021/12/13 18:10

#include <iosfwd>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1446. Consecutive Characters|:
//
// The power of the string is the maximum length of a non-empty substring that
// contains only one unique character. Given a string |s|, return the power of
// |s|.  
//

LEETCODE_BEGIN_RESOLVING(1446, ConsecutiveCharacters, Solution);

class Solution {
public:
  int maxPower(string s) {
    if (s.empty())
      return 0;
    int res = 1, local = 1;
    for (int i = 1; i < s.size(); ++i) {
      if (s[i] == s[i - 1])
        ++local;
      else
        local = 1;
      res = max(res, local);
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= s.length <= 500|
// * |s| consists of only lowercase English letters.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: s = "leetcode"
// Output: 2
//
// The substring "ee" is of length 2 with the character 'e' only.

LEETCODE_SOLUTION_UNITTEST(1446, ConsecutiveCharacters, example_1) {
  auto   solution = MakeSolution();
  string s        = "leetcode";
  int    expect   = 2;
  int    actual   = solution->maxPower(s);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: s = "abbcccddddeeeeedcba"
// Output: 5
//
// The substring "eeeee" is of length 5 with the character 'e' only.

LEETCODE_SOLUTION_UNITTEST(1446, ConsecutiveCharacters, example_2) {
  auto   solution = MakeSolution();
  string s        = "abbcccddddeeeeedcba";
  int    expect   = 5;
  int    actual   = solution->maxPower(s);
  LCD_EXPECT_EQ(expect, actual);
}
