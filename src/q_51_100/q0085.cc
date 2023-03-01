// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Maximal Rectangle
//
// https://leetcode.com/problems/maximal-rectangle/
//
// Question ID: 85
// Difficult  : Hard
// Solve Date : 2021/11/30 18:19

#include <iosfwd>
#include <stack>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |85. Maximal Rectangle|:
//
// Given a |rows x cols| binary |matrix| filled with |0|'s and |1|'s, find the
// largest rectangle containing only |1|'s and return its area.  
//

LEETCODE_BEGIN_RESOLVING(85, MaximalRectangle, Solution);

class Solution {
public:
  int maximalRectangle(vector<vector<char>> &matrix) {
    if (matrix.empty())
      return 0;
    int                 m = matrix.size(), n = matrix[0].size();
    vector<vector<int>> grid(m, vector<int>(n, 0));
    int                 area = 0;
    for (int i = 0; i < m; ++i) {
      for (int j = 0; j < n; ++j) {
        if (i == 0) {
          grid[i][j] = matrix[i][j] - '0';
        } else {
          if (matrix[i][j] == '0')
            grid[i][j] = 0;
          else
            grid[i][j] = 1 + grid[i - 1][j];
        }
      }
      vector<int> left(n), right(n);
      stack<int>  stk;
      for (int j = 0; j < n; ++j) {
        int cur = grid[i][j];
        while (!stk.empty() && grid[i][stk.top()] >= cur)
          stk.pop();
        if (stk.empty())
          left[j] = -1;
        else
          left[j] = stk.top();
        stk.emplace(j);
      }
      stk = {};
      for (int j = n - 1; j >= 0; --j) {
        int cur = grid[i][j];
        while (!stk.empty() && grid[i][stk.top()] >= cur)
          stk.pop();
        if (stk.empty())
          right[j] = n;
        else
          right[j] = stk.top();
        stk.emplace(j);
      }
      for (int j = 0; j < n; ++j)
        area = max(area, (grid[i][j] * (right[j] - left[j] - 1)));
    }
    return area;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |rows == matrix.length|
// * |cols == matrix[i].length|
// * |1 <= row, cols <= 200|
// * |matrix[i][j]| is |'0'| or |'1'|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: matrix =
//  [["1","0","1","0","0"],["1","0","1","1","1"],["1","1","1","1","1"],["1","0","0","1","0"]]
// Output: 6
//
// The maximal rectangle is shown in the above picture.

LEETCODE_SOLUTION_UNITTEST(85, MaximalRectangle, example_1) {
  auto                 solution = MakeSolution();
  vector<vector<char>> matrix   = {
      {'1', '0', '1', '0', '0'},
      {'1', '0', '1', '1', '1'},
      {'1', '1', '1', '1', '1'},
      {'1', '0', '0', '1', '0'}
  };
  int expect = 6;
  int actual = solution->maximalRectangle(matrix);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: matrix = [["0"]]
// Output: 0
//

LEETCODE_SOLUTION_UNITTEST(85, MaximalRectangle, example_2) {
  auto                 solution = MakeSolution();
  vector<vector<char>> matrix   = {{'0'}};
  int                  expect   = 0;
  int                  actual   = solution->maximalRectangle(matrix);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: matrix = [["1"]]
// Output: 1
//

LEETCODE_SOLUTION_UNITTEST(85, MaximalRectangle, example_3) {
  auto                 solution = MakeSolution();
  vector<vector<char>> matrix   = {{'1'}};
  int                  expect   = 1;
  int                  actual   = solution->maximalRectangle(matrix);
  LCD_EXPECT_EQ(expect, actual);
}
