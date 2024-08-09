// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Minimum Deletions to Make String Balanced
//
// https://leetcode.com/problems/minimum-deletions-to-make-string-balanced/
//
// Question ID: 1653
// Difficult  : Medium
// Solve Date : 2024/07/30 20:35

#include <iosfwd>
#include <string>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1653. Minimum Deletions to Make String Balanced|:
//
// You are given a string |s| consisting only of characters |'a'| and
// |'b'|​​​​. You can delete any number of characters in |s| to make |s|
// balanced. |s| is balanced if there is no pair of indices |(i,j)| such that |i
// < j| and |s[i] = 'b'| and |s[j]= 'a'|. Return the minimum number of deletions
// needed to make |s| balanced.
//
//

LEETCODE_BEGIN_RESOLVING(1653, MinimumDeletionsToMakeStringBalanced, Solution);

class Solution {
public:
  int minimumDeletions(string s) {
    int         n = s.size();
    vector<int> f(n + 1, 0);
    int         b = 0;
    for (int i = 1; i <= n; ++i) {
      if (s[i - 1] == 'b') {
        f[i] = f[i - 1];
        ++b;
      } else {
        f[i] = min(f[i - 1] + 1, b);
      }
    }
    return f[n];
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= s.length <= 10⁵|
// * |s[i]| is |'a'| or |'b'|​​.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: s = "aababbab"
// Output: 2
//

LEETCODE_SOLUTION_UNITTEST(1653, MinimumDeletionsToMakeStringBalanced,
                           example_1) {
  auto   solution = MakeSolution();
  string s        = "aababbab";
  int    expect   = 2;
  int    actual   = solution->minimumDeletions(s);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: s = "bbaaaaabb"
// Output: 2
//

LEETCODE_SOLUTION_UNITTEST(1653, MinimumDeletionsToMakeStringBalanced,
                           example_2) {
  auto   solution = MakeSolution();
  string s        = "bbaaaaabb";
  int    expect   = 2;
  int    actual   = solution->minimumDeletions(s);
  LCD_EXPECT_EQ(expect, actual);
}
