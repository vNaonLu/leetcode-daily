// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Count the Number of Special Characters I
//
// https://leetcode.com/problems/count-the-number-of-special-characters-i/
//
// Question ID: 3120
// Difficult  : Easy
// Solve Date : 2024/05/01 18:47

#include <cctype>
#include <iosfwd>
#include <string>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |3120. Count the Number of Special Characters I|:
//
//

LEETCODE_BEGIN_RESOLVING(3120, CountTheNumberOfSpecialCharactersI, Solution);

class Solution {
public:
  int numberOfSpecialChars(string word) {
    vector<vector<int>> memo(2, vector<int>(26, 0));
    int                 res = 0;
    for (auto c : word) {
      int i = c - (isupper(c) ? 'A' : 'a');
      ++memo[isupper(c) ? 0 : 1][i];
    }
    for (int i = 0; i < 26; ++i) {
      if (memo[0][i] && memo[1][i]) {
        ++res;
      }
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= word.length <= 50|
// * |word| consists of only lowercase and uppercase English letters.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: word = "aaAbcBC"
// Output: 3
//

LEETCODE_SOLUTION_UNITTEST(3120, CountTheNumberOfSpecialCharactersI,
                           example_1) {
  auto   solution = MakeSolution();
  string word     = "aaAbcBC";
  int    expect   = 3;
  int    actual   = solution->numberOfSpecialChars(word);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: word = "abc"
// Output: 0
//

LEETCODE_SOLUTION_UNITTEST(3120, CountTheNumberOfSpecialCharactersI,
                           example_2) {
  auto   solution = MakeSolution();
  string word     = "abc";
  int    expect   = 0;
  int    actual   = solution->numberOfSpecialChars(word);
  LCD_EXPECT_EQ(expect, actual);
}
