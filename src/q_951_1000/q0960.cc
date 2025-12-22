// Copyright 2025 Naon Lu
//
// This file describes the solution of
// Delete Columns to Make Sorted III
//
// https://leetcode.com/problems/delete-columns-to-make-sorted-iii/
//
// Question ID: 960
// Difficult  : Hard
// Solve Date : 2025/12/22 22:11

#include <iosfwd>
#include <string>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |960. Delete Columns to Make Sorted III|:
//
// You are given an array of |n| strings |strs|, all of the same length.
// We may choose any deletion indices, and we delete all the characters in those
// indices for each string. For example, if we have |strs = ["abcdef","uvwxyz"]|
// and deletion indices |{0, 2, 3}|, then the final array after deletions is
// |["bef", "vyz"]|. Suppose we chose a set of deletion indices |answer| such
// that after deletions, the final array has every string (row) in lexicographic
// order. (i.e., |(strs[0][0] <= strs[0][1] <= ... <= strs[0][strs[0].length -
// 1])|, and |(strs[1][0] <= strs[1][1] <= ... <= strs[1][strs[1].length - 1])|,
// and so on). Return the minimum possible value of |answer.length|.
//
//

LEETCODE_BEGIN_RESOLVING(960, DeleteColumnsToMakeSortedIII, Solution);

class Solution {
public:
  int dp[100][101];
  int n, m;

  int f(int col, int last, vector<string> &strs) {
    if (col < 0)
      return 0;

    int &cache = dp[col][last];
    if (cache != -1)
      return cache;

    // skip this column
    int ans = f(col - 1, last, strs);

    // take this column
    bool ok = (last == m) ||
              all_of(strs.begin(), strs.end(),
                     [&](const string &s) { return s[col] <= s[last]; });

    if (ok)
      ans = max(ans, 1 + f(col - 1, col, strs));

    return cache = ans;
  }

  int minDeletionSize(vector<string> &strs) {
    n = strs.size();
    m = strs[0].size();
    memset(dp, -1, sizeof(dp));
    return m - f(m - 1, m, strs);
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |n == strs.length|
// * |1 <= n <= 100|
// * |1 <= strs[i].length <= 100|
// * |strs[i]| consists of lowercase English letters.
// *
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: strs = ["babca","bbazb"]
// Output: 3
//

LEETCODE_SOLUTION_UNITTEST(960, DeleteColumnsToMakeSortedIII, example_1) {
  auto           solution = MakeSolution();
  vector<string> strs     = {"babca", "bbazb"};
  int            expect   = 3;
  int            actual   = solution->minDeletionSize(strs);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: strs = ["edcba"]
// Output: 4
//

LEETCODE_SOLUTION_UNITTEST(960, DeleteColumnsToMakeSortedIII, example_2) {
  auto           solution = MakeSolution();
  vector<string> strs     = {"edcba"};
  int            expect   = 4;
  int            actual   = solution->minDeletionSize(strs);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: strs = ["ghi","def","abc"]
// Output: 0
//

LEETCODE_SOLUTION_UNITTEST(960, DeleteColumnsToMakeSortedIII, example_3) {
  auto           solution = MakeSolution();
  vector<string> strs     = {"ghi", "def", "abc"};
  int            expect   = 0;
  int            actual   = solution->minDeletionSize(strs);
  LCD_EXPECT_EQ(expect, actual);
}
