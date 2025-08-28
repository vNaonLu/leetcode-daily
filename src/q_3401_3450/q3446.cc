// Copyright 2025 Naon Lu
//
// This file describes the solution of
// Sort Matrix by Diagonals
//
// https://leetcode.com/problems/sort-matrix-by-diagonals/
//
// Question ID: 3446
// Difficult  : Medium
// Solve Date : 2025/08/28 19:04

#include <algorithm>
#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |3446. Sort Matrix by Diagonals|:
//
// You are given an |n x n| square matrix of integers |grid|. Return the matrix
// such that:
//
//  • The diagonals in the bottom-left triangle (including the middle diagonal)
//  are sorted in non-increasing order.
//
//  • The diagonals in the top-right triangle are sorted in non-decreasing
//  order.
//
//

LEETCODE_BEGIN_RESOLVING(3446, SortMatrixByDiagonals, Solution);

class Solution {
public:
  vector<vector<int>> sortMatrix(vector<vector<int>> &grid) {
    int n = grid.size();
    for (int i = 1; i < n; ++i) {
      vector<int> tmp;
      tmp.reserve(n);

      for (int j = 0; j < n; ++j) {
        if (i + j >= n) {
          break;
        }
        tmp.push_back(grid[j][j + i]);
      }

      sort(tmp.begin(), tmp.end());

      for (int j = 0; j < n; ++j) {
        if (i + j >= n) {
          break;
        }
        grid[j][j + i] = tmp[j];
      }
    }

    for (int i = 0; i < n; ++i) {
      vector<int> tmp;
      tmp.reserve(n);

      for (int j = 0; j < n; ++j) {
        if (j + i >= n) {
          break;
        }
        tmp.push_back(grid[j + i][j]);
      }

      sort(tmp.rbegin(), tmp.rend());

      for (int j = 0; j < n; ++j) {
        if (j + i >= n) {
          break;
        }
        grid[j + i][j] = tmp[j];
      }
    }
    return grid;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |grid.length == grid[i].length == n|
// * |1 <= n <= 10|
// * |-10⁵ <= grid[i][j] <= 10⁵|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: grid = [[1,7,3],[9,8,2],[4,5,6]]
// Output: [[8,2,3],[9,6,7],[4,5,1]]
//

LEETCODE_SOLUTION_UNITTEST(3446, SortMatrixByDiagonals, example_1) {
  auto                solution = MakeSolution();
  vector<vector<int>> grid     = {
      {1, 7, 3},
      {9, 8, 2},
      {4, 5, 6}
  };
  vector<vector<int>> expect = {
      {8, 2, 3},
      {9, 6, 7},
      {4, 5, 1}
  };
  vector<vector<int>> actual = solution->sortMatrix(grid);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: grid = [[0,1],[1,2]]
// Output: [[2,1],[1,0]]
//

LEETCODE_SOLUTION_UNITTEST(3446, SortMatrixByDiagonals, example_2) {
  auto                solution = MakeSolution();
  vector<vector<int>> grid     = {
      {0, 1},
      {1, 2}
  };
  vector<vector<int>> expect = {
      {2, 1},
      {1, 0}
  };
  vector<vector<int>> actual = solution->sortMatrix(grid);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: grid = [[1]]
// Output: [[1]]
//

LEETCODE_SOLUTION_UNITTEST(3446, SortMatrixByDiagonals, example_3) {
  auto                solution = MakeSolution();
  vector<vector<int>> grid     = {{1}};
  vector<vector<int>> expect   = {{1}};
  vector<vector<int>> actual   = solution->sortMatrix(grid);
  LCD_EXPECT_EQ(expect, actual);
}
