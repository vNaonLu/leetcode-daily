// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Equal Row and Column Pairs
//
// https://leetcode.com/problems/equal-row-and-column-pairs/
//
// Question ID: 2352
// Difficult  : Medium
// Solve Date : 2023/06/13 19:54

#include <iosfwd>
#include <map>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2352. Equal Row and Column Pairs|:
//
// Given a 0-indexed |n x n| integer matrix |grid|, return the number of pairs
// |(rᵢ, cⱼ)| such that row |rᵢ| and column |cⱼ| are equal. A row and column
// pair is considered equal if they contain the same elements in the same order
// (i.e., an equal array).
//
//

LEETCODE_BEGIN_RESOLVING(2352, EqualRowAndColumnPairs, Solution);

class Solution {
public:
  int equalPairs(vector<vector<int>> &grid) {
    int                   res = 0;
    int                   n   = grid.size();
    map<vector<int>, int> memo;
    for (int i = 0; i < n; ++i) {
      ++memo[grid[i]];
    }
    for (int i = 0; i < n; ++i) {
      vector<int> col;
      for (int j = 0; j < n; ++j) {
        col.emplace_back(grid[j][i]);
      }
      auto find = memo.find(col);
      if (find != memo.end()) {
        res += find->second;
      }
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |n == grid.length == grid[i].length|
// * |1 <= n <= 200|
// * |1 <= grid[i][j] <= 10⁵|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: grid = [[3,2,1],[1,7,6],[2,7,7]]
// Output: 1
//
// There is 1 equal row and column pair:
// - (Row 2, Column 1): [2,7,7]

LEETCODE_SOLUTION_UNITTEST(2352, EqualRowAndColumnPairs, example_1) {
  auto                solution = MakeSolution();
  vector<vector<int>> grid     = {
      {3, 2, 1},
      {1, 7, 6},
      {2, 7, 7}
  };
  int expect = 1;
  int actual = solution->equalPairs(grid);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: grid = [[3,1,2,2],[1,4,4,5],[2,4,2,2],[2,4,2,2]]
// Output: 3
//
// There are 3 equal row and column pairs:
// - (Row 0, Column 0): [3,1,2,2]
// - (Row 2, Column 2): [2,4,2,2]
// - (Row 3, Column 2): [2,4,2,2]

LEETCODE_SOLUTION_UNITTEST(2352, EqualRowAndColumnPairs, example_2) {
  auto                solution = MakeSolution();
  vector<vector<int>> grid     = {
      {3, 1, 2, 2},
      {1, 4, 4, 5},
      {2, 4, 2, 2},
      {2, 4, 2, 2}
  };
  int expect = 3;
  int actual = solution->equalPairs(grid);
  LCD_EXPECT_EQ(expect, actual);
}
