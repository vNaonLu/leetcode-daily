// Copyright 2026 Naon Lu
//
// This file describes the solution of
// Minimum Absolute Difference in Sliding Submatrix
//
// https://leetcode.com/problems/minimum-absolute-difference-in-sliding-submatrix/
//
// Question ID: 3567
// Difficult  : Medium
// Solve Date : 2026/03/20 19:22

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |3567. Minimum Absolute Difference in Sliding Submatrix|:
//
// You are given an |m x n| integer matrix |grid| and an integer |k|.
// For every contiguous |k x k| submatrix of |grid|, compute the minimum
// absolute difference between any two distinct values within that submatrix.
// Return a 2D array |ans| of size |(m - k + 1) x (n - k + 1)|, where
// |ans[i][j]| is the minimum absolute difference in the submatrix whose
// top-left corner is |(i, j)| in |grid|. Note: If all elements in the submatrix
// have the same value, the answer will be 0. A submatrix |(x1, y1, x2, y2)| is
// a matrix that is formed by choosing all cells |matrix[x][y]| where |x1 <= x
// <= x2| and |y1 <= y <= y2|.
//
//

LEETCODE_BEGIN_RESOLVING(3567, MinimumAbsoluteDifferenceInSlidingSubmatrix,
                         Solution);

class Solution {
public:
  vector<vector<int>> minAbsDiff(vector<vector<int>> &grid, int k) {
    int                 n = grid.size(), m = grid[0].size();
    vector<vector<int>> ans(n - k + 1, vector<int>(m - k + 1));
    for (int i = 0; i <= n - k; i++) {
      map<int, int> mp;
      for (int r = i; r < i + k; r++) {
        for (int c = 0; c < k; c++) {
          mp[grid[r][c]]++;
        }
      }
      for (int c = 0; c <= m - k; c++) {
        if (mp.size() > 1) {
          int  mini = 1e9;
          auto it   = mp.begin();
          int  prev = it->first;
          for (++it; it != mp.end(); it++) {
            mini = min(mini, abs(it->first - prev));
            prev = it->first;
          }
          ans[i][c] = mini;
        } else {
          ans[i][c] = 0;
        }

        if (c < m - k) {
          for (int r = i; r < i + k; r++) {
            mp[grid[r][c]]--;
            if (mp[grid[r][c]] == 0)
              mp.erase(grid[r][c]);
            mp[grid[r][c + k]]++;
          }
        }
      }
    }
    return ans;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= m == grid.length <= 30|
// * |1 <= n == grid[i].length <= 30|
// * |-10⁵ <= grid[i][j] <= 10⁵|
// * |1 <= k <= min(m, n)|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: grid = [[1,8],[3,-2]], k = 2
// Output: [[2]]
//

LEETCODE_SOLUTION_UNITTEST(3567, MinimumAbsoluteDifferenceInSlidingSubmatrix,
                           example_1) {
  auto                solution = MakeSolution();
  vector<vector<int>> grid     = {
      {1,  8},
      {3, -2}
  };
  int                 k      = 2;
  vector<vector<int>> expect = {{2}};
  vector<vector<int>> actual = solution->minAbsDiff(grid, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: grid = [[3,-1]], k = 1
// Output: [[0,0]]
//

LEETCODE_SOLUTION_UNITTEST(3567, MinimumAbsoluteDifferenceInSlidingSubmatrix,
                           example_2) {
  auto                solution = MakeSolution();
  vector<vector<int>> grid     = {
      {3, -1}
  };
  int                 k      = 1;
  vector<vector<int>> expect = {
      {0, 0}
  };
  vector<vector<int>> actual = solution->minAbsDiff(grid, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: grid = [[1,-2,3],[2,3,5]], k = 2
// Output: [[1,2]]
//

LEETCODE_SOLUTION_UNITTEST(3567, MinimumAbsoluteDifferenceInSlidingSubmatrix,
                           example_3) {
  auto                solution = MakeSolution();
  vector<vector<int>> grid     = {
      {1, -2, 3},
      {2,  3, 5}
  };
  int                 k      = 2;
  vector<vector<int>> expect = {
      {1, 2}
  };
  vector<vector<int>> actual = solution->minAbsDiff(grid, k);
  LCD_EXPECT_EQ(expect, actual);
}
