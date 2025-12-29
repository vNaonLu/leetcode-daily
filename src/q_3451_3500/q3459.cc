// Copyright 2025 Naon Lu
//
// This file describes the solution of
// Length of Longest V-Shaped Diagonal Segment
//
// https://leetcode.com/problems/length-of-longest-v-shaped-diagonal-segment/
//
// Question ID: 3459
// Difficult  : Hard
// Solve Date : 2025/08/27 20:48

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |3459. Length of Longest V-Shaped Diagonal Segment|:
//
// You are given a 2D integer matrix |grid| of size |n x m|, where each element
// is either |0|, |1|, or |2|. A V-shaped diagonal segment is defined as:
//
//  • The segment starts with |1|.
//
//  • The subsequent elements follow this infinite sequence: |2, 0, 2, 0, ...|.
//
//  • The segment:
//
//
//    • Starts along a diagonal direction (top-left to bottom-right,
//    bottom-right to top-left, top-right to bottom-left, or bottom-left to
//    top-right).
//
//    • Continues the sequence in the same diagonal direction.
//
//    • Makes at most one clockwise 90-degree turn to another diagonal direction
//    while maintaining the sequence.
//
//
// ![img](https://assets.leetcode.com/uploads/2025/01/11/length_of_longest3.jpg)
// Return the length of the longest V-shaped diagonal segment. If no valid
// segment exists, return 0.
//
//

LEETCODE_BEGIN_RESOLVING(3459, LengthOfLongestVShapedDiagonalSegment, Solution);

class Solution {
public:
  static bool isOutSide(int i, int j, int n, int m) {
    return i < 0 || i >= n || j < 0 || j >= m;
  }

  static int lenOfVDiagonal(vector<vector<int>> &grid) {
    const int                       n = grid.size(), m = grid[0].size();
    vector<vector<array<short, 4>>> dp(n, vector<array<short, 4>>(m));

    for (int i = n - 2; i >= 0; i--) {
      for (int j = m - 2; j >= 0; j--)
        if ((grid[i + 1][j + 1] ^ 2) == grid[i][j])
          dp[i][j][0] = 1 + dp[i + 1][j + 1][0];
      for (int j = 1; j < m; j++)
        if ((grid[i + 1][j - 1] ^ 2) == grid[i][j])
          dp[i][j][1] = 1 + dp[i + 1][j - 1][1];
    }
    for (int i = 1; i < n; i++) {
      for (int j = 1; j < m; j++)
        if ((grid[i - 1][j - 1] ^ 2) == grid[i][j])
          dp[i][j][2] = 1 + dp[i - 1][j - 1][2];
      for (int j = m - 2; j >= 0; j--)
        if ((grid[i - 1][j + 1] ^ 2) == grid[i][j])
          dp[i][j][3] = 1 + dp[i - 1][j + 1][3];
    }

    int ans = 0;
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        if (grid[i][j] == 1) {
          ans = max(ans, 1);
          for (int dir = 0; dir < 4; dir++) {
            int s = i + d[dir], t = j + d[dir + 1];
            if (isOutSide(s, t, n, m) || grid[s][t] != 2)
              continue;
            const int newDir = (dir + 1) & 3; // same as %4

            for (int cnt = 1;
                 !isOutSide(s, t, n, m) && grid[s][t] == 2 * (cnt & 1);
                 cnt++, s += d[dir], t += d[dir + 1]) {
              ans = max(ans, cnt + dp[s][t][newDir] + 1);
            }
          }
        }
      }
    }
    return ans;
  }

private:
  static constexpr int d[5] = {1, 1, -1, -1, 1}; // (1,1),(1,-1),(-1,-1),(-1,1)
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |n == grid.length|
// * |m == grid[i].length|
// * |1 <= n, m <= 500|
// * |grid[i][j]| is either |0|, |1| or |2|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: grid = [[2,2,1,2,2],[2,0,2,2,0],[2,0,1,1,0],[1,0,2,2,2],[2,0,0,2,2]]
// Output: 5
//

LEETCODE_SOLUTION_UNITTEST(3459, LengthOfLongestVShapedDiagonalSegment,
                           example_1) {
  auto                solution = MakeSolution();
  vector<vector<int>> grid     = {
      {2, 2, 1, 2, 2},
      {2, 0, 2, 2, 0},
      {2, 0, 1, 1, 0},
      {1, 0, 2, 2, 2},
      {2, 0, 0, 2, 2}
  };
  int expect = 5;
  int actual = solution->lenOfVDiagonal(grid);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: grid = [[2,2,2,2,2],[2,0,2,2,0],[2,0,1,1,0],[1,0,2,2,2],[2,0,0,2,2]]
// Output: 4
//

LEETCODE_SOLUTION_UNITTEST(3459, LengthOfLongestVShapedDiagonalSegment,
                           example_2) {
  auto                solution = MakeSolution();
  vector<vector<int>> grid     = {
      {2, 2, 2, 2, 2},
      {2, 0, 2, 2, 0},
      {2, 0, 1, 1, 0},
      {1, 0, 2, 2, 2},
      {2, 0, 0, 2, 2}
  };
  int expect = 4;
  int actual = solution->lenOfVDiagonal(grid);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: grid = [[1,2,2,2,2],[2,2,2,2,0],[2,0,0,0,0],[0,0,2,2,2],[2,0,0,2,0]]
// Output: 5
//

LEETCODE_SOLUTION_UNITTEST(3459, LengthOfLongestVShapedDiagonalSegment,
                           example_3) {
  auto                solution = MakeSolution();
  vector<vector<int>> grid     = {
      {1, 2, 2, 2, 2},
      {2, 2, 2, 2, 0},
      {2, 0, 0, 0, 0},
      {0, 0, 2, 2, 2},
      {2, 0, 0, 2, 0}
  };
  int expect = 5;
  int actual = solution->lenOfVDiagonal(grid);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #4]
//  Input: grid = [[1]]
// Output: 1
//

LEETCODE_SOLUTION_UNITTEST(3459, LengthOfLongestVShapedDiagonalSegment,
                           example_4) {
  auto                solution = MakeSolution();
  vector<vector<int>> grid     = {{1}};
  int                 expect   = 1;
  int                 actual   = solution->lenOfVDiagonal(grid);
  LCD_EXPECT_EQ(expect, actual);
}
