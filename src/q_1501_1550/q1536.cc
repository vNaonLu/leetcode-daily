// Copyright 2026 Naon Lu
//
// This file describes the solution of
// Minimum Swaps to Arrange a Binary Grid
//
// https://leetcode.com/problems/minimum-swaps-to-arrange-a-binary-grid/
//
// Question ID: 1536
// Difficult  : Medium
// Solve Date : 2026/03/02 18:37

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1536. Minimum Swaps to Arrange a Binary Grid|:
//
// Given an |n x n| binary |grid|, in one step you can choose two adjacent rows
// of the grid and swap them. A grid is said to be valid if all the cells above
// the main diagonal are zeros. Return the minimum number of steps needed to
// make the grid valid, or -1 if the grid cannot be valid. The main diagonal of
// a grid is the diagonal that starts at cell |(1, 1)| and ends at cell |(n,
// n)|.
//
//

LEETCODE_BEGIN_RESOLVING(1536, MinimumSwapsToArrangeABinaryGrid, Solution);

class Solution {
public:
  int minSwaps(vector<vector<int>> &grid) {
    int n    = grid.size();
    int size = 1;
    while (size < n)
      size <<= 1;
    vector<int> maxT(size << 1, -1);
    vector<int> sumT(size << 1, 0);

    for (int i = 0; i < n; i++) {
      int trail = 0;
      for (int j = n - 1; j >= 0 && grid[i][j] == 0; j--)
        trail++;
      maxT[size | i] = trail;
      sumT[size | i] = 1;
    }

    for (int i = size - 1; i > 0; i--) {
      maxT[i] = max(maxT[i << 1], maxT[(i << 1) | 1]);
      sumT[i] = sumT[i << 1] + sumT[(i << 1) | 1];
    }

    int swap = 0;
    for (int i = 0; i < n; i++) {
      int req = n - 1 - i;
      if (maxT[1] < req)
        return -1;

      int idx = 1;
      while (idx < size) {
        if (maxT[idx << 1] >= req) {
          idx <<= 1;
        } else {
          swap += sumT[idx << 1];
          idx = (idx << 1) | 1;
        }
      }

      maxT[idx] = -1;
      sumT[idx] = 0;

      for (int p = idx >> 1; p > 0; p >>= 1) {
        maxT[p] = max(maxT[p << 1], maxT[(p << 1) | 1]);
        sumT[p] = sumT[p << 1] + sumT[(p << 1) | 1];
      }
    }

    return swap;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |n == grid.length| |== grid[i].length|
// * |1 <= n <= 200|
// * |grid[i][j]| is either |0| or |1|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: grid = [[0,0,1],[1,1,0],[1,0,0]]
// Output: 3
//

LEETCODE_SOLUTION_UNITTEST(1536, MinimumSwapsToArrangeABinaryGrid, example_1) {
  auto                solution = MakeSolution();
  vector<vector<int>> grid     = {
      {0, 0, 1},
      {1, 1, 0},
      {1, 0, 0}
  };
  int expect = 3;
  int actual = solution->minSwaps(grid);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: grid = [[0,1,1,0],[0,1,1,0],[0,1,1,0],[0,1,1,0]]
// Output: -1
//

LEETCODE_SOLUTION_UNITTEST(1536, MinimumSwapsToArrangeABinaryGrid, example_2) {
  auto                solution = MakeSolution();
  vector<vector<int>> grid     = {
      {0, 1, 1, 0},
      {0, 1, 1, 0},
      {0, 1, 1, 0},
      {0, 1, 1, 0}
  };
  int expect = -1;
  int actual = solution->minSwaps(grid);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: grid = [[1,0,0],[1,1,0],[1,1,1]]
// Output: 0
//

LEETCODE_SOLUTION_UNITTEST(1536, MinimumSwapsToArrangeABinaryGrid, example_3) {
  auto                solution = MakeSolution();
  vector<vector<int>> grid     = {
      {1, 0, 0},
      {1, 1, 0},
      {1, 1, 1}
  };
  int expect = 0;
  int actual = solution->minSwaps(grid);
  LCD_EXPECT_EQ(expect, actual);
}
