// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Nearest Exit from Entrance in Maze
//
// https://leetcode.com/problems/nearest-exit-from-entrance-in-maze/
//
// Question ID: 1926
// Difficult  : Medium
// Solve Date : 2022/03/15 18:42

#include <array>
#include <iosfwd>
#include <queue>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1926. Nearest Exit from Entrance in Maze|:
//
// You are given an |m x n| matrix |maze| (0-indexed) with empty cells
// (represented as |'.'|) and walls (represented as |'+'|). You are also given
// the |entrance| of the maze, where |entrance = [entrance^{row},
// entrance^{col}]| denotes the row and column of the cell you are initially
// standing at. In one step, you can move one cell up, down, left, or right. You
// cannot step into a cell with a wall, and you cannot step outside the maze.
// Your goal is to find the nearest exit from the |entrance|. An exit is defined
// as an empty cell that is at the border of the |maze|. The |entrance| does not
// count as an exit. Return the number of steps in the shortest path from the
// |entrance| to the nearest exit, or |-1| if no such path exists.  
//

LEETCODE_BEGIN_RESOLVING(1926, NearestExitFromEntranceInMaze, Solution);

class Solution {
private:
  int                            m, n;
  constexpr static array<int, 8> dir = {1, 0, 0, 1, -1, 0, 0, -1};

  inline bool is_valid(int x, int y) {
    return x >= 0 && x < m && y >= 0 && y < n;
  }

  inline bool is_bound(int x, int y) {
    return x == 0 || x == m - 1 || y == 0 || y == n - 1;
  }

public:
  int nearestExit(vector<vector<char>> &maze, vector<int> &entrance) {
    m = maze.size();
    n = maze[0].size();

    int                   res = 0;
    queue<pair<int, int>> q;
    q.emplace(entrance[0], entrance[1]);
    maze[q.front().first][q.front().second] = '+';

    while (!q.empty()) {
      auto temp = move(q);
      ++res;

      while (!temp.empty()) {
        auto [x, y] = temp.front();
        temp.pop();

        for (int i = 0; i < dir.size(); ++i) {
          int dx = x + dir[i], dy = y + dir[++i];

          if (is_valid(dx, dy) && maze[dx][dy] == '.') {
            if (is_bound(dx, dy)) {
              return res;
            } else {
              q.emplace(dx, dy);
              maze[dx][dy] = '+';
            }
          }
        }
      }
    }

    return -1;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |maze.length == m|
// * |maze[i].length == n|
// * |1 <= m, n <= 100|
// * |maze[i][j]| is either |'.'| or |'+'|.
// * |entrance.length == 2|
// * |0 <= entrance^{row} < m|
// * |0 <= entrance^{col} < n|
// * |entrance| will always be an empty cell.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: maze = [["+","+",".","+"],[".",".",".","+"],["+","+","+","."]],
//  entrance = [1,2]
// Output: 1
//
// There are 3 exits in this maze at [1,0], [0,2], and [2,3].
// Initially, you are at the entrance cell [1,2].
// - You can reach [1,0] by moving 2 steps left.
// - You can reach [0,2] by moving 1 step up.
// It is impossible to reach [2,3] from the entrance.
// Thus, the nearest exit is [0,2], which is 1 step away.

LEETCODE_SOLUTION_UNITTEST(1926, NearestExitFromEntranceInMaze, example_1) {
  auto                 solution = MakeSolution();
  vector<vector<char>> maze     = {
      {'+', '+', '.', '+'},
      {'.', '.', '.', '+'},
      {'+', '+', '+', '.'}
  };
  vector<int> entrance = {1, 2};
  int         expect   = 1;
  int         actual   = solution->nearestExit(maze, entrance);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: maze = [["+","+","+"],[".",".","."],["+","+","+"]], entrance = [1,0]
// Output: 2
//
// There is 1 exit in this maze at [1,2].
// [1,0] does not count as an exit since it is the entrance cell.
// Initially, you are at the entrance cell [1,0].
// - You can reach [1,2] by moving 2 steps right.
// Thus, the nearest exit is [1,2], which is 2 steps away.

LEETCODE_SOLUTION_UNITTEST(1926, NearestExitFromEntranceInMaze, example_2) {
  auto                 solution = MakeSolution();
  vector<vector<char>> maze     = {
      {'+', '+', '+'},
      {'.', '.', '.'},
      {'+', '+', '+'}
  };
  vector<int> entrance = {1, 0};
  int         expect   = 2;
  int         actual   = solution->nearestExit(maze, entrance);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: maze = [[".","+"]], entrance = [0,0]
// Output: -1
//
// There are no exits in this maze.

LEETCODE_SOLUTION_UNITTEST(1926, NearestExitFromEntranceInMaze, example_3) {
  auto                 solution = MakeSolution();
  vector<vector<char>> maze     = {
      {'.', '+'}
  };
  vector<int> entrance = {0, 0};
  int         expect   = -1;
  int         actual   = solution->nearestExit(maze, entrance);
  LCD_EXPECT_EQ(expect, actual);
}
