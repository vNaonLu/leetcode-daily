// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Count Negative Numbers in a Sorted Matrix
//
// https://leetcode.com/problems/count-negative-numbers-in-a-sorted-matrix/
//
// Question ID: 1351
// Difficult  : Easy
// Solve Date : 2022/04/10 14:24

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1351. Count Negative Numbers in a Sorted Matrix|:
//
// Given a |m x n| matrix |grid| which is sorted in non-increasing order both
// row-wise and column-wise, return the number of negative numbers in |grid|.  
//

LEETCODE_BEGIN_RESOLVING(1351, CountNegativeNumbersInASortedMatrix, Solution);

class Solution {
private:
  int count(vector<int> &v) {
    int l = 0, r = v.size();
    while (l < r) {
      int m = l + (r - l) / 2;
      if (v[m] >= 0) {
        l = m + 1;
      } else {
        r = m;
      }
    }

    return v.size() - l;
  }

public:
  int countNegatives(vector<vector<int>> &grid) {
    int res = 0;
    for (auto &v : grid) {
      res += count(v);
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
// * |1 <= m, n <= 100|
// * |-100 <= grid[i][j] <= 100|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: grid = [[4,3,2,-1],[3,2,1,-1],[1,1,-1,-2],[-1,-1,-2,-3]]
// Output: 8
//
// There are 8 negatives number in the matrix.

LEETCODE_SOLUTION_UNITTEST(1351, CountNegativeNumbersInASortedMatrix,
                           example_1) {
  auto                solution = MakeSolution();
  vector<vector<int>> grid     = {
      { 4,  3,  2, -1},
      { 3,  2,  1, -1},
      { 1,  1, -1, -2},
      {-1, -1, -2, -3}
  };
  int expect = 8;
  int actual = solution->countNegatives(grid);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: grid = [[3,2],[1,0]]
// Output: 0
//

LEETCODE_SOLUTION_UNITTEST(1351, CountNegativeNumbersInASortedMatrix,
                           example_2) {
  auto                solution = MakeSolution();
  vector<vector<int>> grid     = {
      {3, 2},
      {1, 0}
  };
  int expect = 0;
  int actual = solution->countNegatives(grid);
  LCD_EXPECT_EQ(expect, actual);
}
