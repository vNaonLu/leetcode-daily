// Copyright 2026 Naon Lu
//
// This file describes the solution of
// Equal Sum Grid Partition I
//
// https://leetcode.com/problems/equal-sum-grid-partition-i/
//
// Question ID: 3546
// Difficult  : Medium
// Solve Date : 2026/03/25 19:32

#include <iosfwd>
#include <numeric>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |3546. Equal Sum Grid Partition I|:
//
// You are given an |m x n| matrix |grid| of positive integers. Your task is to
// determine if it is possible to make either one horizontal or one vertical cut
// on the grid such that:
//
//  • Each of the two resulting sections formed by the cut is non-empty.
//
//  • The sum of the elements in both sections is equal.
// Return |true| if such a partition exists; otherwise return |false|.
//
//

LEETCODE_BEGIN_RESOLVING(3546, EqualSumGridPartitionI, Solution);

class Solution {
public:
  static bool canPartitionGrid(vector<vector<int>> &grid) {
    long long Tsum = 0;
    for (auto &row : grid)
      Tsum += accumulate(row.begin(), row.end(), 0LL);
    if (Tsum & 1)
      return 0;
    const long long target = Tsum / 2;
    const int       r = grid.size(), c = grid[0].size();
    long long       rowSum = 0, colSum = 0;
    for (int i = 0; rowSum < target && i < r; i++) {
      rowSum += accumulate(grid[i].begin(), grid[i].end(), 0LL);
    }
    if (rowSum == target)
      return 1;
    for (int j = 0; colSum < target && j < c; j++) {
      for (int i = 0; i < r; i++)
        colSum += grid[i][j];
    }
    return colSum == target;
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

LEETCODE_SOLUTION_UNITTEST(3546, EqualSumGridPartitionI, example_1) {
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
//  Input: grid = [[1,3],[2,4]]
// Output: false
//

LEETCODE_SOLUTION_UNITTEST(3546, EqualSumGridPartitionI, example_2) {
  auto                solution = MakeSolution();
  vector<vector<int>> grid     = {
      {1, 3},
      {2, 4}
  };
  bool expect = false;
  bool actual = solution->canPartitionGrid(grid);
  LCD_EXPECT_EQ(expect, actual);
}
