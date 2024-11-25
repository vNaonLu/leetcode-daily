// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Flip Columns For Maximum Number of Equal Rows
//
// https://leetcode.com/problems/flip-columns-for-maximum-number-of-equal-rows/
//
// Question ID: 1072
// Difficult  : Medium
// Solve Date : 2024/11/25 21:31

#include <iosfwd>
#include <unordered_map>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1072. Flip Columns For Maximum Number of Equal Rows|:
//
// You are given an |m x n| binary matrix |matrix|.
// You can choose any number of columns in the matrix and flip every cell in
// that column (i.e., Change the value of the cell from |0| to |1| or vice
// versa). Return the maximum number of rows that have all values equal after
// some number of flips.
//
//

LEETCODE_BEGIN_RESOLVING(1072, FlipColumnsForMaximumNumberOfEqualRows,
                         Solution);

class Solution {
public:
  int maxEqualRowsAfterFlips(vector<vector<int>> &matrix) {
    unordered_map<string, int> pat;
    for (auto &v : matrix) {
      string p;
      if (v[0] == 0) {
        for (auto b : v) {
          p += to_string(b);
        }
      } else {
        for (auto b : v) {
          p += to_string(b ^ 1);
        }
      }
      ++pat[p];
    }

    int res = 0;
    for (auto &p : pat) {
      res = max(res, p.second);
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
// * |1 <= m, n <= 300|
// * |matrix[i][j]| is either |0| or |1|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: matrix = [[0,1],[1,1]]
// Output: 1
//

LEETCODE_SOLUTION_UNITTEST(1072, FlipColumnsForMaximumNumberOfEqualRows,
                           example_1) {
  auto                solution = MakeSolution();
  vector<vector<int>> matrix   = {
      {0, 1},
      {1, 1}
  };
  int expect = 1;
  int actual = solution->maxEqualRowsAfterFlips(matrix);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: matrix = [[0,1],[1,0]]
// Output: 2
//

LEETCODE_SOLUTION_UNITTEST(1072, FlipColumnsForMaximumNumberOfEqualRows,
                           example_2) {
  auto                solution = MakeSolution();
  vector<vector<int>> matrix   = {
      {0, 1},
      {1, 0}
  };
  int expect = 2;
  int actual = solution->maxEqualRowsAfterFlips(matrix);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: matrix = [[0,0,0],[0,0,1],[1,1,0]]
// Output: 2
//

LEETCODE_SOLUTION_UNITTEST(1072, FlipColumnsForMaximumNumberOfEqualRows,
                           example_3) {
  auto                solution = MakeSolution();
  vector<vector<int>> matrix   = {
      {0, 0, 0},
      {0, 0, 1},
      {1, 1, 0}
  };
  int expect = 2;
  int actual = solution->maxEqualRowsAfterFlips(matrix);
  LCD_EXPECT_EQ(expect, actual);
}
