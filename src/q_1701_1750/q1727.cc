// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Largest Submatrix With Rearrangements
//
// https://leetcode.com/problems/largest-submatrix-with-rearrangements/
//
// Question ID: 1727
// Difficult  : Medium
// Solve Date : 2023/11/26 13:16

#include <algorithm>
#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1727. Largest Submatrix With Rearrangements|:
//
// You are given a binary matrix |matrix| of size |m x n|, and you are allowed
// to rearrange the columns of the |matrix| in any order. Return the area of the
// largest submatrix within |matrix| where every element of the submatrix is |1|
// after reordering the columns optimally.
//
//

LEETCODE_BEGIN_RESOLVING(1727, LargestSubmatrixWithRearrangements, Solution);

class Solution {
public:
  int largestSubmatrix(vector<vector<int>> &matrix) {
    int m = matrix.size();
    int n = matrix[0].size();
    for (int i = 1; i < m; ++i) {
      for (int j = 0; j < n; ++j) {
        if (matrix[i][j] != 0) {
          matrix[i][j] += matrix[i - 1][j];
        }
      }
    }
    int res = 0;
    for (int i = 0; i < m; ++i) {
      sort(matrix[i].begin(), matrix[i].end(), greater<int>{});
      int loc = 1e5 + 1;
      for (int j = 0; j < n; ++j) {
        if (matrix[i][j] == 0) {
          continue;
        }

        loc = min(loc, matrix[i][j]);
        res = max(res, (j + 1) * loc);
      }
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |m == matrix.length|
// * |n == matrix[i].length|
// * |1 <= m * n <= 10⁵|
// * |matrix[i][j]| is either |0| or |1|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: matrix = [[0,0,1],[1,1,1],[1,0,1]]
// Output: 4
//
// You can rearrange the columns as shown above.
// The largest submatrix of 1s, in bold, has an area of 4.

LEETCODE_SOLUTION_UNITTEST(1727, LargestSubmatrixWithRearrangements,
                           example_1) {
  auto                solution = MakeSolution();
  vector<vector<int>> matrix   = {
      {0, 0, 1},
      {1, 1, 1},
      {1, 0, 1}
  };
  int expect = 4;
  int actual = solution->largestSubmatrix(matrix);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: matrix = [[1,0,1,0,1]]
// Output: 3
//
// You can rearrange the columns as shown above.
// The largest submatrix of 1s, in bold, has an area of 3.

LEETCODE_SOLUTION_UNITTEST(1727, LargestSubmatrixWithRearrangements,
                           example_2) {
  auto                solution = MakeSolution();
  vector<vector<int>> matrix   = {
      {1, 0, 1, 0, 1}
  };
  int expect = 3;
  int actual = solution->largestSubmatrix(matrix);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: matrix = [[1,1,0],[1,0,1]]
// Output: 2
//
// Notice that you must rearrange entire columns, and there is no way to make a
// submatrix of 1s larger than an area of 2.

LEETCODE_SOLUTION_UNITTEST(1727, LargestSubmatrixWithRearrangements,
                           example_3) {
  auto                solution = MakeSolution();
  vector<vector<int>> matrix   = {
      {1, 1, 0},
      {1, 0, 1}
  };
  int expect = 2;
  int actual = solution->largestSubmatrix(matrix);
  LCD_EXPECT_EQ(expect, actual);
}
