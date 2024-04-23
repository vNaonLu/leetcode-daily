// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Diagonal Traverse
//
// https://leetcode.com/problems/diagonal-traverse/
//
// Question ID: 498
// Difficult  : Medium
// Solve Date : 2024/04/21 16:59

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |498. Diagonal Traverse|:
//
// Given an |m x n| matrix |mat|, return an array of all the elements of the
// array in a diagonal order.
//
//

LEETCODE_BEGIN_RESOLVING(498, DiagonalTraverse, Solution);

class Solution {
public:
  vector<int> findDiagonalOrder(vector<vector<int>> &mat) {
    vector<int> res;
    int         m   = mat.size();
    int         n   = mat[0].size();
    int         i   = 0;
    int         j   = 0;
    int         dir = -1;
    res.emplace_back(mat[i][j]);
    while (i < m - 1 || j < n - 1) {
      if (j < n - 1 && ((i == 0 && dir == -1) || (i == m - 1 && dir == 1))) {
        ++j;
        dir *= -1;
      } else if ((j == 0 && dir == 1) || (j == n - 1 && dir == -1)) {
        ++i;
        dir *= -1;
      } else {
        i += dir;
        j -= dir;
      }
      res.emplace_back(mat[i][j]);
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |m == mat.length|
// * |n == mat[i].length|
// * |1 <= m, n <= 10⁴|
// * |1 <= m * n <= 10⁴|
// * |-10⁵ <= mat[i][j] <= 10⁵|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: mat = [[1,2,3],[4,5,6],[7,8,9]]
// Output: [1,2,4,7,5,3,6,8,9]
//

LEETCODE_SOLUTION_UNITTEST(498, DiagonalTraverse, example_1) {
  auto                solution = MakeSolution();
  vector<vector<int>> mat      = {
      {1, 2, 3},
      {4, 5, 6},
      {7, 8, 9}
  };
  vector<int> expect = {1, 2, 4, 7, 5, 3, 6, 8, 9};
  vector<int> actual = solution->findDiagonalOrder(mat);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: mat = [[1,2],[3,4]]
// Output: [1,2,3,4]
//

LEETCODE_SOLUTION_UNITTEST(498, DiagonalTraverse, example_2) {
  auto                solution = MakeSolution();
  vector<vector<int>> mat      = {
      {1, 2},
      {3, 4}
  };
  vector<int> expect = {1, 2, 3, 4};
  vector<int> actual = solution->findDiagonalOrder(mat);
  LCD_EXPECT_EQ(expect, actual);
}
