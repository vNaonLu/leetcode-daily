// Copyright 2025 Naon Lu
//
// This file describes the solution of
// Delete Columns to Make Sorted II
//
// https://leetcode.com/problems/delete-columns-to-make-sorted-ii/
//
// Question ID: 955
// Difficult  : Medium
// Solve Date : 2025/12/21 16:18

#include <iosfwd>
#include <string>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |955. Delete Columns to Make Sorted II|:
//
// You are given an array of |n| strings |strs|, all of the same length.
// We may choose any deletion indices, and we delete all the characters in those
// indices for each string. For example, if we have |strs = ["abcdef","uvwxyz"]|
// and deletion indices |{0, 2, 3}|, then the final array after deletions is
// |["bef", "vyz"]|. Suppose we chose a set of deletion indices |answer| such
// that after deletions, the final array has its elements in lexicographic order
// (i.e., |strs[0] <= strs[1] <= strs[2] <= ... <= strs[n - 1]|). Return the
// minimum possible value of |answer.length|.
//
//

LEETCODE_BEGIN_RESOLVING(955, DeleteColumnsToMakeSortedII, Solution);

class Solution {
public:
  int minDeletionSize(vector<string> &strs) {
    int          n = strs.size();
    int          m = strs[0].size();
    vector<bool> resolved(n - 1, false);
    int          unresolved = n - 1;
    int          deletions  = 0;
    for (int col = 0; col < m && unresolved > 0; col++) {
      bool bad = false;

      for (int i = 0; i < n - 1; i++) {
        if (!resolved[i] && strs[i][col] > strs[i + 1][col]) {
          bad = true;
          break;
        }
      }

      if (bad) {
        deletions++;
        continue;
      }

      for (int i = 0; i < n - 1; i++) {
        if (!resolved[i] && strs[i][col] < strs[i + 1][col]) {
          resolved[i] = true;
          unresolved--;
        }
      }
    }

    return deletions;
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
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: strs = ["ca","bb","ac"]
// Output: 1
//

LEETCODE_SOLUTION_UNITTEST(955, DeleteColumnsToMakeSortedII, example_1) {
  auto           solution = MakeSolution();
  vector<string> strs     = {"ca", "bb", "ac"};
  int            expect   = 1;
  int            actual   = solution->minDeletionSize(strs);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: strs = ["xc","yb","za"]
// Output: 0
//

LEETCODE_SOLUTION_UNITTEST(955, DeleteColumnsToMakeSortedII, example_2) {
  auto           solution = MakeSolution();
  vector<string> strs     = {"xc", "yb", "za"};
  int            expect   = 0;
  int            actual   = solution->minDeletionSize(strs);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: strs = ["zyx","wvu","tsr"]
// Output: 3
//

LEETCODE_SOLUTION_UNITTEST(955, DeleteColumnsToMakeSortedII, example_3) {
  auto           solution = MakeSolution();
  vector<string> strs     = {"zyx", "wvu", "tsr"};
  int            expect   = 3;
  int            actual   = solution->minDeletionSize(strs);
  LCD_EXPECT_EQ(expect, actual);
}
