// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Count Servers that Communicate
//
// https://leetcode.com/problems/count-servers-that-communicate/
//
// Question ID: 1267
// Difficult  : Medium
// Solve Date : 2022/02/01 13:41

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1267. Count Servers that Communicate|:
//
// You are given a map of a server center, represented as a |m * n| integer
// matrix  |grid|, where 1 means that on that cell there is a server and 0 means
// that it is no server. Two servers are said to communicate if they are on the
// same row or on the same column. Return the number of servers that communicate
// with any other server.  
//

LEETCODE_BEGIN_RESOLVING(1267, CountServersThatCommunicate, Solution);

class Solution {
public:
  int countServers(vector<vector<int>> &grid) {
    int         m = grid.size(), n = grid[0].size();
    vector<int> conn_cols(n, 0), conn_rows(m, 0);
    for (int i = 0; i < m; ++i) {
      for (int j = 0; j < n; ++j) {
        if (grid[i][j] == 1) {
          ++conn_rows[i];
          ++conn_cols[j];
        }
      }
    }
    int res = 0;
    for (int i = 0; i < m; ++i) {
      for (int j = 0; j < n; ++j) {
        if (grid[i][j] == 1 && (conn_rows[i] > 1 || conn_cols[j] > 1)) {
          ++res;
        }
      }
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
// * |1 <= m <= 250|
// * |1 <= n <= 250|
// * |grid[i][j] == 0 or 1|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: grid = [[1,0],[0,1]]
// Output: 0
// Explanation: No servers can communicate with others.
//

LEETCODE_SOLUTION_UNITTEST(1267, CountServersThatCommunicate, example_1) {
  auto                solution = MakeSolution();
  vector<vector<int>> grid     = {
      {1, 0},
      {0, 1}
  };
  int expect = 0;
  int actual = solution->countServers(grid);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: grid = [[1,0],[1,1]]
// Output: 3
// Explanation: All three servers can communicate with at least one other
// server.
//

LEETCODE_SOLUTION_UNITTEST(1267, CountServersThatCommunicate, example_2) {
  auto                solution = MakeSolution();
  vector<vector<int>> grid     = {
      {1, 0},
      {1, 1}
  };
  int expect = 3;
  int actual = solution->countServers(grid);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: grid = [[1,1,0,0],[0,0,1,0],[0,0,1,0],[0,0,0,1]]
// Output: 4
// Explanation: The two servers in the first row can communicate with each
// other. The two servers in the third column can communicate with each other.
// The server at right bottom corner can't communicate with any other server.
//

LEETCODE_SOLUTION_UNITTEST(1267, CountServersThatCommunicate, example_3) {
  auto                solution = MakeSolution();
  vector<vector<int>> grid     = {
      {1, 1, 0, 0},
      {0, 0, 1, 0},
      {0, 0, 1, 0},
      {0, 0, 0, 1}
  };
  int expect = 4;
  int actual = solution->countServers(grid);
  LCD_EXPECT_EQ(expect, actual);
}
