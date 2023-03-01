// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Transform to Chessboard
//
// https://leetcode.com/problems/transform-to-chessboard/
//
// Question ID: 782
// Difficult  : Hard
// Solve Date : 2021/09/26 18:44

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |782. Transform to Chessboard|:
//
// You are given an |n x n| binary grid |board|. In each move, you can swap any
// two rows with each other, or any two columns with each other. Return the
// minimum number of moves to transform the board into a chessboard board. If
// the task is impossible, return |-1|. A chessboard board is a board where no
// |0|'s and no |1|'s are 4-directionally adjacent.  
//

LEETCODE_BEGIN_RESOLVING(782, TransformToChessboard, Solution);

class Solution {
private:
  int isRawSame(const vector<vector<int>> &vec, const int &a, const int &b) {
    for (int col = 0; col < vec[a].size(); ++col) {
      if (vec[a][col] != vec[b][col]) {
        return false;
      }
    }
    return true;
  }
  int minSwap(const vector<int> &vec) {
    int ans1 = 0;
    int ans2 = 0;
    for (int i = 0; i < vec.size(); ++i) {
      if (vec[i] != i % 2) {
        ++ans1;
      }
      if (vec[i] != (i + 1) % 2) {
        ++ans2;
      }
    }
    if (ans1 % 2 != 0) {
      return ans2 / 2;
    } else if (ans2 % 2 != 0) {
      return ans1 / 2;
    } else {
      return min(ans1 / 2, ans2 / 2);
    }
  }
  int isValid(const vector<int> &vec) {
    int c1 = 0;
    int c2 = 0;
    for (const auto &v : vec) {
      v == 0 ? ++c1 : ++c2;
    }
    return abs(c1 - c2) <= 1;
  }
  int findRawDiff(const vector<vector<int>> &board, vector<int> &diffRaw,
                  vector<int> &raw) {
    diffRaw.push_back(0);
    for (int i = 1; i < board.size(); ++i) {
      int d = 0;
      for (d = 0; d < diffRaw.size(); ++d) {
        if (isRawSame(board, i, diffRaw[d]))
          break;
      }
      if (d > 1) {
        return -1;
      } else if (d == diffRaw.size()) {
        diffRaw.push_back(i);
      }
      raw[i] = d;
    }
    return 1;
  }

public:
  int movesToChessboard(vector<vector<int>> &board) {
    int         n = board.size();
    vector<int> raw(n, 0), col(n, 0);
    vector<int> diffRaw, diffCol;
    if (findRawDiff(board, diffRaw, raw) == -1)
      return -1;
    vector<vector<int>> tBoard(n, vector<int>(n));
    for (int i = 0; i < board.size(); ++i) {
      for (int j = 0; j < board.size(); ++j) {
        tBoard[j][i] = board[i][j];
      }
    }
    if (findRawDiff(tBoard, diffCol, col) == -1)
      return -1;
    if (diffRaw.size() != 2 || diffCol.size() != 2 || !isValid(raw) ||
        !isValid(col))
      return -1;
    return minSwap(raw) + minSwap(col);
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |n == board.length|
// * |n == board[i].length|
// * |2 <= n <= 30|
// * |board[i][j]| is either  |0| or |1|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: board = [[0,1,1,0],[0,1,1,0],[1,0,0,1],[1,0,0,1]]
// Output: 2
//
// One potential sequence of moves is shown.
// The first move swaps the first and second column.
// The second move swaps the second and third row.

LEETCODE_SOLUTION_UNITTEST(782, TransformToChessboard, example_1) {
  auto                solution = MakeSolution();
  vector<vector<int>> board    = {
      {0, 1, 1, 0},
      {0, 1, 1, 0},
      {1, 0, 0, 1},
      {1, 0, 0, 1}
  };
  int expect = 2;
  int actual = solution->movesToChessboard(board);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: board = [[0,1],[1,0]]
// Output: 0
//
// Also note that the board with 0 in the top left corner, is also a valid
// chessboard.

LEETCODE_SOLUTION_UNITTEST(782, TransformToChessboard, example_2) {
  auto                solution = MakeSolution();
  vector<vector<int>> board    = {
      {0, 1},
      {1, 0}
  };
  int expect = 0;
  int actual = solution->movesToChessboard(board);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: board = [[1,0],[1,0]]
// Output: -1
//
// No matter what sequence of moves you make, you cannot end with a valid
// chessboard.

LEETCODE_SOLUTION_UNITTEST(782, TransformToChessboard, example_3) {
  auto                solution = MakeSolution();
  vector<vector<int>> board    = {
      {1, 0},
      {1, 0}
  };
  int expect = -1;
  int actual = solution->movesToChessboard(board);
  LCD_EXPECT_EQ(expect, actual);
}
