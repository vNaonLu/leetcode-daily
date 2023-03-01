// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Edit Distance
//
// https://leetcode.com/problems/edit-distance/
//
// Question ID: 72
// Difficult  : Hard
// Solve Date : 2021/10/06 13:11

#include <iosfwd>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |72. Edit Distance|:
//
// Given two strings |word1| and |word2|, return the minimum number of
// operations required to convert |word1| to |word2|. You have the following
// three operations permitted on a word:
//
//  • Insert a character
//
//  • Delete a character
//
//  • Replace a character
//  
//

LEETCODE_BEGIN_RESOLVING(72, EditDistance, Solution);

class Solution {
public:
  int minDistance(string word1, string word2) {
    int                 m = word1.size() + 1, n = word2.size() + 1;
    vector<vector<int>> dp(m, vector<int>(n, m + n));
    for (int i = 0; i < m; ++i)
      dp[i][0] = i;
    for (int j = 1; j < n; ++j)
      dp[0][j] = j;
    for (int i = 1; i < m; ++i) {
      for (int j = 1; j < n; ++j) {
        if (word1[i - 1] == word2[j - 1]) {
          dp[i][j] = dp[i - 1][j - 1];
        } else {
          dp[i][j] = min(dp[i - 1][j - 1], dp[i - 1][j]);
          dp[i][j] = min(dp[i][j], dp[i][j - 1]);
          ++dp[i][j];
        }
      }
    }
    return dp.back().back();
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |0 <= word1.length, word2.length <= 500|
// * |word1| and |word2| consist of lowercase English letters.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: word1 = "horse", word2 = "ros"
// Output: 3
//
// horse -> rorse (replace 'h' with 'r')
// rorse -> rose (remove 'r')
// rose -> ros (remove 'e')

LEETCODE_SOLUTION_UNITTEST(72, EditDistance, example_1) {
  auto   solution = MakeSolution();
  string word1    = "horse";
  string word2    = "ros";
  int    expect   = 3;
  int    actual   = solution->minDistance(word1, word2);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: word1 = "intention", word2 = "execution"
// Output: 5
//
// intention -> inention (remove 't')
// inention -> enention (replace 'i' with 'e')
// enention -> exention (replace 'n' with 'x')
// exention -> exection (replace 'n' with 'c')
// exection -> execution (insert 'u')

LEETCODE_SOLUTION_UNITTEST(72, EditDistance, example_2) {
  auto   solution = MakeSolution();
  string word1    = "intention";
  string word2    = "execution";
  int    expect   = 5;
  int    actual   = solution->minDistance(word1, word2);
  LCD_EXPECT_EQ(expect, actual);
}
