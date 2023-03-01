// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Special Positions in a Binary Matrix
//
// https://leetcode.com/problems/special-positions-in-a-binary-matrix/
//
// Question ID: 1582
// Difficult  : Easy
// Solve Date : 2022/02/12 17:00

#include <iosfwd>
#include <queue>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1582. Special Positions in a Binary Matrix|:
//
// Given an |m x n| binary matrix |mat|, return the number of special positions
// in |mat|. A position |(i, j)| is called special if |mat[i][j] == 1| and all
// other elements in row |i| and column |j| are |0| (rows and columns are
// 0-indexed).  
//

LEETCODE_BEGIN_RESOLVING(1582, SpecialPositionsInABinaryMatrix, Solution);

class Solution {
public:
  int numSpecial(vector<vector<int>> &mat) {
    int                   m = mat.size(), n = mat[0].size();
    int                   res = 0;
    queue<pair<int, int>> candidates;
    /// search rows
    for (int i = 0; i < m; ++i) {
      int  first_j = 0;
      bool is_cand = true;
      while (first_j < n && mat[i][first_j] == 0)
        ++first_j;
      for (int j = first_j + 1; j < n; ++j) {
        if (mat[i][j] == 1) {
          is_cand = false;
          break;
        }
      }
      if (is_cand && first_j != n) {
        candidates.emplace(i, first_j);
      }
    }

    /// search cols
    while (true != candidates.empty()) {
      auto [r, c] = candidates.front();
      candidates.pop();
      bool only_one = true;
      for (int i = 0; i < m && only_one; ++i) {
        if (i == r)
          continue;
        if (mat[i][c] == 1)
          only_one = false;
      }
      if (only_one)
        ++res;
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
// * |1 <= m, n <= 100|
// * |mat[i][j]| is either |0| or |1|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: mat = [[1,0,0],[0,0,1],[1,0,0]]
// Output: 1
//
// (1, 2) is a special position because mat[1][2] == 1 and all other elements in
// row 1 and column 2 are 0.

LEETCODE_SOLUTION_UNITTEST(1582, SpecialPositionsInABinaryMatrix, example_1) {
  auto                solution = MakeSolution();
  vector<vector<int>> mat      = {
      {1, 0, 0},
      {0, 0, 1},
      {1, 0, 0}
  };
  int expect = 1;
  int actual = solution->numSpecial(mat);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: mat = [[1,0,0],[0,1,0],[0,0,1]]
// Output: 3
//
// (0, 0), (1, 1) and (2, 2) are special positions.

LEETCODE_SOLUTION_UNITTEST(1582, SpecialPositionsInABinaryMatrix, example_2) {
  auto                solution = MakeSolution();
  vector<vector<int>> mat      = {
      {1, 0, 0},
      {0, 1, 0},
      {0, 0, 1}
  };
  int expect = 3;
  int actual = solution->numSpecial(mat);
  LCD_EXPECT_EQ(expect, actual);
}
