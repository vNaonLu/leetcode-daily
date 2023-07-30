// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Strange Printer
//
// https://leetcode.com/problems/strange-printer/
//
// Question ID: 664
// Difficult  : Hard
// Solve Date : 2023/07/30 11:37

#include <iosfwd>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |664. Strange Printer|:
//
// There is a strange printer with the following two special properties:
//
//  • The printer can only print a sequence of the same character each time.
//
//  • At each turn, the printer can print new characters starting from and
//  ending at any place and will cover the original existing characters.
// Given a string |s|, return the minimum number of turns the printer needed to
// print it.
//
//

LEETCODE_BEGIN_RESOLVING(664, StrangePrinter, Solution);

class Solution {
public:
  int strangePrinter(string s) {
    vector<vector<int>> dp(s.size(), vector<int>(s.size(), -1));
    return helper(&dp, 0, s.size() - 1, s);
  }

private:
  int helper(vector<vector<int>> *dp, int i, int j, const string &s) {
    if ((*dp)[i][j] != -1) {
      return (*dp)[i][j];
    }
    if (i == j) {
      return (*dp)[i][j] = 1;
    }

    int res = 0;
    if (s[i] == s[j] || s[j - 1] == s[j]) {
      res = helper(dp, i, j - 1, s);
    } else if (s[i] == s[i + 1]) {
      res = helper(dp, i + 1, j, s);
    } else {
      res = helper(dp, i, j - 1, s) + 1;
      for (int k = i + 1; k < j; ++k) {
        if (s[k] == s[j]) {
          res = min(res, helper(dp, i, k - 1, s) + helper(dp, k, j - 1, s));
        }
      }
    }
    return (*dp)[i][j] = res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= s.length <= 100|
// * |s| consists of lowercase English letters.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: s = "aaabbb"
// Output: 2
//
// Print "aaa" first and then print "bbb".

LEETCODE_SOLUTION_UNITTEST(664, StrangePrinter, example_1) {
  auto   solution = MakeSolution();
  string s        = "aaabbb";
  int    expect   = 2;
  int    actual   = solution->strangePrinter(s);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: s = "aba"
// Output: 2
//
// Print "aaa" first and then print "b" from the second place of the string,
// which will cover the existing character 'a'.

LEETCODE_SOLUTION_UNITTEST(664, StrangePrinter, example_2) {
  auto   solution = MakeSolution();
  string s        = "aba";
  int    expect   = 2;
  int    actual   = solution->strangePrinter(s);
  LCD_EXPECT_EQ(expect, actual);
}

// [Extra Testcase #1]
//  Input: "tbgtgb"
// Output: 4
//

LEETCODE_SOLUTION_UNITTEST(664, StrangePrinter, extra_testcase_1) {
  auto   solution = MakeSolution();
  string s        = "tbgtgb";
  int    expect   = 4;
  int    actual   = solution->strangePrinter(s);
  LCD_EXPECT_EQ(expect, actual);
}
