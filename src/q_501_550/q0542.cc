// Copyright 2023 Naon Lu
//
// This file describes the solution of
// 01 Matrix
//
// https://leetcode.com/problems/01-matrix/
//
// Question ID: 542
// Difficult  : Medium
// Solve Date : 2021/09/13 08:00

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |542. 01 Matrix|:
//
// Given an |m x n| binary matrix |mat|, return the distance of the nearest |0|
// for each cell. The distance between two adjacent cells is |1|.  
//

LEETCODE_BEGIN_RESOLVING(542, 01Matrix, Solution);

class Solution {
public:
  vector<vector<int>> updateMatrix(vector<vector<int>> &mat) {
    int                 m = mat.size(), n = mat[0].size();
    vector<vector<int>> res(m, vector<int>(n, n * m));
    for (int i = 0; i < m; ++i) {
      for (int j = -0; j < n; ++j) {
        if (mat[i][j] == 0) {
          res[i][j] = 0;
        } else {
          if (i - 1 >= 0)
            res[i][j] = min(res[i][j], res[i - 1][j] + 1);
          if (j - 1 >= 0)
            res[i][j] = min(res[i][j], res[i][j - 1] + 1);
        }
      }
    }
    for (int i = m - 1; i > -1; --i) {
      for (int j = n - 1; j > -1; --j) {
        if (mat[i][j] == 0) {
          res[i][j] = 0;
        } else {
          if (i + 1 < m)
            res[i][j] = min(res[i][j], res[i + 1][j] + 1);
          if (j + 1 < n)
            res[i][j] = min(res[i][j], res[i][j + 1] + 1);
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
// * |m == mat.length|
// * |n == mat[i].length|
// * |1 <= m, n <= 10⁴|
// * |1 <= m * n <= 10⁴|
// * |mat[i][j]| is either |0| or |1|.
// * There is at least one |0| in |mat|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: mat = [[0,0,0],[0,1,0],[0,0,0]]
// Output: [[0,0,0],[0,1,0],[0,0,0]]
//

LEETCODE_SOLUTION_UNITTEST(542, 01Matrix, example_1) {
  auto                solution = MakeSolution();
  vector<vector<int>> mat      = {
      {0, 0, 0},
      {0, 1, 0},
      {0, 0, 0}
  };
  vector<vector<int>> expect = {
      {0, 0, 0},
      {0, 1, 0},
      {0, 0, 0}
  };
  vector<vector<int>> actual = solution->updateMatrix(mat);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: mat = [[0,0,0],[0,1,0],[1,1,1]]
// Output: [[0,0,0],[0,1,0],[1,2,1]]
//

LEETCODE_SOLUTION_UNITTEST(542, 01Matrix, example_2) {
  auto                solution = MakeSolution();
  vector<vector<int>> mat      = {
      {0, 0, 0},
      {0, 1, 0},
      {1, 1, 1}
  };
  vector<vector<int>> expect = {
      {0, 0, 0},
      {0, 1, 0},
      {1, 2, 1}
  };
  vector<vector<int>> actual = solution->updateMatrix(mat);
  LCD_EXPECT_EQ(expect, actual);
}
