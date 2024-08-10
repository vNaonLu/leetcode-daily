// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Regions Cut By Slashes
//
// https://leetcode.com/problems/regions-cut-by-slashes/
//
// Question ID: 959
// Difficult  : Medium
// Solve Date : 2024/08/10 18:07

#include <iosfwd>
#include <string>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |959. Regions Cut By Slashes|:
//
// An |n x n| grid is composed of |1 x 1| squares where each |1 x 1| square
// consists of a |'/'|, |'\'|, or blank space |' '|. These characters divide the
// square into contiguous regions. Given the grid |grid| represented as a string
// array, return the number of regions. Note that backslash characters are
// escaped, so a |'\'| is represented as |'\\'|.
//
//

LEETCODE_BEGIN_RESOLVING(959, RegionsCutBySlashes, Solution);

class Solution {
public:
  int regionsBySlashes(vector<string> &grid) {
    int                 n = grid.size();
    vector<vector<int>> mat(n * 3, vector<int>(n * 3, 0));
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        if (grid[i][j] == '/') {
          mat[i * 3][j * 3 + 2]     = 1;
          mat[i * 3 + 1][j * 3 + 1] = 1;
          mat[i * 3 + 2][j * 3]     = 1;
        } else if (grid[i][j] == '\\') {
          mat[i * 3][j * 3]         = 1;
          mat[i * 3 + 1][j * 3 + 1] = 1;
          mat[i * 3 + 2][j * 3 + 2] = 1;
        }
      }
    }
    int                 res = 0;
    vector<vector<int>> vis(n * 3, vector<int>(n * 3, 0));
    for (int i = 0; i < n * 3; ++i) {
      for (int j = 0; j < n * 3; ++j) {
        if (mat[i][j] == 0 && !vis[i][j]) {
          ++res;
          dfs(i, j, mat, &vis);
        }
      }
    }
    return res;
  }

private:
  void dfs(int i, int j, vector<vector<int>> const &mat,
           vector<vector<int>> *vis) {
    (*vis)[i][j]     = 1;
    int         m    = mat.size();
    int         n    = mat[0].size();
    vector<int> delr = {-1, 0, 1, 0};
    vector<int> delc = {0, 1, 0, -1};
    for (int k = 0; k < 4; ++k) {
      int nrow = i + delr[k];
      int ncol = j + delc[k];
      if (nrow < 0 || nrow >= m || ncol < 0 || ncol >= n ||
          mat[nrow][ncol] != 0 || (*vis)[nrow][ncol]) {
        continue;
      }
      dfs(nrow, ncol, mat, vis);
    }
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |n == grid.length == grid[i].length|
// * |1 <= n <= 30|
// * |grid[i][j]| is either |'/'|, |'\'|, or |' '|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: grid = [" /","/ "]
// Output: 2
//

LEETCODE_SOLUTION_UNITTEST(959, RegionsCutBySlashes, example_1) {
  auto           solution = MakeSolution();
  vector<string> grid     = {" /", "/ "};
  int            expect   = 2;
  int            actual   = solution->regionsBySlashes(grid);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: grid = [" /"," "]
// Output: 1
//

LEETCODE_SOLUTION_UNITTEST(959, RegionsCutBySlashes, example_2) {
  auto           solution = MakeSolution();
  vector<string> grid     = {" /", " "};
  int            expect   = 1;
  int            actual   = solution->regionsBySlashes(grid);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: grid = ["/\\","\\/"]
// Output: 5
//

LEETCODE_SOLUTION_UNITTEST(959, RegionsCutBySlashes, example_3) {
  auto           solution = MakeSolution();
  vector<string> grid     = {"/\\", "\\/"};
  int            expect   = 5;
  int            actual   = solution->regionsBySlashes(grid);
  LCD_EXPECT_EQ(expect, actual);
}
