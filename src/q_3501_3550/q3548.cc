// Copyright 2026 Naon Lu
//
// This file describes the solution of
// Equal Sum Grid Partition II
//
// https://leetcode.com/problems/equal-sum-grid-partition-ii/
//
// Question ID: 3548
// Difficult  : Hard
// Solve Date : 2026/03/26 13:15

#include <iosfwd>
#include <unordered_map>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |3548. Equal Sum Grid Partition II|:
//
// You are given an |m x n| matrix |grid| of positive integers. Your task is to
// determine if it is possible to make either one horizontal or one vertical cut
// on the grid such that:
//
//  • Each of the two resulting sections formed by the cut is non-empty.
//
//  • The sum of elements in both sections is equal, or can be made equal by
//  discounting at most one single cell in total (from either section).
//
//  • If a cell is discounted, the rest of the section must remain connected.
// Return |true| if such a partition exists; otherwise, return |false|.
// Note: A section is connected if every cell in it can be reached from any
// other cell by moving up, down, left, or right through other cells in the
// section.
//
//

LEETCODE_BEGIN_RESOLVING(3548, EqualSumGridPartitionII, Solution);

class Solution {
public:
  bool canPartitionGrid(vector<vector<int>> &grid) {
    int m = grid.size(), n = grid[0].size();

    long long                     total = 0;
    unordered_map<long long, int> bottomMap, topMap, leftMap, rightMap;

    for (auto &row : grid) {
      for (int x : row) {
        total += x;
        bottomMap[x]++;
        rightMap[x]++;
      }
    }

    long long sumTop = 0;

    for (int i = 0; i < m - 1; i++) {
      for (int j = 0; j < n; j++) {
        int val = grid[i][j];
        sumTop += val;

        topMap[val]++;
        bottomMap[val]--;
      }

      long long sumBottom = total - sumTop;

      if (sumTop == sumBottom)
        return true;

      long long diff = abs(sumTop - sumBottom);

      if (sumTop > sumBottom) {
        if (check(topMap, grid, 0, i, 0, n - 1, diff))
          return true;
      } else {
        if (check(bottomMap, grid, i + 1, m - 1, 0, n - 1, diff))
          return true;
      }
    }

    long long sumLeft = 0;
    for (int j = 0; j < n - 1; j++) {
      for (int i = 0; i < m; i++) {
        int val = grid[i][j];
        sumLeft += val;

        leftMap[val]++;
        rightMap[val]--;
      }

      long long sumRight = total - sumLeft;
      if (sumLeft == sumRight)
        return true;

      long long diff = abs(sumLeft - sumRight);

      if (sumLeft > sumRight) {
        if (check(leftMap, grid, 0, m - 1, 0, j, diff))
          return true;
      } else {
        if (check(rightMap, grid, 0, m - 1, j + 1, n - 1, diff))
          return true;
      }
    }

    return false;
  }

  bool check(unordered_map<long long, int> &mp, vector<vector<int>> &grid,
             int r1, int r2, int c1, int c2, long long diff) {

    int rows = r2 - r1 + 1;
    int cols = c2 - c1 + 1;

    if (rows * cols == 1)
      return false;

    if (rows == 1) {
      return (grid[r1][c1] == diff || grid[r1][c2] == diff);
    }

    if (cols == 1) {
      return (grid[r1][c1] == diff || grid[r2][c1] == diff);
    }

    return mp[diff] > 0;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= m == grid.length <= 10⁵|
// * |1 <= n == grid[i].length <= 10⁵|
// * |2 <= m * n <= 10⁵|
// * |1 <= grid[i][j] <= 10⁵|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: grid = [[1,4],[2,3]]
// Output: true
//

LEETCODE_SOLUTION_UNITTEST(3548, EqualSumGridPartitionII, example_1) {
  auto                solution = MakeSolution();
  vector<vector<int>> grid     = {
      {1, 4},
      {2, 3}
  };
  bool expect = true;
  bool actual = solution->canPartitionGrid(grid);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: grid = [[1,2],[3,4]]
// Output: true
//

LEETCODE_SOLUTION_UNITTEST(3548, EqualSumGridPartitionII, example_2) {
  auto                solution = MakeSolution();
  vector<vector<int>> grid     = {
      {1, 2},
      {3, 4}
  };
  bool expect = true;
  bool actual = solution->canPartitionGrid(grid);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: grid = [[1,2,4],[2,3,5]]
// Output: false
//

LEETCODE_SOLUTION_UNITTEST(3548, EqualSumGridPartitionII, example_3) {
  auto                solution = MakeSolution();
  vector<vector<int>> grid     = {
      {1, 2, 4},
      {2, 3, 5}
  };
  bool expect = false;
  bool actual = solution->canPartitionGrid(grid);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #4]
//  Input: grid = [[4,1,8],[3,2,6]]
// Output: false
//

LEETCODE_SOLUTION_UNITTEST(3548, EqualSumGridPartitionII, example_4) {
  auto                solution = MakeSolution();
  vector<vector<int>> grid     = {
      {4, 1, 8},
      {3, 2, 6}
  };
  bool expect = false;
  bool actual = solution->canPartitionGrid(grid);
  LCD_EXPECT_EQ(expect, actual);
}
