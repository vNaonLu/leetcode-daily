// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Spiral Matrix II
//
// https://leetcode.com/problems/spiral-matrix-ii/
//
// Question ID: 59
// Difficult  : Medium
// Solve Date : 2021/09/21 08:00

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |59. Spiral Matrix II|:
//
// Given a positive integer |n|, generate an |n x n| |matrix| filled with
// elements from |1| to |n²| in spiral order.  
//

LEETCODE_BEGIN_RESOLVING(59, SpiralMatrixII, Solution);

class Solution {
public:
  vector<vector<int>> generateMatrix(int n) {
    vector<vector<int>> res(n, vector<int>(n, 0));
    int                 cnt = 0;
    for (int i = 0; i < (n + 1) / 2; ++i) {
      for (int j = i; j < n - i; ++j)
        res[i][j] = ++cnt;
      for (int j = i + 1; j < n - i; ++j)
        res[j][n - i - 1] = ++cnt;
      for (int j = n - i - 2; j >= i; --j)
        res[n - i - 1][j] = ++cnt;
      for (int j = n - i - 2; j > i; --j)
        res[j][i] = ++cnt;
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= n <= 20|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: n = 3
// Output: [[1,2,3],[8,9,4],[7,6,5]]
//

LEETCODE_SOLUTION_UNITTEST(59, SpiralMatrixII, example_1) {
  auto                solution = MakeSolution();
  int                 n        = 3;
  vector<vector<int>> expect   = {
      {1, 2, 3},
      {8, 9, 4},
      {7, 6, 5}
  };
  vector<vector<int>> actual = solution->generateMatrix(n);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: n = 1
// Output: [[1]]
//

LEETCODE_SOLUTION_UNITTEST(59, SpiralMatrixII, example_2) {
  auto                solution = MakeSolution();
  int                 n        = 1;
  vector<vector<int>> expect   = {{1}};
  vector<vector<int>> actual   = solution->generateMatrix(n);
  LCD_EXPECT_EQ(expect, actual);
}
