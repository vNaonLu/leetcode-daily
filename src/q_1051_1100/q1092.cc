// Copyright 2025 Naon Lu
//
// This file describes the solution of
// Shortest Common Supersequence
//
// https://leetcode.com/problems/shortest-common-supersequence/
//
// Question ID: 1092
// Difficult  : Hard
// Solve Date : 2025/02/28 18:16

#include <iosfwd>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1092. Shortest Common Supersequence |:
//
// Given two strings |str1| and |str2|, return the shortest string that has both
// |str1| and |str2| as subsequences. If there are multiple valid strings,
// return any of them. A string |s| is a subsequence of string |t| if deleting
// some number of characters from |t| (possibly |0|) results in the string |s|.
//
//

LEETCODE_BEGIN_RESOLVING(1092, ShortestCommonSupersequence, Solution);

class Solution {
public:
  string shortestCommonSupersequence(string str1, string str2) {
    int                 m = str1.length(), n = str2.length();
    vector<vector<int>> lcs(m + 1, vector<int>(n + 1, 0));

    for (int i = 1; i <= m; i++) {
      for (int j = 1; j <= n; j++) {
        if (str1[i - 1] == str2[j - 1]) {
          lcs[i][j] = 1 + lcs[i - 1][j - 1];
        } else {
          lcs[i][j] = max(lcs[i - 1][j], lcs[i][j - 1]);
        }
      }
    }

    int    i = m, j = n;
    string result = "";

    while (i > 0 && j > 0) {
      if (str1[i - 1] == str2[j - 1]) {
        result += str1[i - 1];
        i--, j--;
      } else if (lcs[i - 1][j] > lcs[i][j - 1]) {
        result += str1[i - 1];
        i--;
      } else {
        result += str2[j - 1];
        j--;
      }
    }

    while (i > 0)
      result += str1[--i];
    while (j > 0)
      result += str2[--j];

    reverse(result.begin(), result.end());
    return result;
  }
};
LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= str1.length, str2.length <= 1000|
// * |str1| and |str2| consist of lowercase English letters.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: str1 = "abac", str2 = "cab"
// Output: "cabac"
//

LEETCODE_SOLUTION_UNITTEST(1092, ShortestCommonSupersequence, example_1) {
  auto   solution = MakeSolution();
  string str1     = "abac";
  string str2     = "cab";
  string expect   = "cabac";
  string actual   = solution->shortestCommonSupersequence(str1, str2);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: str1 = "aaaaaaaa", str2 = "aaaaaaaa"
// Output: "aaaaaaaa"
//

LEETCODE_SOLUTION_UNITTEST(1092, ShortestCommonSupersequence, example_2) {
  auto   solution = MakeSolution();
  string str1     = "aaaaaaaa";
  string str2     = "aaaaaaaa";
  string expect   = "aaaaaaaa";
  string actual   = solution->shortestCommonSupersequence(str1, str2);
  LCD_EXPECT_EQ(expect, actual);
}
