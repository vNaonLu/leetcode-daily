// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Row With Maximum Ones
//
// https://leetcode.com/problems/row-with-maximum-ones/
//
// Question ID: 2643
// Difficult  : Easy
// Solve Date : 2023/05/09 20:03

#include <algorithm>
#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2643. Row With Maximum Ones|:
//
// Given a |m x n| binary matrix |mat|, find the 0-indexed position of the row
// that contains the maximum count of ones, and the number of ones in that row.
// In case there are multiple rows that have the maximum count of ones, the row
// with the smallest row number should be selected. Return an array containing
// the index of the row, and the number of ones in it.
//
//

LEETCODE_BEGIN_RESOLVING(2643, RowWithMaximumOnes, Solution);

class Solution {
public:
  vector<int> rowAndMaximumOnes(vector<vector<int>> &mat) {
    vector<int> res{-1, -1};
    for (int i = 0; i < mat.size(); ++i) {
      auto cnt = count(mat[i].begin(), mat[i].end(), 1);
      if (cnt > res[1]) {
        res[0] = i;
        res[1] = cnt;
      }
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |m == mat.length|
// * |n == mat[i].length|
// * |1 <= m, n <= 100|
// * |mat[i][j]| is either |0| or |1|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: mat = [[0,1],[1,0]]
// Output: [0,1]
//
// Both rows have the same number of 1's. So we return the index of the smaller
// row, 0, and the maximum count of ones (1 |)|. So, the answer is [0,1].

LEETCODE_SOLUTION_UNITTEST(2643, RowWithMaximumOnes, example_1) {
  auto                solution = MakeSolution();
  vector<vector<int>> mat      = {
      {0, 1},
      {1, 0}
  };
  vector<int> expect = {0, 1};
  vector<int> actual = solution->rowAndMaximumOnes(mat);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: mat = [[0,0,0],[0,1,1]]
// Output: [1,2]
//
// The row indexed 1 has the maximum count of ones |(2)|. So we return its
// index, |1|, and the count. So, the answer is [1,2].

LEETCODE_SOLUTION_UNITTEST(2643, RowWithMaximumOnes, example_2) {
  auto                solution = MakeSolution();
  vector<vector<int>> mat      = {
      {0, 0, 0},
      {0, 1, 1}
  };
  vector<int> expect = {1, 2};
  vector<int> actual = solution->rowAndMaximumOnes(mat);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: mat = [[0,0],[1,1],[0,0]]
// Output: [1,2]
//
// The row indexed 1 has the maximum count of ones (2). So the answer is [1,2].

LEETCODE_SOLUTION_UNITTEST(2643, RowWithMaximumOnes, example_3) {
  auto                solution = MakeSolution();
  vector<vector<int>> mat      = {
      {0, 0},
      {1, 1},
      {0, 0}
  };
  vector<int> expect = {1, 2};
  vector<int> actual = solution->rowAndMaximumOnes(mat);
  LCD_EXPECT_EQ(expect, actual);
}
