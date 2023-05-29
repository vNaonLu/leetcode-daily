// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Find the Width of Columns of a Grid
//
// https://leetcode.com/problems/find-the-width-of-columns-of-a-grid/
//
// Question ID: 2639
// Difficult  : Easy
// Solve Date : 2023/05/29 13:47

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2639. Find the Width of Columns of a Grid|:
//
// You are given a 0-indexed |m x n| integer matrix |grid|. The width of a
// column is the maximum length of its integers.
//
//  • For example, if |grid = [[-10], [3], [12]]|, the width of the only column
//  is |3| since |-10| is of length |3|.
// Return an integer array |ans| of size |n| where |ans[i]| is the width of the
// |iᵗʰ| column. The length of an integer |x| with |len| digits is equal to
// |len| if |x| is non-negative, and |len + 1| otherwise.
//
//

LEETCODE_BEGIN_RESOLVING(2639, FindTheWidthOfColumnsOfAGrid, Solution);

class Solution {
public:
  vector<int> findColumnWidth(vector<vector<int>> &grid) {
    auto        m = grid.size();
    auto        n = grid[0].size();
    vector<int> res(n, 0);
    for (int i = 0; i < m; ++i) {
      for (int j = 0; j < n; ++j) {
        res[j] = max(res[j], length(grid[i][j]));
      }
    }
    return res;
  }

private:
  int length(int x) {
    int res = x < 0 ? 1 : 0;
    x       = abs(x);
    while (x) {
      ++res;
      x /= 10;
    }
    return max(res, 1);
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |m == grid.length|
// * |n == grid[i].length|
// * |1 <= m, n <= 100 |
// * |-10⁹ <= grid[r][c] <= 10⁹|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: grid = [[1],[22],[333]]
// Output: [3]
//
// In the 0ᵗʰ column, 333 is of length 3.

LEETCODE_SOLUTION_UNITTEST(2639, FindTheWidthOfColumnsOfAGrid, example_1) {
  auto                solution = MakeSolution();
  vector<vector<int>> grid     = {{1}, {22}, {333}};
  vector<int>         expect   = {3};
  vector<int>         actual   = solution->findColumnWidth(grid);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: grid = [[-15,1,3],[15,7,12],[5,6,-2]]
// Output: [3,1,2]
//
// In the 0ᵗʰ column, only -15 is of length 3.
// In the 1ˢᵗ column, all integers are of length 1.
// In the 2ⁿᵈ column, both 12 and -2 are of length 2.

LEETCODE_SOLUTION_UNITTEST(2639, FindTheWidthOfColumnsOfAGrid, example_2) {
  auto                solution = MakeSolution();
  vector<vector<int>> grid     = {
      {-15, 1,  3},
      { 15, 7, 12},
      {  5, 6, -2}
  };
  vector<int> expect = {3, 1, 2};
  vector<int> actual = solution->findColumnWidth(grid);
  LCD_EXPECT_EQ(expect, actual);
}
