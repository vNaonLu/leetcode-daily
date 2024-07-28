// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Find Valid Matrix Given Row and Column Sums
//
// https://leetcode.com/problems/find-valid-matrix-given-row-and-column-sums/
//
// Question ID: 1605
// Difficult  : Medium
// Solve Date : 2024/07/20 14:11

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1605. Find Valid Matrix Given Row and Column Sums|:
//
// You are given two arrays |rowSum| and |colSum| of non-negative integers where
// |rowSum[i]| is the sum of the elements in the |iᵗʰ| row and |colSum[j]| is
// the sum of the elements of the |jᵗʰ| column of a 2D matrix. In other words,
// you do not know the elements of the matrix, but you do know the sums of each
// row and column. Find any matrix of non-negative integers of size
// |rowSum.length x colSum.length| that satisfies the |rowSum| and |colSum|
// requirements. Return a 2D array representing any matrix that fulfills the
// requirements. It's guaranteed that at least one matrix that fulfills the
// requirements exists.
//
//

LEETCODE_BEGIN_RESOLVING(1605, FindValidMatrixGivenRowAndColumnSums, Solution);

class Solution {
public:
  vector<vector<int>> restoreMatrix(vector<int> &rowSum, vector<int> &colSum) {
    int                 m = rowSum.size();
    int                 n = colSum.size();
    vector<vector<int>> res(m, vector<int>(n));
    for (int i = 0; i < m; ++i) {
      for (int j = 0; j < n; ++j) {
        res[i][j] = min(rowSum[i], colSum[j]);
        rowSum[i] -= res[i][j];
        colSum[j] -= res[i][j];
      }
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= rowSum.length, colSum.length <= 500|
// * |0 <= rowSum[i], colSum[i] <= 10⁸|
// * |sum(rowSum) == sum(colSum)|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: rowSum = [3,8], colSum = [4,7]
// Output: [[3,0],
//  [1,7]]
//

LEETCODE_SOLUTION_UNITTEST(1605, FindValidMatrixGivenRowAndColumnSums,
                           example_1) {
  auto                solution = MakeSolution();
  vector<int>         rowSum   = {3, 8};
  vector<int>         colSum   = {4, 7};
  vector<vector<int>> expect   = {
      {3, 0},
      {1, 7}
  };
  vector<vector<int>> actual = solution->restoreMatrix(rowSum, colSum);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: rowSum = [5,7,10], colSum = [8,6,8]
// Output: [[0,5,0],
//  [6,1,0],
//  [2,0,8]]
//

LEETCODE_SOLUTION_UNITTEST(1605, FindValidMatrixGivenRowAndColumnSums,
                           example_2) {
  auto                solution = MakeSolution();
  vector<int>         rowSum   = {5, 7, 10};
  vector<int>         colSum   = {8, 6, 8};
  vector<vector<int>> expect   = {
      {5, 0, 0},
      {3, 4, 0},
      {0, 2, 8}
  };
  vector<vector<int>> actual = solution->restoreMatrix(rowSum, colSum);
  LCD_EXPECT_EQ(expect, actual);
}
