// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Last Day Where You Can Still Cross
//
// https://leetcode.com/problems/last-day-where-you-can-still-cross/
//
// Question ID: 1970
// Difficult  : Hard
// Solve Date : 2023/06/30 14:47

#include <iosfwd>
#include <queue>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1970. Last Day Where You Can Still Cross|:
//
// There is a 1-based binary matrix where |0| represents land and |1| represents
// water. You are given integers |row| and |col| representing the number of rows
// and columns in the matrix, respectively. Initially on day |0|, the entire
// matrix is land. However, each day a new cell becomes flooded with water. You
// are given a 1-based 2D array |cells|, where |cells[i] = [rᵢ, cᵢ]| represents
// that on the |iᵗʰ| day, the cell on the |rᵢᵗʰ| row and |cᵢᵗʰ| column (1-based
// coordinates) will be covered with water (i.e., changed to |1|). You want to
// find the last day that it is possible to walk from the top to the bottom by
// only walking on land cells. You can start from any cell in the top row and
// end at any cell in the bottom row. You can only travel in the four cardinal
// directions (left, right, up, and down). Return the last day where it is
// possible to walk from the top to the bottom by only walking on land cells.
//
//

LEETCODE_BEGIN_RESOLVING(1970, LastDayWhereYouCanStillCross, Solution);

class Solution {
public:
  int latestDayToCross(int row, int col, vector<vector<int>> &cells) {
    int lo  = 0;
    int hi  = row * col;
    int res = 0;
    while (lo < hi - 1) {
      int mid = lo + (hi - lo) / 2;
      if (isPossible(row, col, mid, cells)) {
        lo  = mid;
        res = mid;
      } else {
        hi = mid;
      }
    }
    return res;
  }

private:
  const vector<int> kDir = {1, 0, 0, 1, -1, 0, 0, -1};
  bool isPossible(int m, int n, int t, vector<vector<int>> &cells) {
    vector<vector<int>> grid(m + 1, vector<int>(n + 1, 0));
    for (int i = 0; i < t; ++i) {
      grid[cells[i][0]][cells[i][1]] = 1;
    }

    queue<pair<int, int>> q;
    for (int i = 1; i <= n; ++i) {
      if (grid[1][i] == 0) {
        q.emplace(1, i);
        grid[1][i] = 1;
      }
    }

    while (!q.empty()) {
      auto [r, c] = q.front();
      q.pop();

      for (int i = 0; i < kDir.size(); ++i) {
        int dr = r + kDir[i];
        int dc = c + kDir[++i];

        if (dr > 0 && dr <= m && dc > 0 && dc <= n && grid[dr][dc] == 0) {
          grid[dr][dc] = 1;
          if (dr == m) {
            return true;
          }

          q.emplace(dr, dc);
        }
      }
    }
    return false;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |2 <= row, col <= 2 * 10⁴|
// * |4 <= row * col <= 2 * 10⁴|
// * |cells.length == row * col|
// * |1 <= rᵢ <= row|
// * |1 <= cᵢ <= col|
// * All the values of |cells| are unique.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: row = 2, col = 2, cells = [[1,1],[2,1],[1,2],[2,2]]
// Output: 2
//
// The above image depicts how the matrix changes each day starting from day 0.
// The last day where it is possible to cross from top to bottom is on day 2.

LEETCODE_SOLUTION_UNITTEST(1970, LastDayWhereYouCanStillCross, example_1) {
  auto                solution = MakeSolution();
  int                 row      = 2;
  int                 col      = 2;
  vector<vector<int>> cells    = {
      {1, 1},
      {2, 1},
      {1, 2},
      {2, 2}
  };
  int expect = 2;
  int actual = solution->latestDayToCross(row, col, cells);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: row = 2, col = 2, cells = [[1,1],[1,2],[2,1],[2,2]]
// Output: 1
//
// The above image depicts how the matrix changes each day starting from day 0.
// The last day where it is possible to cross from top to bottom is on day 1.

LEETCODE_SOLUTION_UNITTEST(1970, LastDayWhereYouCanStillCross, example_2) {
  auto                solution = MakeSolution();
  int                 row      = 2;
  int                 col      = 2;
  vector<vector<int>> cells    = {
      {1, 1},
      {1, 2},
      {2, 1},
      {2, 2}
  };
  int expect = 1;
  int actual = solution->latestDayToCross(row, col, cells);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: row = 3, col = 3, cells =
//  [[1,2],[2,1],[3,3],[2,2],[1,1],[1,3],[2,3],[3,2],[3,1]]
// Output: 3
//
// The above image depicts how the matrix changes each day starting from day 0.
// The last day where it is possible to cross from top to bottom is on day 3.

LEETCODE_SOLUTION_UNITTEST(1970, LastDayWhereYouCanStillCross, example_3) {
  auto                solution = MakeSolution();
  int                 row      = 3;
  int                 col      = 3;
  vector<vector<int>> cells    = {
      {1, 2},
      {2, 1},
      {3, 3},
      {2, 2},
      {1, 1},
      {1, 3},
      {2, 3},
      {3, 2},
      {3, 1}
  };
  int expect = 3;
  int actual = solution->latestDayToCross(row, col, cells);
  LCD_EXPECT_EQ(expect, actual);
}
