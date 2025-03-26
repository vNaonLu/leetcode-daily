// Copyright 2025 Naon Lu
//
// This file describes the solution of
// Minimum Operations to Make a Uni-Value Grid
//
// https://leetcode.com/problems/minimum-operations-to-make-a-uni-value-grid/
//
// Question ID: 2033
// Difficult  : Medium
// Solve Date : 2025/03/26 20:52

#include <algorithm>
#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2033. Minimum Operations to Make a Uni-Value Grid|:
//
// You are given a 2D integer |grid| of size |m x n| and an integer |x|. In one
// operation, you can add |x| to or subtract |x| from any element in the |grid|.
// A uni-value grid is a grid where all the elements of it are equal.
// Return the minimum number of operations to make the grid uni-value. If it is
// not possible, return |-1|.
//
//

LEETCODE_BEGIN_RESOLVING(2033, MinimumOperationsToMakeAUniValueGrid, Solution);

class Solution {
public:
  int minOperations(vector<vector<int>> &grid, int x) {
    vector<int> v;
    for (auto &r : grid) {
      v.insert(v.end(), r.begin(), r.end());
    }

    for (int y : v) {
      if (abs(y - v[0]) % x != 0) {
        return -1;
      }
    }

    nth_element(v.begin(), v.begin() + v.size() / 2, v.end());
    int res = 0;
    int mid = *(v.begin() + v.size() / 2);
    for (auto y : v) {
      res += abs(y - mid) / x;
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
// * |1 <= x, grid[i][j] <= 10⁴|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: grid = [[2,4],[6,8]], x = 2
// Output: 4
//

LEETCODE_SOLUTION_UNITTEST(2033, MinimumOperationsToMakeAUniValueGrid,
                           example_1) {
  auto                solution = MakeSolution();
  vector<vector<int>> grid     = {
      {2, 4},
      {6, 8}
  };
  int x      = 2;
  int expect = 4;
  int actual = solution->minOperations(grid, x);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: grid = [[1,5],[2,3]], x = 1
// Output: 5
//

LEETCODE_SOLUTION_UNITTEST(2033, MinimumOperationsToMakeAUniValueGrid,
                           example_2) {
  auto                solution = MakeSolution();
  vector<vector<int>> grid     = {
      {1, 5},
      {2, 3}
  };
  int x      = 1;
  int expect = 5;
  int actual = solution->minOperations(grid, x);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: grid = [[1,2],[3,4]], x = 2
// Output: -1
//

LEETCODE_SOLUTION_UNITTEST(2033, MinimumOperationsToMakeAUniValueGrid,
                           example_3) {
  auto                solution = MakeSolution();
  vector<vector<int>> grid     = {
      {1, 2},
      {3, 4}
  };
  int x      = 2;
  int expect = -1;
  int actual = solution->minOperations(grid, x);
  LCD_EXPECT_EQ(expect, actual);
}
