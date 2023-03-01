// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Distinct Subsequences
//
// https://leetcode.com/problems/distinct-subsequences/
//
// Question ID: 115
// Difficult  : Hard
// Solve Date : 2021/09/19 08:00

#include <iosfwd>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |115. Distinct Subsequences|:
//
// Given two strings |s| and |t|, return the number of distinct subsequences of
// |s| which equals |t|. The test cases are generated so that the answer fits on
// a 32-bit signed integer.  
//

LEETCODE_BEGIN_RESOLVING(115, DistinctSubsequences, Solution);

class Solution {
public:
  int numDistinct(string s, string t) {
    vector<vector<unsigned long long>> dp(
        t.size() + 1, vector<unsigned long long>(s.size() + 1, 0));
    for (int i = 0; i <= s.size(); ++i)
      dp[0][i] = 1;
    for (int i = 1; i <= t.size(); ++i) {
      for (int j = 1; j <= s.size(); ++j) {
        dp[i][j] = dp[i][j - 1];
        if (t[i - 1] == s[j - 1])
          dp[i][j] += dp[i - 1][j - 1];
      }
    }
    return dp.back().back();
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= s.length, t.length <= 1000|
// * |s| and |t| consist of English letters.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: s = "rabbbit", t = "rabbit"
// Output: 3
//
// As shown below, there are 3 ways you can generate "rabbit" from s.
// |rabbbit|
// |rabbbit|
// |rabbbit|

LEETCODE_SOLUTION_UNITTEST(115, DistinctSubsequences, example_1) {
  auto   solution = MakeSolution();
  string s        = "rabbbit";
  string t        = "rabbit";
  int    expect   = 3;
  int    actual   = solution->numDistinct(s, t);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: s = "babgbag", t = "bag"
// Output: 5
//
// As shown below, there are 5 ways you can generate "bag" from s.
// |babgbag|
// |babgbag|
// |babgbag|
// |babgbag|
// |babgbag|

LEETCODE_SOLUTION_UNITTEST(115, DistinctSubsequences, example_2) {
  auto   solution = MakeSolution();
  string s        = "babgbag";
  string t        = "bag";
  int    expect   = 5;
  int    actual   = solution->numDistinct(s, t);
  LCD_EXPECT_EQ(expect, actual);
}
