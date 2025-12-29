// Copyright 2025 Naon Lu
//
// This file describes the solution of
// Find the Minimum Area to Cover All Ones II
//
// https://leetcode.com/problems/find-the-minimum-area-to-cover-all-ones-ii/
//
// Question ID: 3197
// Difficult  : Hard
// Solve Date : 2025/08/23 20:22

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |3197. Find the Minimum Area to Cover All Ones II|:
//
// You are given a 2D binary array |grid|. You need to find 3 non-overlapping
// rectangles having non-zero areas with horizontal and vertical sides such that
// all the 1's in |grid| lie inside these rectangles. Return the minimum
// possible sum of the area of these rectangles. Note that the rectangles are
// allowed to touch.
//
//

LEETCODE_BEGIN_RESOLVING(3197, FindTheMinimumAreaToCoverAllOnesII, Solution);

class Solution {
public:
  int minimumSum(vector<vector<int>> &A) {
    int res = numeric_limits<int>::max();
    for (int rot = 0; rot < 4; rot++) {
      int n = A.size(), m = A[0].size();
      for (int i = 1; i < n; i++) {
        int a1 = minimumArea(vector<vector<int>>(A.begin(), A.begin() + i));
        for (int j = 1; j < m; j++) {
          vector<vector<int>> part2(n - i, vector<int>(j));
          vector<vector<int>> part3(n - i, vector<int>(m - j));
          for (int r = 0; r < n - i; r++) {
            copy(A[i + r].begin(), A[i + r].begin() + j, part2[r].begin());
            copy(A[i + r].begin() + j, A[i + r].end(), part3[r].begin());
          }
          int a2 = minimumArea(part2);
          int a3 = minimumArea(part3);
          res    = min(res, a1 + a2 + a3);
        }
        for (int i2 = i + 1; i2 < n; i2++) {
          vector<vector<int>> part2(A.begin() + i, A.begin() + i2);
          vector<vector<int>> part3(A.begin() + i2, A.end());
          int                 a2 = minimumArea(part2);
          int                 a3 = minimumArea(part3);
          res                    = min(res, a1 + a2 + a3);
        }
      }
      A = rotate(A);
    }
    return res;
  }

private:
  int minimumArea(vector<vector<int>> const &A) {
    if (A.empty() || A[0].empty())
      return 0;
    int n = A.size(), m = A[0].size();
    int left = numeric_limits<int>::max(), top = numeric_limits<int>::max(),
        right = -1, bottom = -1;
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        if (A[i][j] == 1) {
          left   = min(left, j);
          top    = min(top, i);
          right  = max(right, j);
          bottom = max(bottom, i);
        }
      }
    }
    if (right == -1)
      return 0;
    return (right - left + 1) * (bottom - top + 1);
  }

  vector<vector<int>> rotate(vector<vector<int>> &A) {
    int                 n = A.size(), m = A[0].size();
    vector<vector<int>> rotated(m, vector<int>(n));
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        rotated[j][n - 1 - i] = A[i][j];
      }
    }
    return rotated;
  }
};
LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= grid.length, grid[i].length <= 30|
// * |grid[i][j]| is either 0 or 1.
// * The input is generated such that there are at least three 1's in |grid|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: grid = [[1,0,1],[1,1,1]]
// Output: 5
//

LEETCODE_SOLUTION_UNITTEST(3197, FindTheMinimumAreaToCoverAllOnesII,
                           example_1) {
  auto                solution = MakeSolution();
  vector<vector<int>> grid     = {
      {1, 0, 1},
      {1, 1, 1}
  };
  int expect = 5;
  int actual = solution->minimumSum(grid);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: grid = [[1,0,1,0],[0,1,0,1]]
// Output: 5
//

LEETCODE_SOLUTION_UNITTEST(3197, FindTheMinimumAreaToCoverAllOnesII,
                           example_2) {
  auto                solution = MakeSolution();
  vector<vector<int>> grid     = {
      {1, 0, 1, 0},
      {0, 1, 0, 1}
  };
  int expect = 5;
  int actual = solution->minimumSum(grid);
  LCD_EXPECT_EQ(expect, actual);
}
