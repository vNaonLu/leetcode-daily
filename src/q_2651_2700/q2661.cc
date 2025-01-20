// Copyright 2025 Naon Lu
//
// This file describes the solution of
// First Completely Painted Row or Column
//
// https://leetcode.com/problems/first-completely-painted-row-or-column/
//
// Question ID: 2661
// Difficult  : Medium
// Solve Date : 2025/01/20 19:56

#include <iosfwd>
#include <unordered_map>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2661. First Completely Painted Row or Column|:
//
// You are given a 0-indexed integer array |arr|, and an |m x n| integer matrix
// |mat|. |arr| and |mat| both contain all the integers in the range |[1, m *
// n]|. Go through each index |i| in |arr| starting from index |0| and paint the
// cell in |mat| containing the integer |arr[i]|. Return the smallest index |i|
// at which either a row or a column will be completely painted in |mat|.
//
//

LEETCODE_BEGIN_RESOLVING(2661, FirstCompletelyPaintedRowOrColumn, Solution);

class Solution {
public:
  int firstCompleteIndex(vector<int> &arr, vector<vector<int>> &mat) {
    int                                m = mat.size();
    int                                n = mat[0].size();
    vector<int>                        row(m);
    vector<int>                        col(n);
    unordered_map<int, pair<int, int>> pos;
    for (int i = 0; i < m; ++i) {
      for (int j = 0; j < n; ++j) {
        int x  = mat[i][j];
        pos[x] = {i, j};
      }
    }
    for (int i = 0; i < arr.size(); ++i) {
      int x       = arr[i];
      auto [r, c] = pos[x];
      ++row[r];
      ++col[c];
      if (row[r] == n || col[c] == m) {
        return i;
      }
    }
    return -1;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |m == mat.length|
// * |n = mat[i].length|
// * |arr.length == m * n|
// * |1 <= m, n <= 10⁵|
// * |1 <= m * n <= 10⁵|
// * |1 <= arr[i], mat[r][c] <= m * n|
// * All the integers of |arr| are unique.
// * All the integers of |mat| are unique.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: arr = [1,3,4,2], mat = [[1,4],[2,3]]
// Output: 2
//

LEETCODE_SOLUTION_UNITTEST(2661, FirstCompletelyPaintedRowOrColumn, example_1) {
  auto                solution = MakeSolution();
  vector<int>         arr      = {1, 3, 4, 2};
  vector<vector<int>> mat      = {
      {1, 4},
      {2, 3}
  };
  int expect = 2;
  int actual = solution->firstCompleteIndex(arr, mat);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: arr = [2,8,7,4,1,3,5,6,9], mat = [[3,2,5],[1,4,6],[8,7,9]]
// Output: 3
//

LEETCODE_SOLUTION_UNITTEST(2661, FirstCompletelyPaintedRowOrColumn, example_2) {
  auto                solution = MakeSolution();
  vector<int>         arr      = {2, 8, 7, 4, 1, 3, 5, 6, 9};
  vector<vector<int>> mat      = {
      {3, 2, 5},
      {1, 4, 6},
      {8, 7, 9}
  };
  int expect = 3;
  int actual = solution->firstCompleteIndex(arr, mat);
  LCD_EXPECT_EQ(expect, actual);
}

// [Extra Testcase #1]
//  Input: [1,4,5,2,6,3]
// [[4,3,5],[1,2,6]]
// Output: 1
//

LEETCODE_SOLUTION_UNITTEST(2661, FirstCompletelyPaintedRowOrColumn,
                           extra_testcase_1) {
  auto                solution = MakeSolution();
  vector<int>         arr      = {1, 4, 5, 2, 6, 3};
  vector<vector<int>> mat      = {
      {4, 3, 5},
      {1, 2, 6}
  };
  int expect = 1;
  int actual = solution->firstCompleteIndex(arr, mat);
  LCD_EXPECT_EQ(expect, actual);
}
