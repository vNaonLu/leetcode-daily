// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Surrounded Regions
//
// https://leetcode.com/problems/surrounded-regions/
//
// Question ID: 130
// Difficult  : Medium
// Solve Date : 2021/09/26 15:27

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |130. Surrounded Regions|:
//
// Given an |m x n| matrix |board| containing |'X'| and |'O'|, capture all
// regions that are 4-directionally surrounded by |'X'|. A region is captured by
// flipping all |'O'|s into |'X'|s in that surrounded region.  
//

LEETCODE_BEGIN_RESOLVING(130, SurroundedRegions, Solution);

class Solution {
private:
  int                  m = 0, n = 0;
  vector<int>          direct = {1, 0, 0, 1, -1, 0, 0, -1};
  vector<vector<bool>> visit;
  bool                 isSurreounded(const vector<vector<char>> &board,
                                     vector<pair<int, int>>     &path) {
    bool res = true;
    int  beg = 0;
    char val = board[path[0].first][path[0].second];
    visit[path[0].first][path[0].second] = true;
    while (beg < path.size()) {
      int len = path.size() - beg;
      while (len--) {
        auto c = path[beg++];
        if (c.first == 0 || c.first == m - 1 || c.second == 0 ||
            c.second == n - 1)
          res = false;
        for (int i = 0; i < direct.size(); i++) {
          int x = c.first + direct[i];
          int y = c.second + direct[++i];
          if (x >= 0 && x < m && y >= 0 && y < n && board[x][y] == val &&
              !visit[x][y]) {
            visit[x][y] = true;
            path.emplace_back(x, y);
          }
        }
      }
    }
    return res;
  }

public:
  void solve(vector<vector<char>> &board) {
    m = board.size();
    n = board[0].size();
    visit.resize(m, vector<bool>(n, false));
    for (int i = 0; i < m; ++i) {
      for (int j = 0; j < n; ++j) {
        if (i > 0 && i < m - 1 && j > 0 && j < n - 1 && board[i][j] == 'O' &&
            !visit[i][j]) {
          int                    beg = 0;
          vector<pair<int, int>> path;
          path.emplace_back(i, j);
          if (isSurreounded(board, path)) {
            for (const auto &cur : path) {
              board[cur.first][cur.second] = 'X';
            }
          }
        }
      }
    }
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |m == board.length|
// * |n == board[i].length|
// * |1 <= m, n <= 200|
// * |board[i][j]| is |'X'| or |'O'|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: board =
//  [["X","X","X","X"],["X","O","O","X"],["X","X","O","X"],["X","O","X","X"]]
// Output:
// [["X","X","X","X"],["X","X","X","X"],["X","X","X","X"],["X","O","X","X"]]
//
// Notice that an 'O' should not be flipped if:
// - It is on the border, or
// - It is adjacent to an 'O' that should not be flipped.
// The bottom 'O' is on the border, so it is not flipped.
// The other three 'O' form a surrounded region, so they are flipped.

LEETCODE_SOLUTION_UNITTEST(130, SurroundedRegions, example_1) {
  auto                 solution = MakeSolution();
  vector<vector<char>> board    = {
      {'X', 'X', 'X', 'X'},
      {'X', 'O', 'O', 'X'},
      {'X', 'X', 'O', 'X'},
      {'X', 'O', 'X', 'X'}
  };
  vector<vector<char>> expect = {
      {'X', 'X', 'X', 'X'},
      {'X', 'X', 'X', 'X'},
      {'X', 'X', 'X', 'X'},
      {'X', 'O', 'X', 'X'}
  };
  solution->solve(board);
  LCD_EXPECT_EQ(expect, board);
}

// [Example #2]
//  Input: board = [["X"]]
// Output: [["X"]]
//

LEETCODE_SOLUTION_UNITTEST(130, SurroundedRegions, example_2) {
  auto                 solution = MakeSolution();
  vector<vector<char>> board    = {{'X'}};
  vector<vector<char>> expect   = {{'X'}};
  solution->solve(board);
  LCD_EXPECT_EQ(expect, board);
}
