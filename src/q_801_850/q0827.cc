// Copyright 2025 Naon Lu
//
// This file describes the solution of
// Making A Large Island
//
// https://leetcode.com/problems/making-a-large-island/
//
// Question ID: 827
// Difficult  : Hard
// Solve Date : 2025/01/31 12:04

#include <iosfwd>
#include <unordered_set>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |827. Making A Large Island|:
//
// You are given an |n x n| binary matrix |grid|. You are allowed to change at
// most one |0| to be |1|. Return the size of the largest island in |grid| after
// applying this operation. An island is a 4-directionally connected group of
// |1|s.
//
//

LEETCODE_BEGIN_RESOLVING(827, MakingALargeIsland, Solution);

class Solution {
public:
  int largestIsland(vector<vector<int>> &grid) {
    if (grid.empty())
      return 0;

    int                     n = grid.size();
    vector<vector<int>>     labels(n, vector<int>(n, 0));
    unordered_map<int, int> islandSizes;
    int                     label   = 1;
    int                     maxSize = 0;

    int dirs[4][2] = {
        {-1,  0},
        { 1,  0},
        { 0, -1},
        { 0,  1}
    };

    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        if (grid[i][j] == 1 && labels[i][j] == 0) {
          int                    size = 0;
          vector<pair<int, int>> stack;
          stack.push_back({i, j});
          labels[i][j] = label;

          while (!stack.empty()) {
            auto [x, y] = stack.back();
            stack.pop_back();
            size++;

            for (auto [dx, dy] : dirs) {
              int nx = x + dx, ny = y + dy;
              if (nx >= 0 && nx < n && ny >= 0 && ny < n && grid[nx][ny] == 1 &&
                  labels[nx][ny] == 0) {
                labels[nx][ny] = label;
                stack.push_back({nx, ny});
              }
            }
          }

          islandSizes[label] = size;
          maxSize            = max(maxSize, size);
          label++;
        }
      }
    }

    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        if (grid[i][j] == 0) {
          unordered_set<int> neighborLabels;
          int                total = 1;

          for (auto [dx, dy] : dirs) {
            int nx = i + dx, ny = j + dy;
            if (nx >= 0 && nx < n && ny >= 0 && ny < n && grid[nx][ny] == 1) {
              neighborLabels.insert(labels[nx][ny]);
            }
          }

          for (int lbl : neighborLabels) {
            total += islandSizes[lbl];
          }

          maxSize = max(maxSize, total);
        }
      }
    }

    return maxSize;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |n == grid.length|
// * |n == grid[i].length|
// * |1 <= n <= 500|
// * |grid[i][j]| is either |0| or |1|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: grid = [[1,0],[0,1]]
// Output: 3
//

LEETCODE_SOLUTION_UNITTEST(827, MakingALargeIsland, example_1) {
  auto                solution = MakeSolution();
  vector<vector<int>> grid     = {
      {1, 0},
      {0, 1}
  };
  int expect = 3;
  int actual = solution->largestIsland(grid);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: grid = [[1,1],[1,0]]
// Output: 4
//

LEETCODE_SOLUTION_UNITTEST(827, MakingALargeIsland, example_2) {
  auto                solution = MakeSolution();
  vector<vector<int>> grid     = {
      {1, 1},
      {1, 0}
  };
  int expect = 4;
  int actual = solution->largestIsland(grid);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: grid = [[1,1],[1,1]]
// Output: 4
//

LEETCODE_SOLUTION_UNITTEST(827, MakingALargeIsland, example_3) {
  auto                solution = MakeSolution();
  vector<vector<int>> grid     = {
      {1, 1},
      {1, 1}
  };
  int expect = 4;
  int actual = solution->largestIsland(grid);
  LCD_EXPECT_EQ(expect, actual);
}
