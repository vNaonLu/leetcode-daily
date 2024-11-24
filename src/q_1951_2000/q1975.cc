// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Maximum Matrix Sum
//
// https://leetcode.com/problems/maximum-matrix-sum/
//
// Question ID: 1975
// Difficult  : Medium
// Solve Date : 2024/11/24 14:54

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1975. Maximum Matrix Sum|:
//
// You are given an |n x n| integer |matrix|. You can do the following operation
// any number of times:
//
//  • Choose any two adjacent elements of |matrix| and multiply each of them by
//  |-1|.
// Two elements are considered adjacent if and only if they share a border.
// Your goal is to maximize the summation of the matrix's elements. Return the
// maximum sum of the matrix's elements using the operation mentioned above.
//
//

LEETCODE_BEGIN_RESOLVING(1975, MaximumMatrixSum, Solution);

class Solution {
public:
  long long maxMatrixSum(vector<vector<int>> &matrix) {
    int     mn  = numeric_limits<int>::max();
    int64_t res = 0;
    int     cnt = 0;
    for (int i = 0; i < matrix.size(); ++i) {
      for (int j = 0; j < matrix[0].size(); ++j) {
        if (matrix[i][j] < 0) {
          --cnt;
        }
        int a = abs(matrix[i][j]);
        mn    = min(mn, a);
        res += a;
      }
    }

    if (cnt % 2 == 0) {
      return res;
    }
    return res - 2 * mn;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |n == matrix.length == matrix[i].length|
// * |2 <= n <= 250|
// * |-10⁵ <= matrix[i][j] <= 10⁵|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: matrix = [[1,-1],[-1,1]]
// Output: 4
//

LEETCODE_SOLUTION_UNITTEST(1975, MaximumMatrixSum, example_1) {
  auto                solution = MakeSolution();
  vector<vector<int>> matrix   = {
      { 1, -1},
      {-1,  1}
  };
  long long expect = 4;
  long long actual = solution->maxMatrixSum(matrix);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: matrix = [[1,2,3],[-1,-2,-3],[1,2,3]]
// Output: 16
//

LEETCODE_SOLUTION_UNITTEST(1975, MaximumMatrixSum, example_2) {
  auto                solution = MakeSolution();
  vector<vector<int>> matrix   = {
      { 1,  2,  3},
      {-1, -2, -3},
      { 1,  2,  3}
  };
  long long expect = 16;
  long long actual = solution->maxMatrixSum(matrix);
  LCD_EXPECT_EQ(expect, actual);
}
