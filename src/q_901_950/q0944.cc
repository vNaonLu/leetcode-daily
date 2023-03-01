// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Delete Columns to Make Sorted
//
// https://leetcode.com/problems/delete-columns-to-make-sorted/
//
// Question ID: 944
// Difficult  : Easy
// Solve Date : 2023/01/03 18:51

#include <iosfwd>
#include <string>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |944. Delete Columns to Make Sorted|:
//
// You are given an array of |n| strings |strs|, all of the same length.
// The strings can be arranged such that there is one on each line, making a
// grid.
//
//  • For example, |strs = ["abc", "bce", "cae"]| can be arranged as follows:
// abc
// bce
// cae
// You want to delete the columns that are not sorted lexicographically. In the
// above example (0-indexed), columns 0 ( |'a'|, |'b'|, |'c'|) and 2 ( |'c'|,
// |'e'|, |'e'|) are sorted, while column 1 ( |'b'|, |'c'|, |'a'|) is not, so
// you would delete column 1. Return the number of columns that you will delete.
//

LEETCODE_BEGIN_RESOLVING(944, DeleteColumnsToMakeSorted, Solution);

class Solution {
public:
  int minDeletionSize(vector<string> &strs) {
    auto n   = strs.size();
    auto m   = strs.front().size();
    auto res = (int)0;
    for (int i = 0; i < m; ++i) {
      for (int j = 1; j < n; ++j) {
        if (strs[j][i] < strs[j - 1][i]) {
          ++res;
          break;
        }
      }
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |n == strs.length|
// * |1 <= n <= 100|
// * |1 <= strs[i].length <= 1000|
// * |strs[i]| consists of lowercase English letters.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: strs = ["cba","daf","ghi"]
// Output: 1
//
// The grid looks as follows:
//  cba
//  daf
//  ghi
// Columns 0 and 2 are sorted, but column 1 is not, so you only need to delete 1
// column.

LEETCODE_SOLUTION_UNITTEST(944, DeleteColumnsToMakeSorted, example_1) {
  auto           solution = MakeSolution();
  vector<string> strs     = {"cba", "daf", "ghi"};
  int            expect   = 1;
  int            actual   = solution->minDeletionSize(strs);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: strs = ["a","b"]
// Output: 0
//
// The grid looks as follows:
//  a
//  b
// Column 0 is the only column and is sorted, so you will not delete any
// columns.

LEETCODE_SOLUTION_UNITTEST(944, DeleteColumnsToMakeSorted, example_2) {
  auto           solution = MakeSolution();
  vector<string> strs     = {"a", "b"};
  int            expect   = 0;
  int            actual   = solution->minDeletionSize(strs);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: strs = ["zyx","wvu","tsr"]
// Output: 3
//
// The grid looks as follows:
//  zyx
//  wvu
//  tsr
// All 3 columns are not sorted, so you will delete all 3.

LEETCODE_SOLUTION_UNITTEST(944, DeleteColumnsToMakeSorted, example_3) {
  auto           solution = MakeSolution();
  vector<string> strs     = {"zyx", "wvu", "tsr"};
  int            expect   = 3;
  int            actual   = solution->minDeletionSize(strs);
  LCD_EXPECT_EQ(expect, actual);
}
