// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Delete Greatest Value in Each Row
//
// https://leetcode.com/problems/delete-greatest-value-in-each-row/
//
// Question ID: 2500
// Difficult  : Easy
// Solve Date : 2023/05/03 19:02

#include <algorithm>
#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2500. Delete Greatest Value in Each Row|:
//
// You are given an |m x n| matrix |grid| consisting of positive integers.
// Perform the following operation until |grid| becomes empty:
//
//  • Delete the element with the greatest value from each row. If multiple such
//  elements exist, delete any of them.
//
//  • Add the maximum of deleted elements to the answer.
// Note that the number of columns decreases by one after each operation.
// Return the answer after performing the operations described above.
//
//

LEETCODE_BEGIN_RESOLVING(2500, DeleteGreatestValueInEachRow, Solution);

class Solution {
public:
  int deleteGreatestValue(vector<vector<int>> &grid) {
    int m   = grid.size();
    int n   = grid[0].size();
    int res = 0;
    for (auto &v : grid) {
      sort(v.begin(), v.end());
    }
    for (int i = 0; i < n; ++i) {
      int mx = 0;
      for (int j = 0; j < m; ++j) {
        mx = max(mx, grid[j][i]);
      }
      res += mx;
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |m == grid.length|
// * |n == grid[i].length|
// * |1 <= m, n <= 50|
// * |1 <= grid[i][j] <= 100|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: grid = [[1,2,4],[3,3,1]]
// Output: 8
//
// The diagram above shows the removed values in each step.
// - In the first operation, we remove 4 from the first row and 3 from the
// second row (notice that, there are two cells with value 3 and we can remove
// any of them). We add 4 to the answer.
// - In the second operation, we remove 2 from the first row and 3 from the
// second row. We add 3 to the answer.
// - In the third operation, we remove 1 from the first row and 1 from the
// second row. We add 1 to the answer. The final answer = 4 + 3 + 1 = 8.

LEETCODE_SOLUTION_UNITTEST(2500, DeleteGreatestValueInEachRow, example_1) {
  auto                solution = MakeSolution();
  vector<vector<int>> grid     = {
      {1, 2, 4},
      {3, 3, 1}
  };
  int expect = 8;
  int actual = solution->deleteGreatestValue(grid);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: grid = [[10]]
// Output: 10
//
// The diagram above shows the removed values in each step.
// - In the first operation, we remove 10 from the first row. We add 10 to the
// answer. The final answer = 10.

LEETCODE_SOLUTION_UNITTEST(2500, DeleteGreatestValueInEachRow, example_2) {
  auto                solution = MakeSolution();
  vector<vector<int>> grid     = {{10}};
  int                 expect   = 10;
  int                 actual   = solution->deleteGreatestValue(grid);
  LCD_EXPECT_EQ(expect, actual);
}
