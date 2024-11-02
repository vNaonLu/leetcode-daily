// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Reconstruct a 2-Row Binary Matrix
//
// https://leetcode.com/problems/reconstruct-a-2-row-binary-matrix/
//
// Question ID: 1253
// Difficult  : Medium
// Solve Date : 2024/11/02 12:54

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1253. Reconstruct a 2-Row Binary Matrix|:
//
// Given the following details of a matrix with |n| columns and |2| rows :
//
//  • The matrix is a binary matrix, which means each element in the matrix can
//  be |0| or |1|.
//
//  • The sum of elements of the 0-th(upper) row is given as |upper|.
//
//  • The sum of elements of the 1-st(lower) row is given as |lower|.
//
//  • The sum of elements in the i-th column(0-indexed) is |colsum[i]|, where
//  |colsum| is given as an integer array with length |n|.
// Your task is to reconstruct the matrix with |upper|, |lower| and |colsum|.
// Return it as a 2-D integer array.
// If there are more than one valid solution, any of them will be accepted.
// If no valid solution exists, return an empty 2-D array.
//
//

LEETCODE_BEGIN_RESOLVING(1253, ReconstructA2RowBinaryMatrix, Solution);

class Solution {
public:
  vector<vector<int>> reconstructMatrix(int upper, int lower,
                                        vector<int> &colsum) {
    vector<vector<int>> res(2, vector<int>(colsum.size()));
    for (int i = 0; i < colsum.size(); ++i) {
      if (colsum[i] == 1) {
        if (upper > lower) {
          res[0][i] = 1;
          --upper;
        } else {
          res[1][i] = 1;
          --lower;
        }
      } else if (colsum[i] == 2) {
        res[0][i] = 1;
        res[1][i] = 1;
        --upper;
        --lower;
      }

      if (upper < 0 || lower < 0) {
        return {};
      }
    }

    if (upper != 0 || lower != 0) {
      return {};
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= colsum.length <= 10^5|
// * |0 <= upper, lower <= colsum.length|
// * |0 <= colsum[i] <= 2|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: upper = 2, lower = 1, colsum = [1,1,1]
// Output: [[1,1,0],[0,0,1]]
//

LEETCODE_SOLUTION_UNITTEST(1253, ReconstructA2RowBinaryMatrix, example_1) {
  auto                solution = MakeSolution();
  int                 upper    = 2;
  int                 lower    = 1;
  vector<int>         colsum   = {1, 1, 1};
  vector<vector<int>> expect   = {
      {1, 0, 1},
      {0, 1, 0}
  };
  vector<vector<int>> actual =
      solution->reconstructMatrix(upper, lower, colsum);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: upper = 2, lower = 3, colsum = [2,2,1,1]
// Output: []
//

LEETCODE_SOLUTION_UNITTEST(1253, ReconstructA2RowBinaryMatrix, example_2) {
  auto                solution = MakeSolution();
  int                 upper    = 2;
  int                 lower    = 3;
  vector<int>         colsum   = {2, 2, 1, 1};
  vector<vector<int>> expect   = {};
  vector<vector<int>> actual =
      solution->reconstructMatrix(upper, lower, colsum);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: upper = 5, lower = 5, colsum = [2,1,2,0,1,0,1,2,0,1]
// Output: [[1,1,1,0,1,0,0,1,0,0],[1,0,1,0,0,0,1,1,0,1]]
//

LEETCODE_SOLUTION_UNITTEST(1253, ReconstructA2RowBinaryMatrix, example_3) {
  auto                solution = MakeSolution();
  int                 upper    = 5;
  int                 lower    = 5;
  vector<int>         colsum   = {2, 1, 2, 0, 1, 0, 1, 2, 0, 1};
  vector<vector<int>> expect   = {
      {1, 0, 1, 0, 1, 0, 0, 1, 0, 1},
      {1, 1, 1, 0, 0, 0, 1, 1, 0, 0}
  };
  vector<vector<int>> actual =
      solution->reconstructMatrix(upper, lower, colsum);
  LCD_EXPECT_EQ(expect, actual);
}
