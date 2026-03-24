// Copyright 2026 Naon Lu
//
// This file describes the solution of
// Construct Product Matrix
//
// https://leetcode.com/problems/construct-product-matrix/
//
// Question ID: 2906
// Difficult  : Medium
// Solve Date : 2026/03/24 22:03

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2906. Construct Product Matrix|:
//
// Given a 0-indexed 2D integer matrix |grid| of size |n * m|, we define a
// 0-indexed 2D matrix |p| of size |n * m| as the product matrix of |grid| if
// the following condition is met:
//
//  • Each element |p[i][j]| is calculated as the product of all elements in
//  |grid| except for the element |grid[i][j]|. This product is then taken
//  modulo |12345|.
// Return the product matrix of |grid|.
//
//

LEETCODE_BEGIN_RESOLVING(2906, ConstructProductMatrix, Solution);

class Solution {
public:
  vector<vector<int>> constructProductMatrix(vector<vector<int>> &grid) {
    int                 m = grid.size();
    int                 n = grid[0].size();
    vector<vector<int>> res(m, vector<int>(n));
    using ll = int64_t;
    ll pref  = 1;
    ll suff  = 1;
    ll mod   = 12345;
    for (int i = 0; i < m; i++) {
      for (int j = 0; j < n; j++) {
        res[i][j] = pref;
        pref      = (pref * grid[i][j]) % mod;
      }
    }
    for (int i = m - 1; i >= 0; i--) {
      for (int j = n - 1; j >= 0; j--) {
        res[i][j] = (res[i][j] * suff) % mod;
        suff      = (suff * grid[i][j]) % mod;
      }
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= n == grid.length <= 10⁵|
// * |1 <= m == grid[i].length <= 10⁵|
// * |2 <= n * m <= 10⁵|
// * |1 <= grid[i][j] <= 10⁹|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: grid = [[1,2],[3,4]]
// Output: [[24,12],[8,6]]
//

LEETCODE_SOLUTION_UNITTEST(2906, ConstructProductMatrix, example_1) {
  auto                solution = MakeSolution();
  vector<vector<int>> grid     = {
      {1, 2},
      {3, 4}
  };
  vector<vector<int>> expect = {
      {24, 12},
      { 8,  6}
  };
  vector<vector<int>> actual = solution->constructProductMatrix(grid);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: grid = [[12345],[2],[1]]
// Output: [[2],[0],[0]]
//

LEETCODE_SOLUTION_UNITTEST(2906, ConstructProductMatrix, example_2) {
  auto                solution = MakeSolution();
  vector<vector<int>> grid     = {{12345}, {2}, {1}};
  vector<vector<int>> expect   = {{2}, {0}, {0}};
  vector<vector<int>> actual   = solution->constructProductMatrix(grid);
  LCD_EXPECT_EQ(expect, actual);
}
