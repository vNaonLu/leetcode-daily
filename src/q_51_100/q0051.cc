// Copyright 2023 Naon Lu
//
// This file describes the solution of
// N-Queens
//
// https://leetcode.com/problems/n-queens/
//
// Question ID: 51
// Difficult  : Hard
// Solve Date : 2022/02/26 23:32

#include <iosfwd>
#include <set>
#include <string>
#include <unordered_set>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |51. N-Queens|:
//
// The n-queens puzzle is the problem of placing |n| queens on an |n x n|
// chessboard such that no two queens attack each other. Given an integer |n|,
// return all distinct solutions to the n-queens puzzle. You may return the
// answer in any order. Each solution contains a distinct board configuration of
// the n-queens' placement, where |'Q'| and |'.'| both indicate a queen and an
// empty space, respectively.  
//

LEETCODE_BEGIN_RESOLVING(51, NQueens, Solution);

class Solution {
private:
  int                    n;
  vector<vector<string>> res;
  unordered_set<int>     occupy_col;
  bool                   validate(vector<string> &curr, int x, int y) {
    /// check diagonal
    int dx = x - 1, dy = y - 1;
    while (dx >= 0 && dy >= 0) {
      if (curr[dx][dy] != '.')
        return false;
      --dx;
      --dy;
    }
    dx = x + 1, dy = y + 1;
    while (dx < n && dy < n) {
      if (curr[dx][dy] != '.')
        return false;
      ++dx;
      ++dy;
    }
    dx = x - 1, dy = y + 1;
    while (dx >= 0 && dy < n) {
      if (curr[dx][dy] != '.')
        return false;
      --dx;
      ++dy;
    }
    dx = x + 1, dy = y - 1;
    while (dx < n && dy >= 0) {
      if (curr[dx][dy] != '.')
        return false;
      ++dx;
      --dy;
    }
    return true;
  }

  void solver(vector<string> &curr, int queens = 0, int row = 0) {
    if (queens == n) {
      res.emplace_back(curr);
      return;
    }

    for (int i = 0; i < n; ++i) {
      if (occupy_col.count(i))
        continue;
      curr[row][i] = 'Q';
      if (queens == 0 || validate(curr, row, i)) {
        occupy_col.emplace(i);
        solver(curr, queens + 1, row + 1);
        occupy_col.erase(i);
      }
      curr[row][i] = '.';
    }
  }

public:
  vector<vector<string>> solveNQueens(int n) {
    res.clear();
    this->n = n;

    string temp;
    for (int i = 0; i < n; ++i) {
      temp.push_back('.');
    }
    vector<string> board(n, temp);
    solver(board);

    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= n <= 9|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: n = 4
// Output: [[".Q..","...Q","Q...","..Q."],["..Q.","Q...","...Q",".Q.."]]
//
// There exist two distinct solutions to the 4-queens puzzle as shown above

LEETCODE_SOLUTION_UNITTEST(51, NQueens, example_1) {
  auto                   solution = MakeSolution();
  int                    n        = 4;
  vector<vector<string>> expect   = {
      {".Q..", "...Q", "Q...", "..Q."},
      {"..Q.", "Q...", "...Q", ".Q.."}
  };
  vector<vector<string>> actual = solution->solveNQueens(n);
  EXPECT_ANYORDER_EQ(expect, actual);
}

// [Example #2]
//  Input: n = 1
// Output: [["Q"]]
//

LEETCODE_SOLUTION_UNITTEST(51, NQueens, example_2) {
  auto                   solution = MakeSolution();
  int                    n        = 1;
  vector<vector<string>> expect   = {{"Q"}};
  vector<vector<string>> actual   = solution->solveNQueens(n);
  EXPECT_ANYORDER_EQ(expect, actual);
}
