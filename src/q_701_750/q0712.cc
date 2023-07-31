// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Minimum ASCII Delete Sum for Two Strings
//
// https://leetcode.com/problems/minimum-ascii-delete-sum-for-two-strings/
//
// Question ID: 712
// Difficult  : Medium
// Solve Date : 2023/07/31 20:18

#include <iosfwd>
#include <numeric>
#include <string>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |712. Minimum ASCII Delete Sum for Two Strings|:
//
// Given two strings |s1| and |s2|, return the lowest ASCII sum of deleted
// characters to make two strings equal.
//
//

LEETCODE_BEGIN_RESOLVING(712, MinimumASCIIDeleteSumForTwoStrings, Solution);

class Solution {
public:
  int minimumDeleteSum(string s1, string s2) {
    vector<vector<int>> dp(s1.size(), vector<int>(s2.size(), -1));
    return helper(0, 0, s1, s2, &dp);
  }

private:
  int64_t helper(int i, int j, const string &s1, const string &s2,
                 vector<vector<int>> *dp) {
    if (i == s1.size() && j == s2.size()) {
      return 0;
    } else if (i == s1.size()) {
      return accumulate(s2.begin() + j, s2.end(), 0ll);
    } else if (j == s2.size()) {
      return accumulate(s1.begin() + i, s1.end(), 0ll);
    }

    if ((*dp)[i][j] != -1) {
      return (*dp)[i][j];
    }

    int64_t res        = s1[i] == s2[j] ? helper(i + 1, j + 1, s1, s2, dp)
                                        : min(s1[i] + helper(i + 1, j, s1, s2, dp),
                                              s2[j] + helper(i, j + 1, s1, s2, dp));
    return (*dp)[i][j] = res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= s1.length, s2.length <= 1000|
// * |s1| and |s2| consist of lowercase English letters.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: s1 = "sea", s2 = "eat"
// Output: 231
//
// Deleting "s" from "sea" adds the ASCII value of "s" (115) to the sum.
// Deleting "t" from "eat" adds 116 to the sum.
// At the end, both strings are equal, and 115 + 116 = 231 is the minimum sum
// possible to achieve this.

LEETCODE_SOLUTION_UNITTEST(712, MinimumASCIIDeleteSumForTwoStrings, example_1) {
  auto   solution = MakeSolution();
  string s1       = "sea";
  string s2       = "eat";
  int    expect   = 231;
  int    actual   = solution->minimumDeleteSum(s1, s2);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: s1 = "delete", s2 = "leet"
// Output: 403
//
// Deleting "dee" from "delete" to turn the string into "let",
// adds 100[d] + 101[e] + 101[e] to the sum.
// Deleting "e" from "leet" adds 101[e] to the sum.
// At the end, both strings are equal to "let", and the answer is
// 100+101+101+101 = 403. If instead we turned both strings into "lee" or "eet",
// we would get answers of 433 or 417, which are higher.

LEETCODE_SOLUTION_UNITTEST(712, MinimumASCIIDeleteSumForTwoStrings, example_2) {
  auto   solution = MakeSolution();
  string s1       = "delete";
  string s2       = "leet";
  int    expect   = 403;
  int    actual   = solution->minimumDeleteSum(s1, s2);
  LCD_EXPECT_EQ(expect, actual);
}
