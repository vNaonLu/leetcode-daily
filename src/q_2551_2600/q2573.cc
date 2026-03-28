// Copyright 2026 Naon Lu
//
// This file describes the solution of
// Find the String with LCP
//
// https://leetcode.com/problems/find-the-string-with-lcp/
//
// Question ID: 2573
// Difficult  : Hard
// Solve Date : 2026/03/28 12:28

#include <iosfwd>
#include <string>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2573. Find the String with LCP|:
//
// We define the |lcp| matrix of any 0-indexed string |word| of |n| lowercase
// English letters as an |n x n| grid such that:
//
//  • |lcp[i][j]| is equal to the length of the longest common prefix between
//  the substrings |word[i,n-1]| and |word[j,n-1]|.
// Given an |n x n| matrix |lcp|, return the alphabetically smallest string
// |word| that corresponds to |lcp|. If there is no such string, return an empty
// string. A string |a| is lexicographically smaller than a string |b| (of the
// same length) if in the first position where |a| and |b| differ, string |a|
// has a letter that appears earlier in the alphabet than the corresponding
// letter in |b|. For example, |"aabd"| is lexicographically smaller than
// |"aaca"| because the first position they differ is at the third letter, and
// |'b'| comes before |'c'|.
//
//

LEETCODE_BEGIN_RESOLVING(2573, FindTheStringWithLCP, Solution);

class Solution {
public:
  static string findTheString(vector<vector<int>> &lcp) {
    const int n = lcp.size();
    string    s(n, 'X');
    int       id = -1;
    for (int i = 0; i < n; i++) {
      if (lcp[i][i] != n - i)
        return "";
      if (s[i] >= 'a')
        continue;
      if (id++ >= 25)
        return "";
      for (int j = i; j < n; j++)
        if (lcp[i][j])
          s[j] = 'a' + id;
    }
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < i; j++) {
        const int x = lcp[i][j];
        if (x != lcp[j][i] || x + i > n)
          return "";
        int y = (i < n - 1) ? lcp[i + 1][j + 1] : 0;
        y     = (s[i] == s[j]) ? y + 1 : 0;
        if (x != y)
          return "";
      }
    }
    return s;
  }
};
LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= n == | |lcp.length == | |lcp[i].length| |<= 1000|
// * |0 <= lcp[i][j] <= n|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: lcp = [[4,0,2,0],[0,3,0,1],[2,0,2,0],[0,1,0,1]]
// Output: "abab"
//

LEETCODE_SOLUTION_UNITTEST(2573, FindTheStringWithLCP, example_1) {
  auto                solution = MakeSolution();
  vector<vector<int>> lcp      = {
      {4, 0, 2, 0},
      {0, 3, 0, 1},
      {2, 0, 2, 0},
      {0, 1, 0, 1}
  };
  string expect = "abab";
  string actual = solution->findTheString(lcp);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: lcp = [[4,3,2,1],[3,3,2,1],[2,2,2,1],[1,1,1,1]]
// Output: "aaaa"
//

LEETCODE_SOLUTION_UNITTEST(2573, FindTheStringWithLCP, example_2) {
  auto                solution = MakeSolution();
  vector<vector<int>> lcp      = {
      {4, 3, 2, 1},
      {3, 3, 2, 1},
      {2, 2, 2, 1},
      {1, 1, 1, 1}
  };
  string expect = "aaaa";
  string actual = solution->findTheString(lcp);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: lcp = [[4,3,2,1],[3,3,2,1],[2,2,2,1],[1,1,1,3]]
// Output: ""
//

LEETCODE_SOLUTION_UNITTEST(2573, FindTheStringWithLCP, example_3) {
  auto                solution = MakeSolution();
  vector<vector<int>> lcp      = {
      {4, 3, 2, 1},
      {3, 3, 2, 1},
      {2, 2, 2, 1},
      {1, 1, 1, 3}
  };
  string expect = "";
  string actual = solution->findTheString(lcp);
  LCD_EXPECT_EQ(expect, actual);
}
