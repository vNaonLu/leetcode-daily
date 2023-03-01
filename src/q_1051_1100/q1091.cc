// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Shortest Path in Binary Matrix
//
// https://leetcode.com/problems/shortest-path-in-binary-matrix/
//
// Question ID: 1091
// Difficult  : Medium
// Solve Date : 2021/09/26 14:51

#include <iosfwd>
#include <queue>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1091. Shortest Path in Binary Matrix|:
//
// Given an |n x n| binary matrix |grid|, return the length of the shortest
// clear path in the matrix. If there is no clear path, return |-1|. A clear
// path in a binary matrix is a path from the top-left cell (i.e., |(0, 0)|) to
// the bottom-right cell (i.e., |(n - 1, n - 1)|) such that:
//
//  • All the visited cells of the path are |0|.
//
//  • All the adjacent cells of the path are 8-directionally connected (i.e.,
//  they are different and they share an edge or a corner).
// The length of a clear path is the number of visited cells of this path.
//  
//

LEETCODE_BEGIN_RESOLVING(1091, ShortestPathInBinaryMatrix, Solution);

class Solution {
private:
  vector<int> direct = {-1, -1, -1, 0, -1, 1, 0, -1, 0, 1, 1, -1, 1, 0, 1, 1};

public:
  int shortestPathBinaryMatrix(vector<vector<int>> &grid) {
    int                   res = 1;
    int                   n   = grid.size();
    queue<pair<int, int>> path;
    if (grid[0][0] == 0) {
      grid[0][0] = 1;
      path.emplace(0, 0);
      while (!path.empty()) {
        int len = path.size();
        while (len--) {
          auto c = path.front();
          path.pop();
          if (c.first == n - 1 && c.second == n - 1)
            return res;
          for (int i = 0; i < direct.size(); ++i) {
            int x = c.first + direct[i];
            int y = c.second + direct[++i];
            if (x >= 0 && x < n && y >= 0 && y < n && grid[x][y] == 0) {
              grid[x][y] = 1;
              path.emplace(x, y);
            }
          }
        }
        ++res;
      }
    }
    return -1;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |n == grid.length|
// * |n == grid[i].length|
// * |1 <= n <= 100|
// * |grid[i][j] is 0 or 1|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: grid = [[0,1],[1,0]]
// Output: 2
//

LEETCODE_SOLUTION_UNITTEST(1091, ShortestPathInBinaryMatrix, example_1) {
  auto                solution = MakeSolution();
  vector<vector<int>> grid     = {
      {0, 1},
      {1, 0}
  };
  int expect = 2;
  int actual = solution->shortestPathBinaryMatrix(grid);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: grid = [[0,0,0],[1,1,0],[1,1,0]]
// Output: 4
//

LEETCODE_SOLUTION_UNITTEST(1091, ShortestPathInBinaryMatrix, example_2) {
  auto                solution = MakeSolution();
  vector<vector<int>> grid     = {
      {0, 0, 0},
      {1, 1, 0},
      {1, 1, 0}
  };
  int expect = 4;
  int actual = solution->shortestPathBinaryMatrix(grid);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: grid = [[1,0,0],[1,1,0],[1,1,0]]
// Output: -1
//

LEETCODE_SOLUTION_UNITTEST(1091, ShortestPathInBinaryMatrix, example_3) {
  auto                solution = MakeSolution();
  vector<vector<int>> grid     = {
      {1, 0, 0},
      {1, 1, 0},
      {1, 1, 0}
  };
  int expect = -1;
  int actual = solution->shortestPathBinaryMatrix(grid);
  LCD_EXPECT_EQ(expect, actual);
}
