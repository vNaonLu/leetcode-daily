// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Delete Operation for Two Strings
//
// https://leetcode.com/problems/delete-operation-for-two-strings/
//
// Question ID: 583
// Difficult  : Medium
// Solve Date : 2021/10/05 12:06

#include <iosfwd>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |583. Delete Operation for Two Strings|:
//
// Given two strings |word1| and |word2|, return the minimum number of steps
// required to make |word1| and |word2| the same. In one step, you can delete
// exactly one character in either string.  
//

LEETCODE_BEGIN_RESOLVING(583, DeleteOperationForTwoStrings, Solution);

class Solution {
public:
  int minDistance(string word1, string word2) {
    int                 m = word1.size() + 1, n = word2.size() + 1;
    vector<vector<int>> dp(m, vector<int>(n, 0));
    for (int i = 1; i < m; ++i) {
      for (int j = 1; j < n; ++j) {
        dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
        if (word1[i - 1] == word2[j - 1]) {
          dp[i][j] = max(dp[i][j], 1 + dp[i - 1][j - 1]);
        }
      }
    }
    int maxlen = dp.back().back();
    return word1.size() - maxlen + word2.size() - maxlen;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= word1.length, word2.length <= 500|
// * |word1| and |word2| consist of only lowercase English letters.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: word1 = "sea", word2 = "eat"
// Output: 2
//
// You need one step to make "sea" to "ea" and another step to make "eat" to
// "ea".

LEETCODE_SOLUTION_UNITTEST(583, DeleteOperationForTwoStrings, example_1) {
  auto   solution = MakeSolution();
  string word1    = "sea";
  string word2    = "eat";
  int    expect   = 2;
  int    actual   = solution->minDistance(word1, word2);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: word1 = "leetcode", word2 = "etco"
// Output: 4
//

LEETCODE_SOLUTION_UNITTEST(583, DeleteOperationForTwoStrings, example_2) {
  auto   solution = MakeSolution();
  string word1    = "leetcode";
  string word2    = "etco";
  int    expect   = 4;
  int    actual   = solution->minDistance(word1, word2);
  LCD_EXPECT_EQ(expect, actual);
}
