// Copyright 2025 Naon Lu
//
// This file describes the solution of
// Increment Submatrices by One
//
// https://leetcode.com/problems/increment-submatrices-by-one/
//
// Question ID: 2536
// Difficult  : Medium
// Solve Date : 2025/11/14 13:04

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2536. Increment Submatrices by One|:
//
// You are given a positive integer |n|, indicating that we initially have an |n
// x n| 0-indexed integer matrix |mat| filled with zeroes. You are also given a
// 2D integer array |query|. For each |query[i] = [row1ᵢ, col1ᵢ, row2ᵢ, col2ᵢ]|,
// you should do the following operation:
//
//  • Add |1| to every element in the submatrix with the top left corner
//  |(row1ᵢ, col1ᵢ)| and the bottom right corner |(row2ᵢ, col2ᵢ)|. That is, add
//  |1| to |mat[x][y]| for all |row1ᵢ <= x <= row2ᵢ| and |col1ᵢ <= y <= col2ᵢ|.
// Return the matrix |mat| after performing every query.
//
//

LEETCODE_BEGIN_RESOLVING(2536, IncrementSubmatricesByOne, Solution);

class Solution {
public:
  vector<vector<int>> rangeAddQueries(int n, vector<vector<int>> &queries) {
    vector<vector<int>> diff(n + 1, vector<int>(n + 1, 0));
    for (auto &v : queries) {
      diff[v[0]][v[1]]++;
      diff[v[2] + 1][v[1]]--;
      diff[v[0]][v[3] + 1]--;
      diff[v[2] + 1][v[3] + 1]++;
    }
    vector<vector<int>> res(n, vector<int>(n));
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        int above = i > 0 ? res[i - 1][j] : 0;
        int left  = j > 0 ? res[i][j - 1] : 0;
        int diag  = (i > 0 && j > 0) ? res[i - 1][j - 1] : 0;
        res[i][j] = diff[i][j] + above + left - diag;
      }
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= n <= 500|
// * |1 <= queries.length <= 10⁴|
// * |0 <= row1ᵢ <= row2ᵢ < n|
// * |0 <= col1ᵢ <= col2ᵢ < n|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: n = 3, queries = [[1,1,2,2],[0,0,1,1]]
// Output: [[1,1,0],[1,2,1],[0,1,1]]
//

LEETCODE_SOLUTION_UNITTEST(2536, IncrementSubmatricesByOne, example_1) {
  auto                solution = MakeSolution();
  int                 n        = 3;
  vector<vector<int>> queries  = {
      {1, 1, 2, 2},
      {0, 0, 1, 1}
  };
  vector<vector<int>> expect = {
      {1, 1, 0},
      {1, 2, 1},
      {0, 1, 1}
  };
  vector<vector<int>> actual = solution->rangeAddQueries(n, queries);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: n = 2, queries = [[0,0,1,1]]
// Output: [[1,1],[1,1]]
//

LEETCODE_SOLUTION_UNITTEST(2536, IncrementSubmatricesByOne, example_2) {
  auto                solution = MakeSolution();
  int                 n        = 2;
  vector<vector<int>> queries  = {
      {0, 0, 1, 1}
  };
  vector<vector<int>> expect = {
      {1, 1},
      {1, 1}
  };
  vector<vector<int>> actual = solution->rangeAddQueries(n, queries);
  LCD_EXPECT_EQ(expect, actual);
}
