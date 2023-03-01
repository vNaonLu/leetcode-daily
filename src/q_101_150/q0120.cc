// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Triangle
//
// https://leetcode.com/problems/triangle/
//
// Question ID: 120
// Difficult  : Medium
// Solve Date : 2021/09/16 08:00

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |120. Triangle|:
//
// Given a |triangle| array, return the minimum path sum from top to bottom.
// For each step, you may move to an adjacent number of the row below. More
// formally, if you are on index |i| on the current row, you may move to either
// index |i| or index |i + 1| on the next row.  
//

LEETCODE_BEGIN_RESOLVING(120, Triangle, Solution);

class Solution {
public:
  int minimumTotal(vector<vector<int>> &triangle) {
    for (int i = triangle.size() - 2; i > -1; --i) {
      for (int j = 0; j < triangle[i].size(); ++j) {
        triangle[i][j] += min(triangle[i + 1][j], triangle[i + 1][j + 1]);
      }
    }
    return triangle[0][0];
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= triangle.length <= 200|
// * |triangle[0].length == 1|
// * |triangle[i].length == triangle[i - 1].length + 1|
// * |-10⁴ <= triangle[i][j] <= 10⁴|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: triangle = [[2],[3,4],[6,5,7],[4,1,8,3]]
// Output: 11
//
// The triangle looks like:
//  2
//  3 4
//  6 5 7
// 4 1 8 3
// The minimum path sum from top to bottom is 2 + 3 + 5 + 1 = 11 (underlined
// above).

LEETCODE_SOLUTION_UNITTEST(120, Triangle, example_1) {
  auto                solution = MakeSolution();
  vector<vector<int>> triangle = {
      {2},
      {3, 4},
      {6, 5, 7},
      {4, 1, 8, 3}
  };
  int expect = 11;
  int actual = solution->minimumTotal(triangle);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: triangle = [[-10]]
// Output: -10
//

LEETCODE_SOLUTION_UNITTEST(120, Triangle, example_2) {
  auto                solution = MakeSolution();
  vector<vector<int>> triangle = {{-10}};
  int                 expect   = -10;
  int                 actual   = solution->minimumTotal(triangle);
  LCD_EXPECT_EQ(expect, actual);
}
