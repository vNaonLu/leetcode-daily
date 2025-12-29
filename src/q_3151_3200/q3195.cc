// Copyright 2025 Naon Lu
//
// This file describes the solution of
// Find the Minimum Area to Cover All Ones I
//
// https://leetcode.com/problems/find-the-minimum-area-to-cover-all-ones-i/
//
// Question ID: 3195
// Difficult  : Medium
// Solve Date : 2025/08/22 11:51

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |3195. Find the Minimum Area to Cover All Ones I|:
//
// You are given a 2D binary array |grid|. Find a rectangle with horizontal and
// vertical sides with the smallest area, such that all the 1's in |grid| lie
// inside this rectangle. Return the minimum possible area of the rectangle.
//
//

LEETCODE_BEGIN_RESOLVING(3195, FindTheMinimumAreaToCoverAllOnesI, Solution);

class Solution {
public:
  int minimumArea(vector<vector<int>> &grid) {
    int m     = grid.size();
    int n     = grid[0].size();
    int mnrow = m;
    int mxrow = -1;
    int mncol = n;
    int mxcol = -1;
    for (int i = 0; i < m; ++i) {
      for (int j = 0; j < n; ++j) {
        if (grid[i][j] != 1) {
          continue;
        }

        mnrow = min(mnrow, i);
        mxrow = max(mxrow, i);
        mncol = min(mncol, j);
        mxcol = max(mxcol, j);
      }
    }
    return (mxrow - mnrow + 1) * (mxcol - mncol + 1);
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= grid.length, grid[i].length <= 1000|
// * |grid[i][j]| is either 0 or 1.
// * The input is generated such that there is at least one 1 in |grid|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: grid = [[0,1,0],[1,0,1]]
// Output: 6
//

LEETCODE_SOLUTION_UNITTEST(3195, FindTheMinimumAreaToCoverAllOnesI, example_1) {
  auto                solution = MakeSolution();
  vector<vector<int>> grid     = {
      {0, 1, 0},
      {1, 0, 1}
  };
  int expect = 6;
  int actual = solution->minimumArea(grid);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: grid = [[1,0],[0,0]]
// Output: 1
//

LEETCODE_SOLUTION_UNITTEST(3195, FindTheMinimumAreaToCoverAllOnesI, example_2) {
  auto                solution = MakeSolution();
  vector<vector<int>> grid     = {
      {1, 0},
      {0, 0}
  };
  int expect = 1;
  int actual = solution->minimumArea(grid);
  LCD_EXPECT_EQ(expect, actual);
}
