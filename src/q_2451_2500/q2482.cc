// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Difference Between Ones and Zeros in Row and Column
//
// https://leetcode.com/problems/difference-between-ones-and-zeros-in-row-and-column/
//
// Question ID: 2482
// Difficult  : Medium
// Solve Date : 2023/12/14 21:41

#include <algorithm>
#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2482. Difference Between Ones and Zeros in Row and Column|:
//
// You are given a 0-indexed |m x n| binary matrix |grid|.
// A 0-indexed |m x n| difference matrix |diff| is created with the following
// procedure:
//
//  • Let the number of ones in the |iᵗʰ| row be |onesRowᵢ|.
//
//  • Let the number of ones in the |jᵗʰ| column be |onesColⱼ|.
//
//  • Let the number of zeros in the |iᵗʰ| row be |zerosRowᵢ|.
//
//  • Let the number of zeros in the |jᵗʰ| column be |zerosColⱼ|.
//
//  • |diff[i][j] = onesRowᵢ + onesColⱼ - zerosRowᵢ - zerosColⱼ|
// Return the difference matrix |diff|.
//
//

LEETCODE_BEGIN_RESOLVING(2482, DifferenceBetweenOnesAndZerosInRowAndColumn,
                         Solution);

class Solution {
public:
  vector<vector<int>> onesMinusZeros(vector<vector<int>> &grid) {
    int                 m = grid.size();
    int                 n = grid[0].size();
    vector<int>         row_ones(m, 0);
    vector<int>         col_ones(n, 0);
    vector<vector<int>> res(m, vector<int>(n, 0));
    for (int i = 0; i < m; ++i) {
      row_ones[i] = count_if(grid[i].begin(), grid[i].end(),
                             [](auto x) { return x == 1; });
    }
    for (int j = 0; j < n; ++j) {
      for (int i = 0; i < m; ++i) {
        if (grid[i][j] == 1) {
          ++col_ones[j];
        }
      }
    }
    for (int i = 0; i < m; ++i) {
      for (int j = 0; j < n; ++j) {
        res[i][j] = 2 * row_ones[i] - m + 2 * col_ones[j] - n;
      }
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |m == grid.length|
// * |n == grid[i].length|
// * |1 <= m, n <= 10⁵|
// * |1 <= m * n <= 10⁵|
// * |grid[i][j]| is either |0| or |1|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: grid = [[0,1,1],[1,0,1],[0,0,1]]
// Output: [[0,0,4],[0,0,4],[-2,-2,2]]
//
// - diff[0][0] = |onesRow₀ + onesCol₀ - zerosRow₀ - zerosCol₀| = 2 + 1 - 1 - 2
// = 0
// - diff[0][1] = |onesRow₀ + onesCol₁ - zerosRow₀ - zerosCol₁| = 2 + 1 - 1 - 2
// = 0
// - diff[0][2] = |onesRow₀ + onesCol₂ - zerosRow₀ - zerosCol₂| = 2 + 3 - 1 - 0
// = 4
// - diff[1][0] = |onesRow₁ + onesCol₀ - zerosRow₁ - zerosCol₀| = 2 + 1 - 1 - 2
// = 0
// - diff[1][1] = |onesRow₁ + onesCol₁ - zerosRow₁ - zerosCol₁| = 2 + 1 - 1 - 2
// = 0
// - diff[1][2] = |onesRow₁ + onesCol₂ - zerosRow₁ - zerosCol₂| = 2 + 3 - 1 - 0
// = 4
// - diff[2][0] = |onesRow₂ + onesCol₀ - zerosRow₂ - zerosCol₀| = 1 + 1 - 2 - 2
// = -2
// - diff[2][1] = |onesRow₂ + onesCol₁ - zerosRow₂ - zerosCol₁| = 1 + 1 - 2 - 2
// = -2
// - diff[2][2] = |onesRow₂ + onesCol₂ - zerosRow₂ - zerosCol₂| = 1 + 3 - 2 - 0
// = 2

LEETCODE_SOLUTION_UNITTEST(2482, DifferenceBetweenOnesAndZerosInRowAndColumn,
                           example_1) {
  auto                solution = MakeSolution();
  vector<vector<int>> grid     = {
      {0, 1, 1},
      {1, 0, 1},
      {0, 0, 1}
  };
  vector<vector<int>> expect = {
      { 0,  0, 4},
      { 0,  0, 4},
      {-2, -2, 2}
  };
  vector<vector<int>> actual = solution->onesMinusZeros(grid);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: grid = [[1,1,1],[1,1,1]]
// Output: [[5,5,5],[5,5,5]]
//
// - diff[0][0] = onesRow₀ + onesCol₀ - zerosRow₀ - zerosCol₀ = 3 + 2 - 0 - 0 =
// 5
// - diff[0][1] = onesRow₀ + onesCol₁ - zerosRow₀ - zerosCol₁ = 3 + 2 - 0 - 0 =
// 5
// - diff[0][2] = onesRow₀ + onesCol₂ - zerosRow₀ - zerosCol₂ = 3 + 2 - 0 - 0 =
// 5
// - diff[1][0] = onesRow₁ + onesCol₀ - zerosRow₁ - zerosCol₀ = 3 + 2 - 0 - 0 =
// 5
// - diff[1][1] = onesRow₁ + onesCol₁ - zerosRow₁ - zerosCol₁ = 3 + 2 - 0 - 0 =
// 5
// - diff[1][2] = onesRow₁ + onesCol₂ - zerosRow₁ - zerosCol₂ = 3 + 2 - 0 - 0 =
// 5

LEETCODE_SOLUTION_UNITTEST(2482, DifferenceBetweenOnesAndZerosInRowAndColumn,
                           example_2) {
  auto                solution = MakeSolution();
  vector<vector<int>> grid     = {
      {1, 1, 1},
      {1, 1, 1}
  };
  vector<vector<int>> expect = {
      {5, 5, 5},
      {5, 5, 5}
  };
  vector<vector<int>> actual = solution->onesMinusZeros(grid);
  LCD_EXPECT_EQ(expect, actual);
}
